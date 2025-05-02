#include "Univers.hxx"
#include <algorithm>
#include <iostream>
#include <array>

#include "VTKWriter.hxx"
#include "Forces.hxx"


Univers::Univers(int n, Vecteur l, float r, float eps, float sigm, float grav, int b_cond){
            
    //Initialisation
    dimension = n;
    Ld = l;
    rcut = r;
    G = grav;
    epsilon = eps;
    sigma = sigm;
    sigma6 = std::pow(sigma, 6); //Précalculé car beaucoup utilisé
    boundary_condition = b_cond;

    //Grille des cellules
    ncd_x = (Ld.x/rcut); ncd_y = (Ld.y/rcut); ncd_z = (Ld.z/rcut);
    fLd = Vecteur(ncd_x,ncd_y,ncd_z)*rcut; //On tronque Ld au cas ou qu'il ne soit pas multiple de rcut

    if (dimension==1) cellules.resize(ncd_x);
    else if (dimension==2) cellules.resize(ncd_x*ncd_y);
    else cellules.resize(ncd_x*ncd_y*ncd_z);
    setupNeighbours();
}


void Univers::addParticle(Particule& p) {
    //Calcul de l'id de cellule en fonction de la position de p
    int calc_id = getCellLinearIndex(p.getPosition().x/rcut, p.getPosition().y/rcut, p.getPosition().z/rcut);
    particules.push_back(p);
    cellules[calc_id].partInd.push_back(particules.size()-1);
}


int Univers::getCellLinearIndex(int x, int y, int z) const {
    if (dimension==1) return x;
    if (dimension==2) return x + ncd_x * y;
    return x + ncd_x * (y + ncd_y * z);
}


void Univers::setupNeighbours() {

    for (int i = 0; i < ncd_x; ++i) {
    for (int j = 0; j < (dimension >= 2 ? ncd_y : 1); ++j) {
    for (int k = 0; k < (dimension >= 3 ? ncd_z : 1); ++k) {

        Cellule& cellule = cellules[getCellLinearIndex(i, j, k)];

        //On initialise la positionn des cellules
        cellule.position = Vecteur(
            i*rcut + rcut/2,
            dimension >= 2 ? j*rcut + rcut/2 : 0,
            dimension >= 3 ? k*rcut + rcut/2 : 0); 

        for (int di = -1; di <= 1; ++di) {
        for (int dj = (dimension >= 2)? -1 : 0; dj <= (dimension >= 2)?  1 : 0; ++dj) {
        for (int dk = (dimension >= 3)? -1 : 0; dk <= (dimension >= 3)?  1 : 0; ++dk) {

            int ni = i + di, nj = j + dj, nk = k + dk;

            if                    (ni < 0 || ni >= ncd_x)  continue;    
            if (dimension >= 2 && (nj < 0 || nj >= ncd_y)) continue;
            if (dimension >= 3 && (nk < 0 || nk >= ncd_z)) continue;

            cellule.voisins.push_back(&cellules[getCellLinearIndex(ni, nj, nk)]);
        }
        }
        }
    }
    }
    }
}


void Univers::updateCellPart(int c, int ind_p) {

    Particule& p = particules[cellules[c].partInd[ind_p]];

    //En théorie, cette condition n'est jamais sensée être réalisée
    //Cependant il peut avoir des dépassement de float dans HandleBoundaryConditions si le pas de temps est trop grand
    if (isPositionOut(p.getPosition())) return;

    //Calcul de l'id de cellule en fonction de la position de p
    int calc_id = getCellLinearIndex(p.getPosition().x/rcut, p.getPosition().y/rcut, p.getPosition().z/rcut);

    //Si la particule n'a pas changé de cellules
    if (c == calc_id) return;
    
    //Sinon on la deplace dans la bonne cellule
    uint ind = cellules[c].partInd[ind_p];
    cellules[c].partInd.erase(cellules[c].partInd.begin() + ind_p);
    cellules[calc_id].partInd.push_back(ind);
}


    bool Univers::isPositionOut(const Vecteur& v) const {
        return ((v.x < 0 || v.x >= fLd.x) ||
                (dimension >= 2 && (v.y < 0 || v.y >= fLd.y)) ||
                (dimension >= 3 && (v.z < 0 || v.z >= fLd.z)));
    }

void Univers::HandleBoundaryConditions(Particule& p, Vecteur& calcPos, int c, int ind_p, int boundary_condition) {

    switch(boundary_condition) {
            
        case BOUND_REFLEXION: {

            // Distance minimale au mur (éviter division par 0)
            //Cette distance affecte beaucoup le résultat de la réfléxion si le pas de temps est trop grand
            const float r_min = 0.01f; 
            calcPos.clamp(Vecteur(r_min,r_min,r_min), fLd - r_min, dimension);
            p.setPosition(calcPos);
            break;
        }
            
        case BOUND_ABSORPTION: {
            if (isPositionOut(calcPos))
                cellules[c].partInd.erase(cellules[c].partInd.begin() + ind_p); //Effacer la particule des cellules
            p.setPosition(calcPos);
            break;
        }

        case BOUND_PERIODIC: {

            if (!isPositionOut(calcPos)) return;

            //Fonction qui calcule le modulo périodique de la position
            auto PeriodicMod = [](float pos, float maxPos) {
                const double result = std::fmod(pos, maxPos);
                return result < 0.0f ? result + maxPos : result;
            };

            Vecteur periodicPos = Vecteur(
                PeriodicMod(calcPos.x, fLd.x),
                dimension >= 2 ? PeriodicMod(calcPos.y, fLd.y) : 0,
                dimension >= 3 ? PeriodicMod(calcPos.z, fLd.z) : 0
            );
            
            p.setPosition(periodicPos);
            break;
        }
    }
}


void Univers::calcForces() {

    for(auto &cell : cellules) { //Pour toute les cellules
        for (auto& i : cell.partInd) { //Pour toute les particules des cellules
            for(Cellule* cellNeigh : cell.voisins) { //Pour toutes les cellules voisines

                //Condition de distances
                if ((cellNeigh->position - particules[i].getPosition()).squared_norm() > rcut*rcut) 
                    continue;

                for (auto& j : cellNeigh->partInd) {  //Pour toute les particules des cellules voisines

                    //Optimisation pour réduire la complexité par deux
                    if (particules[i].getId() >= particules[j].getId()) continue;

                    //Calcul de la force entre p_i et ses voisines p_j
                    Vecteur forces = Forces::calcForceInteractionPot(i,j, particules, sigma6, epsilon) +
                                     Forces::calcForceInteractionGrav(i,j, particules);
                    particules[i].addForce(forces);
                    particules[j].subForce(forces); // Fji = -Fij
                                                
                }
            }
            //Force de reflexion des bords
            if (boundary_condition == BOUND_REFLEXION)
                particules[i].addForce(Forces::calcForceReflexion(i, particules, sigma, epsilon, fLd, dimension));

            //Potentiel gravitationnel
            if (dimension >= 2)
                particules[i].addForce(Vecteur(0.0f,Forces::calcPotentielGravitationnel(particules[i].getMasse(), G), 0.0f));
        }
    }
}



void Univers::printParticules() {
    for(auto& c : cellules) 
        for(auto& i : c.partInd)
            std::cout << particules[i].getPosition() << std::endl;
}


//Algorithme de Stromer-Verlet
void Univers::StromerVerlet(float t_end, float delta_t) {

    float t = 0.0f;

    //On calcul les forces initiales des particules
    calcForces();
    
    VTKWriter::write("start.vtu", *this);

    while (t < t_end) {

        //Calcul des positions
        for (size_t c = 0; c < cellules.size(); c++) {
            for (int ind_p = 0; ind_p < cellules[c].partInd.size(); ind_p++) {

                int i = cellules[c].partInd[ind_p];

                particules[i].setForceOld(particules[i].getForce());
                particules[i].setForce(Vecteur(0.0f, 0.0f, 0.0f)); // Reinitialisation des forces

                Particule& p = particules[i];
                Vecteur newPosition = p.getPosition() + delta_t*(p.getVitesse() + .5f/p.getMasse()*particules[i].getForceOld()*delta_t);

                //Gérer les conditions aux limites avant d'ajuster la position
                HandleBoundaryConditions(p, newPosition, c, ind_p, boundary_condition);

            }
        }

        //Calcul des vitesses
        calcForces();

        for (size_t c = 0; c < cellules.size(); c++) {
            for (auto& i : cellules[c].partInd) {
                Particule &p = particules[i];
                
                Vecteur newVitesse = p.getVitesse() + delta_t*.5f/p.getMasse()*(particules[i].getForce() + particules[i].getForceOld());
                particules[i].setVitesse(newVitesse);
            }
        }

        //Update des cellules des particules
        for (size_t c = 0; c < cellules.size(); c++) {
            //On parcours à l'envers pour éviter les décalages
            for (int ind_p = 0; ind_p < cellules[c].partInd.size(); ind_p++) {
                updateCellPart(c, ind_p);
            }
        }

        t += delta_t;
    }
    VTKWriter::write("end.vtu", *this);
}
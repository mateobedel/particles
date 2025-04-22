#include "Univers.hxx"
#include <algorithm>
#include <iostream>

#include "VTKWriter.hxx"


Univers::Univers(int n, int nb_p, Vecteur l, float r, float eps, float sigm, int b_cond){
            
    //Initialisation
    dimension = n;
    nb_particules = nb_p;
    Ld = l;
    rcut = r;
    epsilon = eps;
    sigma = sigm;
    sigma6 = std::pow(sigma, 6);
    boundary_condition = b_cond;

    //Grille des cellules
    ncd_x = (Ld.x/rcut); ncd_y = (Ld.y/rcut); ncd_z = (Ld.z/rcut);
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
        cellule.position = Vecteur(
            i*rcut + rcut/2,
            dimension >= 2 ? j*rcut + rcut/2 : 0,
            dimension >= 3 ? k*rcut + rcut/2 : 0); 

        for (int di = -1; di <= 1; ++di) {
        for (int dj = (dimension >= 2)? -1 : 0; dj <= (dimension >= 2)?  1 : 0; ++dj) {
        for (int dk = (dimension >= 3)? -1 : 0; dk <= (dimension >= 3)?  1 : 0; ++dk) {

            int ni = i + di;
            int nj = j + dj;
            int nk = k + dk;

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

        return ((v.x < 0 || v.x >= ncd_x*rcut) ||
                (dimension >= 2 && (v.y < 0 || v.y >= ncd_y*rcut)) ||
                (dimension >= 3 && (v.z < 0 || v.z >= ncd_z*rcut)));

    }

void Univers::HandleBoundaryConditions(Particule& p, Vecteur& calcPos, int c, int ind_p, int boundary_condition) {

    switch(boundary_condition) {

        case BOUND_REFLEXION:
            p.setVitesse(0.0f - p.getVitesse());
            break;

        case BOUND_ABSORPTION:
            cellules[c].partInd.erase(cellules[c].partInd.begin() + ind_p);
            break;

        case BOUND_PERIODIC:

            auto PeriodicMod = [](float pos, float maxPos) {
                const double result = std::fmod(pos, maxPos);
                return result < 0.0f ? result + maxPos : result;
            };

            Vecteur periodicPos = Vecteur(
                PeriodicMod(calcPos.x, ncd_x*rcut),
                dimension >= 2 ? PeriodicMod(calcPos.y, ncd_y*rcut) : 0,
                dimension >= 3 ? PeriodicMod(calcPos.z, ncd_z*rcut) : 0
            );
            
            p.setPosition(periodicPos);
            break;
    }
}


    Vecteur Univers::calcForceInteractionPot(int i, int j) {

        Particule& pi = particules[i];
        Particule& pj = particules[j];

        Vecteur r_ij = pj.getPosition() - pi.getPosition();
        float r_sq = r_ij.squared_norm();

        if (r_sq < 1e-4) return Vecteur(0.0f,0.0f,0.0f);

        float sr6 = sigma6 / std::pow(r_sq, 3);
        float force_magnitude = 24.0f * epsilon * sr6 * (1.0f - 2.0f * sr6) / r_sq;
        return r_ij * force_magnitude;
    }


Vecteur Univers::calcForceInteractionGrav(int i, int j) {

    Particule& pi = particules[i];
    Particule& pj = particules[j];

    Vecteur r_ij = pj.getPosition() - pi.getPosition();
    float r_sq = r_ij.squared_norm();

    if (r_sq < 1e-6) return Vecteur(0.0f,0.0f,0.0f);

    float inv_sqrt_r = 1.0f / std::sqrt(r_sq);

    return r_ij * (pi.getMasse() * pj.getMasse()) * inv_sqrt_r * inv_sqrt_r * inv_sqrt_r;
}


void Univers::resetForces() {
    for (auto& c : cellules) {
        for (auto& i : c.partInd) {
            particules[i].force.x = 0.0f;
            particules[i].force.y = 0.0f;
            particules[i].force.z = 0.0f;
        }
    }
}


void Univers::calcForces() {

    resetForces();

    for(auto &cell : cellules) { //Pour toute les cellules
        for (auto& i : cell.partInd) { //Pour toute les particules des cellules
            for(Cellule* cellNeigh : cell.voisins) { //Pour toutes les cellules voisines

                if ((cellNeigh->position - particules[i].getPosition()).squared_norm() > rcut*rcut) 
                    continue;

                for (auto& j : cellNeigh->partInd) {  //Pour toute les particules des cellules voisines

                    if (particules[i].getId() >= particules[j].getId()) continue;

                    //Calcul de la force entre p_i et ses voisines p_j
                    Vecteur forces = calcForceInteractionPot(i,j) + calcForceInteractionGrav(i,j);
                    particules[i].force += forces;
                    particules[j].force -= forces;
                                                
                }
            }
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

        printParticules();
        std::cout << std::endl;
        
        //Calcul des positions
        for (size_t c = 0; c < cellules.size(); c++) {
            for (int ind_p = 0; ind_p < cellules[c].partInd.size(); ind_p++) {

                int i = cellules[c].partInd[ind_p];
                particules[i].force_old = particules[i].force;

                Particule& p = particules[i];
                Vecteur newPosition = p.getPosition() + delta_t*(p.getVitesse() + .5f/p.getMasse()*particules[i].force_old*delta_t);

                //Gérer les conditions aux limites
                if (isPositionOut(newPosition)) {
                    HandleBoundaryConditions(p, newPosition, c, ind_p, boundary_condition);
                } else {
                    particules[i].setPosition(newPosition);
                }
                
            }
        }

        //Calcul des vitesses
        calcForces();

        for (size_t c = 0; c < cellules.size(); c++) {
            for (auto& i : cellules[c].partInd) {
                Particule &p = particules[i];
                Vecteur newVitesse = p.getVitesse() + delta_t*.5f/p.getMasse()*(particules[i].force + particules[i].force_old);
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
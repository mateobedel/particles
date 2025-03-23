#include "Univers.hxx"
#include <algorithm>
#include <iostream>

#include "VTKWriter.hxx"


Univers::Univers(int n, int nb_p, Vecteur l, float r, float eps, float sigm){
            
    //Initialisation
    dimension = n;
    nb_particules = nb_p;
    Ld = l;
    rcut = r;
    epsilon = eps;
    sigma = sigm;

    //Grille des cellules
    ncd_x = (Ld.x/rcut); ncd_y = (Ld.y/rcut); ncd_z = (Ld.z/rcut);
    if (dimension==1) cellules.resize(ncd_x);
    else if (dimension==2) cellules.resize(ncd_x*ncd_y);
    else cellules.resize(ncd_x*ncd_y*ncd_z);
    setupNeighbours();

    //Distribution aléatoire uniforme sur [0,1]
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0, 1.0);


    // //Generation aléatoire des particules
    // for (int i = 0; i < nb_particules; i++) {
    //     float masse = 1.0f;
    //     Vecteur rdmPos = Vecteur(
    //         dist(mt)*Ld.x, 
    //         dimension>1 ? dist(mt)*Ld.y : 0.0f,
    //         dimension>2 ? dist(mt)*Ld.z : 0.0f
    //     );
    //     Vecteur vit = Vecteur(0.0f, 0.0f, 0.0f);
    //     Particule p = Particule(masse, rdmPos, vit);
    //     addParticle(p);
    // }

    //Système solaire
    // Particule soleil = Particule(1,        10+Vecteur(0,0,0),    Vecteur(0,0,0));
    // Particule terre = Particule(3.0e-6,    10+Vecteur(0,1,0),    Vecteur(-1,0,0));
    // Particule jupiter = Particule(9.55e-4, 10+Vecteur(0,5.36,0), Vecteur(-0.425, 0, 0));
    // addParticle(soleil);
    // addParticle(terre);
    // addParticle(jupiter);

    //Carré rouge
    for(int i = 0; i < 40; i++) {
        for(int j = 0; j < 40; j++) {
            float ecart = 1.0f/64.0f;
            float start_x = 8.0f;
            Particule p = Particule(1, Vecteur(start_x+ecart*i,ecart*j,0), Vecteur(0,10,0));
            addParticle(p);
        }
    }

    //Rectangle bleu
    for(int i = 0; i < 160; i++) {
        for(int j = 0; j < 40; j++) {
            float ecart = 1.0f/64.0f;
            float start_x = 8.0f;
            float start_y = 32.0f;
            Particule p = Particule(1, Vecteur(start_x+ecart*(float)(i),start_y+ecart*(float)j,0), Vecteur(0,0,0));
            addParticle(p);
        }
    }

}


void Univers::addParticle(Particule& p) {
    //Calcul de l'id de cellule en fonction de la position de p
    int calc_id = getCellLinearIndex(p.getPosition().x/rcut, p.getPosition().y/rcut, p.getPosition().z/rcut);
    cellules[calc_id].particules.push_back(p);
}


int Univers::getCellLinearIndex(int x, int y, int z) {
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


void Univers::updateCellPart(int c, int i) {

    Particule p = cellules[c].particules[i];

    //Supprimer la particule si elle sort des cellules (ncd_x*rcut != Ld.x)
    if                ((p.getPosition().x < 0 || p.getPosition().x >= ncd_x*rcut)  ||
    (dimension >= 2 && (p.getPosition().y < 0 || p.getPosition().y >= ncd_y*rcut)) ||
    (dimension >= 3 && (p.getPosition().z < 0 || p.getPosition().z >= ncd_z*rcut))) {
        cellules[c].particules.erase(cellules[c].particules.begin() + i);
        return;
    }

    

    //Calcul de l'id de cellule en fonction de la position de p
    int calc_id = getCellLinearIndex(p.getPosition().x/rcut, p.getPosition().y/rcut, p.getPosition().z/rcut);

    //Si la particule n'a pas changé de cellules
    if (c == calc_id) return;
    
    //Sinon on la deplace dans la bonne cellule
    cellules[c].particules.erase(cellules[c].particules.begin() + i);
    cellules[calc_id].particules.push_back(p);
}


Vecteur Univers::calcForceInteractionPot(Cellule& c_i, Cellule& c_j, int i, int j) {

    Particule& pi = c_i.particules[i];
    Particule& pj = c_j.particules[j];

    Vecteur r_ij = pj.getPosition() - pi.getPosition();;
    float norm_rij = r_ij.norm();

    if (norm_rij == 0.0f) 
        return Vecteur(0.0f,0.0f,0.0f);

    float sr6 = std::pow(sigma / norm_rij, 6);
    float force_magnitude = 24.0f * epsilon * sr6 * (1.0f - 2.0f * sr6) / (norm_rij * norm_rij);
    
    return r_ij * (-force_magnitude);
}


Vecteur Univers::calcForceInteractionGrav(Cellule& c_i, Cellule& c_j, int i, int j) {

    Particule& pi = c_i.particules[i];
    Particule& pj = c_j.particules[j];

    Vecteur r_ij = pj.getPosition() - pi.getPosition();;
    float norm_rij = r_ij.norm();

    if (norm_rij == 0.0f) 
        return Vecteur(0.0f,0.0f,0.0f);
    
    return r_ij * (pi.getMasse() * pj.getMasse()) / (norm_rij*norm_rij*norm_rij) ;
}


void Univers::calcCellForces(Cellule& cell) {

    for (size_t i = 0; i < cell.particules.size(); i++) { //Pour toute les particules de cell
        
        //On reset la force i
        cell.particules[i].force.x = 0.0f; cell.particules[i].force.y = 0.0f; cell.particules[i].force.z = 0.0f;
        
        for(Cellule* cellNeigh : cell.voisins) { //Pour toutes les cellules voisines

            if ((cellNeigh->position - cell.particules[i].getPosition()).norm() > rcut) 
                continue;

            for (size_t j = 0; j < cellNeigh->particules.size(); j++) {  //Pour toute les particules des cellules voisines

                if (cell.particules[i].getId() == cellNeigh->particules[j].getId()) continue;

                //Calcul de la force entre p_i et ses voisines p_j
                cell.particules[i].force += calcForceInteractionPot(cell, *cellNeigh, i, j);
                                            
            }
        }
    }
}


void Univers::printCells() {
    for (size_t c = 0; c < cellules.size(); c++) {
        for (size_t i = 0; i < cellules[c].particules.size(); i++) {
            std::cout << cellules[c].particules[i].getId() << ":" << cellules[c].particules[i].getPosition() << std::endl;
        }
    }
    std::cout << std::endl;
}


//Algorithme de Stromer-Verlet
void Univers::StromerVerlet(float t_end, float delta_t) {

    float t = 0.0f;

    //On calcul les forces initiales des particules
    for (size_t c = 0; c < cellules.size(); c++) 
        calcCellForces(cellules[c]);
    
    //VTKWriter::write("p.vtk", *this);

    while (t < t_end) {

        //printCells();
        
        //Calcul des positions
        for (size_t c = 0; c < cellules.size(); c++) {
            for (size_t i = 0; i < cellules[c].particules.size(); i++) {

                cellules[c].particules[i].force_old = cellules[c].particules[i].force;

                Particule p = cellules[c].particules[i];
                Vecteur newPosition = p.getPosition() + delta_t*(p.getVitesse() + .5f/p.getMasse()*cellules[c].particules[i].force_old*delta_t);
                cellules[c].particules[i].setPosition(newPosition);
                
            }
        }

        //Calcul des vitesses
        for (size_t c = 0; c < cellules.size(); c++) {

            calcCellForces(cellules[c]);

            for (size_t i = 0; i < cellules[c].particules.size(); i++) {

                Particule &p = cellules[c].particules[i];
                Vecteur newVitesse = p.getVitesse() + delta_t*.5f/p.getMasse()*(cellules[c].particules[i].force + cellules[c].particules[i].force_old);
                cellules[c].particules[i].setVitesse(newVitesse);
            }
        }

        

        //Update des cellules des particules
        for (size_t c = 0; c < cellules.size(); c++) {
            //On parcours à l'envers pour éviter les décalages
            for (size_t i = cellules[c].particules.size(); i-- > 0; ) { 
                updateCellPart(c, i);
            }
        }

        
        t += delta_t;
    }
}
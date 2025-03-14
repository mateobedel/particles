#pragma once

#include <string>
#include <vector>
#include <random>

#include "Vecteur.hxx"
#include "Particule.hxx"


struct Cellule {
    std::vector<Particule> particules;
    std::vector<Cellule*> voisins;
};

class Univers {

    private:

        //Constantes de l'univers
        const float epsilon = 1.0f;
        const float sigma = 1.0f;

        //Caractéristiqu de l'univers
        int dimension;
        Vecteur Ld; //Longueur caractéristique
        float rcut; //Rayon de coupe
        int ncd_x, ncd_y, ncd_z;
        int nb_particules;

        std::vector<Cellule> cellules;

        //Mersenne twister
        std::mt19937 mt;

    public:

        Univers(int n, int nb_p, Vecteur l, float r);

        //Calcule la force d'interaction gravitationelle (0 si i et j sont superposées)
        Vecteur calcForceInteractionGrav(Cellule& c_i, Cellule& c_j, int id_i, int id_j);

        //Calcule la force de potentiel (0 si i et j sont superposées)
        Vecteur calcForceInteractionPot(Cellule& c_i, Cellule& c_j, int i, int j);

        //Calcule les forces de toute les particules
        void calcAllForces(std::vector<Vecteur>& forces, Cellule& cell);

        //Algorithme de Stromer-Verlet
        void StromerVerlet(float t_end, float delta_t);
    
        int getCellLinearIndex(int x, int y, int z);

        void addParticule(Particule& p);

        void removeParticule(int cellInd, Particule& p);

        void setupVoisin();

        void updateCellulePart(int c, int i);
    
};
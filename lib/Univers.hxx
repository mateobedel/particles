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

        int dimension;
        Vecteur Ld; //Longueur caractéristique
        float rcut; //Rayon de coupe

        int nb_particules;
        std::vector<Particule> particules;

        //Mersenne twister
        std::mt19937 mt;

    public:

        Univers(int n, int nb_p, Vecteur l, float r);

        //Calcule la force d'interaction gravitationelle (0 si i et j sont superposées)
        Vecteur calcForceInteractionGrav(int id_i, int id_j);

        //Calcule le potentiel de Lennard-Jones entre deux particules
        float calcPotLennardJones(int i, int j);

        //Calcule les forces gravitationelles de toute les particules
        void calcAllForcesGrav(std::vector<Vecteur>& forces);

        //Algorithme de Stromer-Verlet
        void StromerVerlet(float t_end, float delta_t);
    

    
};
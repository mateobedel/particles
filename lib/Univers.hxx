#pragma once

#include <string>
#include <vector>
#include <random>

#include "Vecteur.hxx"
#include "Particule.hxx"

class Univers {

    private:
        int dimension;
        int nb_particules;
        std::vector<Particule> particules;

    public:

        Univers(int n, int nb_p);

        //Calcule la force d'interaction gravitationelle (0 si i et j sont superposées)
        Vecteur calcForceInteraction(int id_i, int id_j);

        //Calcule la force d'une particule
        Vecteur calcForce(int id);

        //Algorithme de Stromer-Verlet
        void StromerVerlet(float t_end, float delta_t);
    

    
};
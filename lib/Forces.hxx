#pragma once

#include "Vecteur.hxx"
#include "Particule.hxx"

class Forces {
    
    public:

        static Vecteur calcForceInteractionPot(int i, int j, std::vector<Particule>& particules, float sigma6, float epsilon);

        static Vecteur calcForceInteractionGrav(int i, int j, std::vector<Particule>& particules);

        static Vecteur calcForceReflexion(int i, std::vector<Particule>& particules, float sigma, float epsilon, Vecteur fLd, int dimension);

        static float calcPotentielReflexion(float r, float sigma, float epsilon);

        static float calcPotentielGravitationnel(float m, float G);

};
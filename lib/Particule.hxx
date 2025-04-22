#pragma once

#include <string>
#include <vector>
#include "Vecteur.hxx"

class Particule {
    private:
        float masse; 
        Vecteur position;          
        Vecteur vitesse;
        int id;

        std::string categorie;    
    public:

        Vecteur force;
        Vecteur force_old;

        Particule(float m, Vecteur pos, Vecteur vit) : 
        masse(m),  position(pos), vitesse(vit) {
            static int glob_id = 0;
            id = glob_id++;
        };

        float getMasse() const { return masse; }
        const Vecteur& getPosition() const { return position; }
        const Vecteur& getVitesse() const { return vitesse; }
        int getId() const {return id;}
        void setPosition(const Vecteur& newPos) { position = newPos; }
        void setVitesse(const Vecteur& newVit) { vitesse = newVit; }
    
};
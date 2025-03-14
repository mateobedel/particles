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

        Vecteur force;
        std::string categorie;    
    public:
        Particule(float m, Vecteur pos, Vecteur vit) : 
        masse(m),  position(pos), vitesse(vit) {
            static int glob_id = 0;
            id = glob_id++;
        };

        float getMasse() { return masse; }
        Vecteur& getPosition() { return position; }
        Vecteur& getVitesse() { return vitesse; }
        int getId() const {return id;}
        void setPosition(const Vecteur& newPos) { position = newPos; }
        void setVitesse(const Vecteur& newVit) { vitesse = newVit; }
    
};
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
        Particule() = default;
        Particule(float m, Vecteur pos, Vecteur vit) : 
        masse(m),  position(pos), vitesse(vit) {};

        float getMasse() { return masse; }
        Vecteur getPosition() { return position; }
        Vecteur getVitesse() { return vitesse; }
        void setPosition(const Vecteur& newPos) { position = newPos; }
        void setVitesse(const Vecteur& newVit) { vitesse = newVit; }
    
};
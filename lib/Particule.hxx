#pragma once

#include <string>
#include <vector>
#include "Vecteur.hxx"

class Particule {
    private:
        float masse; 
        Vecteur position;          
        Vecteur vitesse;
        std::string identifiant;

        Vecteur force;
        std::string categorie;    
    public:
        Particule() = default;

        Particule(float m, Vecteur pos, Vecteur vit, std::string id) : 
        masse(m),  position(pos), vitesse(vit), identifiant(id) {};

        float getMasse() { return masse; }
        std::string getIdentifiant() { return identifiant; }
        Vecteur getPosition() { return position; }
        Vecteur getVitesse() { return vitesse; }
        void setPosition(const Vecteur& newPos) { position = newPos; }
        void setVitesse(const Vecteur& newVit) { vitesse = newVit; }
    
};
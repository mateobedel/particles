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
        Vecteur force_old; 

    public:

        Particule(float m, Vecteur pos, Vecteur vit) : 
        masse(m),  position(pos), vitesse(vit) {
            static int glob_id = 0;
            id = glob_id++;
        };

        float getMasse() const { return masse; }
        const Vecteur& getPosition() const { return position; }
        const Vecteur& getVitesse() const { return vitesse; }
        int getId() const {return id;}
        const Vecteur& getForce() const { return force; }
        const Vecteur& getForceOld() const { return force_old; }

        void setPosition(const Vecteur& newPos) { position = newPos; }
        void setVitesse(const Vecteur& newVit) { vitesse = newVit; }
        void setForce(const Vecteur& newForce) { force = newForce; }
        void setForceOld(const Vecteur& newForceOld) { force_old = newForceOld; }

        void addForce(const Vecteur& f) {force += f;}
        void subForce(const Vecteur& f) {force -= f;}
    
};
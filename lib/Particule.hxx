#pragma once

#include <string>
#include <vector>
#include "Vecteur.hxx"


/**
 * @class Particule
 * @brief Représente une particule avec des propriétés physiques.
 * 
 * Cette classe contient les propriétés d'une particule, comme sa masse, sa position, 
 * sa vitesse et ses forces appliquées.
 */
class Particule {

    private:
        float masse;          ///< Masse de la particule
        Vecteur position;     ///< Position de la particule
        Vecteur vitesse;      ///< Vitesse de la particule
        int id;               ///< Identifiant unique de la particule
        Vecteur force;        ///< Force actuelle appliquée sur la particule
        Vecteur force_old;    ///< Force précédente appliquée sur la particule 

    public:

        /**
         * @brief Constructeur de la particule.
         * 
         * Initialise une particule avec une masse, une position et une vitesse.
         * @param m Masse de la particule.
         * @param pos Position initiale de la particule.
         * @param vit Vitesse initiale de la particule.
         */
        Particule(float m, Vecteur pos, Vecteur vit) : masse(m),  position(pos), vitesse(vit) {
            static int glob_id = 0;
            id = glob_id++;
        };

        /**
         * @brief Retourne la masse de la particule.
         * @return La masse de la particule.
         */
        float getMasse() const { return masse; }

        /**
         * @brief Retourne la position de la particule.
         * @return La position de la particule.
         */
        const Vecteur& getPosition() const { return position; }

        /**
        * @brief Retourne la vitesse de la particule.
        * @return La vitesse de la particule.
        */
        const Vecteur& getVitesse() const { return vitesse; }

        /**
         * @brief Retourne l'identifiant unique de la particule.
         * @return L'identifiant de la particule.
         */
        int getId() const {return id;}

        /**
         * @brief Retourne la force actuelle appliquée à la particule.
         * @return La force actuelle de la particule.
         */
        const Vecteur& getForce() const { return force; }

        /**
         * @brief Retourne la force précédente appliquée à la particule.
         * @return La force précédente de la particule.
         */
        const Vecteur& getForceOld() const { return force_old; }

        /**
         * @brief Met à jour la position de la particule.
         * @param newPos La nouvelle position.
         */
        void setPosition(const Vecteur& newPos) { position = newPos; }

        /**
         * @brief Met à jour la vitesse de la particule.
         * @param newVit La nouvelle vitesse.
         */
        void setVitesse(const Vecteur& newVit) { vitesse = newVit; }

        /**
         * @brief Met à jour la force appliquée à la particule.
         * @param newForce La nouvelle force.
         */
        void setForce(const Vecteur& newForce) { force = newForce; }

        /**
         * @brief Met à jour la force précédente appliquée à la particule.
         * @param newForceOld La nouvelle force précédente.
         */
        void setForceOld(const Vecteur& newForceOld) { force_old = newForceOld; }
        
        /**
         * @brief Ajoute une force à la force actuelle de la particule.
         * @param f La force à ajouter.
         */
        void addForce(const Vecteur& f) {force += f;}

        /**
         * @brief Soustrait une force de la force actuelle de la particule.
         * @param f La force à soustraire.
         */
        void subForce(const Vecteur& f) {force -= f;}
    
};
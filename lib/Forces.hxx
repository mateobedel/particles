#pragma once

#include "Vecteur.hxx"
#include "Particule.hxx"


/**
 * @class Forces
 * @brief Classe qui regroupe des méthodes statiques pour calculer les forces et potentiels
 *        entre particules.
 
 */
class Forces {
    
    public:

        /**
         * @brief Calcule la force d'interaction potentielle entre deux particules.
         * 
         * Cette méthode calcule la force d'interaction potentielle entre les particules `i` et `j`
         * en utilisant le potentiel de Lennard-Jones.
         * 
         * @param i L'indice de la première particule dans le vecteur des particules.
         * @param j L'indice de la deuxième particule dans le vecteur des particules.
         * @param particules Vecteur de toutes les particules utilisées pour calculer l'interaction.
         * @param sigma6 constante de l'univers précalculé à la puissance 6.
         * @param epsilon contstante de l'univers.
         * @return La force d'interaction entre les deux particules sous forme de vecteur.
         */
        static Vecteur calcForceInteractionPot(int i, int j, std::vector<Particule>& particules, float sigma6, float epsilon);


        /**
         * @brief Calcule la force d'interaction gravitationnelle entre deux particules.
         * 
         * Cette méthode calcule la force gravitationnelle entre les particules `i` et `j` en
         * utilisant la loi de la gravitation universelle.
         * 
         * @param i L'indice de la première particule dans le vecteur des particules.
         * @param j L'indice de la deuxième particule dans le vecteur des particules.
         * @param particules Vecteur de toutes les particules utilisées pour calculer l'interaction.
         * @return La force gravitationnelle entre les deux particules sous forme de vecteur.
         */
        static Vecteur calcForceInteractionGrav(int i, int j, std::vector<Particule>& particules);


         /**
         * @brief Calcule la force de réflexion d'une particule sur une paroi.
         * 
         * Cette méthode calcule la force de réflexion qu'une particule `i` subit en se heurtant à
         * une paroi d'après un potentiel définit dans calcPotentielReflexion.
         * 
         * @param i L'indice de la particule dans le vecteur des particules.
         * @param particules Un vecteur de toutes les particules utilisées pour calculer l'interaction.
         * @param sigma Constante de l'univers.
         * @param epsilon Constante de l'univers.
         * @param fLd Distance caractéristiques de l'univers tronquée.
         * @param dimension Dimension de l'univers.
         * @return La force de réflexion sous forme de vecteur.
         */
        static Vecteur calcForceReflexion(int i, std::vector<Particule>& particules, float sigma, float epsilon, Vecteur fLd, int dimension);


        /**
         * @brief Calcule le potentiel de réflexion en fonction de la distance r.
         * 
         * Cette méthode calcule le potentiel de réflexion en fonction de la distance entre la particule
         * et la paroi.
         * 
         * @param r La distance entre la particule et la paroi.
         * @param sigma Constante de l'univers.
         * @param epsilon Constante de l'univers.
         * @return Le potentiel de réflexion.
         */
        static float calcPotentielReflexion(float r, float sigma, float epsilon);


        /**
         * @brief Calcule le potentiel gravitationnel d'une particule en fonction de sa masse.
         * 
         * Cette méthode calcule le potentiel gravitationnel d'une particule en utilisant sa masse et
         * la constante gravitationnelle.
         * 
         * @param m La masse de la particule.
         * @param G La constante gravitationnelle.
         * @return Le potentiel gravitationnel de la particule.
         */
        static float calcPotentielGravitationnel(float m, float G);

};
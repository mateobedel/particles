#pragma once

#include <string>
#include <vector>
#include <random>

#include "Vecteur.hxx"
#include "Particule.hxx"

//Type de conditions aux limites
#define BOUND_REFLEXION 0   ///< Condition de réflexion
#define BOUND_ABSORPTION 1  ///< Condition d'absorption
#define BOUND_PERIODIC 2    ///< Condition périodique

/**
 * @struct Cellule
 * @brief Représente une cellule de l'univers contenant des particules et des voisins.
 */
struct Cellule {
    std::vector<uint> partInd;
    std::vector<Cellule*> voisins;
    Vecteur position;
};


/**
 * @class Univers
 * @brief Représente l'univers dans lequel les particules évoluent avec des conditions aux limites.
 * 
 * Cette classe gère l'évolution des particules, la gestion des cellules et les forces dans l'univers,
 * et applique un algorithme de dynamique des particules.
 */
class Univers {

    private:

        float epsilon; ///< Constante epsilon de l'univers
        float sigma, sigma6; ///< Constantes sigma et sigma^6
        float G; ///< Constante gravitationnelle
        int boundary_condition; ///< Condition aux limites


        int dimension; ///< Dimension de l'univers
        Vecteur Ld; ///< Longueur de l'univers
        Vecteur fLd; ///< Longueur tronquée de l'univers
        float rcut; ///< Rayon de coupe (longueur caractéristique)
        int ncd_x, ncd_y, ncd_z; ///< Nombre de cellules dans chaque direction

        std::vector<Particule> particules;  ///< Liste des particules
        std::vector<Cellule> cellules;      ///< Liste des cellules


    public:

        /**
         * @brief Constructeur de l'univers.
         * 
         * Initialise l'univers avec des particules et des paramètres physiques.
         * @param n Dimension de l'univers.
         * @param l Longueur de l'univers.
         * @param r Rayon de coupe.
         * @param eps Constante epsilon.
         * @param sigm Constante sigma.
         * @param grav Constante gravitationnelle G.
         * @param b_cond Condition aux limites (BOUND_*).
         */
        Univers(int n, Vecteur l, float r, float eps, float sigm, float grav, int b_cond);

        /**
         * @brief Calcule toutes les forces de toutes les particules.
         */
        void calcForces();

        /**
         * @brief Algorithme de Stromer-Verlet pour la mise à jour des positions et vitesses.
         * @param t_end Temps final de la simulation.
         * @param delta_t Pas de temps.
         */
        void StromerVerlet(float t_end, float delta_t);
    
        /**
         * @brief Calcul l'index linéaire d'une cellule en fonction de ses indices 3D/2D/1D.
         * 
         * La fonction ne vérifie pas que les indices soit valide.
         * 
         * @param x Index X.
         * @param y Index Y.
         * @param z Index Z.
         * @return L'index linéaire de la cellule.
         */
        int getCellLinearIndex(int x, int y, int z) const;

        /**
         * @brief Ajoute une particule à la cellule appropriée.
         * @param p La particule à ajouter.
         */
        void addParticle(Particule& p);

        /**
         * @brief Initialise les voisins de chaque cellule et mets à jour la position des cellules.
         */
        void setupNeighbours();

        /**
         * @brief Mets à jour la cellule associée à une particule.
         * @param c Indice de la cellule.
         * @param ind_p Indice de la liste d'indices de c de la paricule.
         */
        void updateCellPart(int c, int ind_p);

        /**
         * @brief Vérifie si une position est en dehors des limites de l'univers.
         * @param v La position à vérifier.
         * @return True si la position est hors limites, sinon false.
         */
        bool isPositionOut(const Vecteur& v) const;


        /**
         * @brief Gère les conditions aux limites pour une particule et lui assigne une position en fonction.
         * @param p La particule.
         * @param calcPos La position à verifier.
         * @param c La cellule.
         * @param ind_p Indice de la liste d'indices de c de la particule.
         * @param boundary_condition Le type de condition aux limites.
         */
        void HandleBoundaryConditions(Particule& p, Vecteur& calcPos, int c, int ind_p, int boundary_condition);

        /**
         * @brief Affiche la position de toutes les particules.
         */ 
        void printParticules();

        /**
         * @brief Retourne le nombre total de particules dans les cellules.
         * @return Le nombre de particules.
         */
        int getNbParticule() const {
            int somme = 0;
            for(auto& c : cellules) somme += c.partInd.size();
            return somme;
        };
        
        /**
         * @brief Retourne la dimension de l'univers.
         * @return La dimension.
         */
        int getDimension() const {return dimension;};

        /**
         * @brief Retourne la liste des cellules de l'univers.
         * @return Les cellules.
         */
        const std::vector<Cellule>& getCellules() const {return cellules;};

        /**
         * @brief Retourne la liste des particules de l'univers.
         * @return Les particules.
         */
        const std::vector<Particule>& getParticules() const {return particules;};
};
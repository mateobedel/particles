#pragma once

#include <string>
#include <vector>
#include <random>

#include "Vecteur.hxx"
#include "Particule.hxx"

//Type de conditions aux limites
#define BOUND_REFLEXION 0
#define BOUND_ABSORPTION 1
#define BOUND_PERIODIC 2

struct Cellule {
    std::vector<uint> partInd;
    std::vector<Cellule*> voisins;
    Vecteur position;
};

class Univers {

    private:

        //Constantes de l'univers
        float epsilon;
        float sigma, sigma6;
        float G;
        int boundary_condition;

        //Caractéristiqu de l'univers
        int dimension;
        Vecteur Ld; //Longueur caractéristique
        Vecteur fLd; //Longueur caractéristique tronquée
        float rcut; //Rayon de coupe
        int ncd_x, ncd_y, ncd_z;
        
        int nb_particules;

        std::vector<Particule> particules;
        std::vector<Cellule> cellules;

    public:

        Univers(int n, int nb_p, Vecteur l, float r, float eps, float sigm, float grav, int b_cond);

        //Calcule les forces de toute les particules de la cellule cell
        void calcForces();

        //Algorithme de Stromer-Verlet
        void StromerVerlet(float t_end, float delta_t);
    
        //Calcul l'index linéaire d'une cellule en fonction de ses index 3D (ou 2D ou 1D)
        int getCellLinearIndex(int x, int y, int z) const;

        //Ajoute une particule à la bonne cellule
        void addParticle(Particule& p);

        //Initialise les voisins de chaques cellules
        void setupNeighbours();

        //Mets à jour la bonne cellule en fonction de l'indice de la liste d'indices des particules
        void updateCellPart(int c, int ind_p);

        bool isPositionOut(const Vecteur& v) const;

        void HandleBoundaryConditions(Particule& p, Vecteur& calcPos, int c, int ind_p, int boundary_condition);

        //Affiche toute les particules 
        void printParticules();


        int getNbParticule() const {
            int somme = 0;
            for(auto& c : cellules) somme += c.partInd.size();
            return somme;
        };
        
        int getDimension() const {return dimension;};

        const std::vector<Cellule>& getCellules() const {return cellules;};

        const std::vector<Particule>& getParticules() const {return particules;};
};
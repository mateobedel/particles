#pragma once

#include <string>
#include <vector>
#include <random>

#include "Vecteur.hxx"
#include "Particule.hxx"


struct Cellule {
    std::vector<Particule> particules;
    std::vector<Cellule*> voisins;
    Vecteur position;
};

class Univers {

    private:

        //Constantes de l'univers
        float epsilon;
        float sigma;

        //Caractéristiqu de l'univers
        int dimension;
        Vecteur Ld; //Longueur caractéristique
        float rcut; //Rayon de coupe
        int ncd_x, ncd_y, ncd_z;
        int nb_particules;

        std::vector<Cellule> cellules;

        //Mersenne twister
        std::mt19937 mt;

    public:

        Univers(int n, int nb_p, Vecteur l, float r, float eps, float sigm);

        //Calcule la force d'interaction gravitationelle (0 si i et j sont superposées)
        Vecteur calcForceInteractionGrav(Cellule& c_i, Cellule& c_j, int id_i, int id_j);

        //Calcule la force de potentiel (0 si i et j sont superposées)
        Vecteur calcForceInteractionPot(Cellule& c_i, Cellule& c_j, int i, int j);

        //Calcule les forces de toute les particules de la cellule cell
        void calcCellForces(Cellule& cell);

        //Algorithme de Stromer-Verlet
        void StromerVerlet(float t_end, float delta_t);
    
        //Calcul l'index linéaire d'une cellule en fonction de ses index 3D (ou 2D ou 1D)
        int getCellLinearIndex(int x, int y, int z);

        //Ajoute une particule à la bonne cellule
        void addParticle(Particule& p);

        //Initialise les voisins de chaques cellules
        void setupNeighbours();

        //Mets à jour la bonne cellule en fonction de la position d'une particule i
        void updateCellPart(int c, int i);

        //Affiche toute les particules de toute les cellules (id:Position)
        void printCells();
    
};
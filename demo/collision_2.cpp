
#include "Univers.hxx"
#include "VTKWriter.hxx"

#include <iostream>

int main(int argc, char* argv[]) {

    //Paramètres
    float sigma = 1.0f;
    float epsilon = 1.0f;
    float G = -12.0f;

    //Lecture des arguments
    int nb_vtk = VTKWriter::readVTKNumber(argc, argv);

    //Initialisation de l'univers
    Univers univ = Univers(2, Vecteur(250.0f,180.0f,0.0f), 2.5*sigma, epsilon, sigma, G, BOUND_ABSORPTION, nb_vtk);

    //Sol 
    for(int i = 0; i < 250; i++) {
        for(int j = 0; j < 70; j++) {
            float ecart = 1.0f;
            float start_x = 0.0f;
            float start_y = 0.0f;
            Particule p = Particule(1, Vecteur(start_x+ecart*(float)(i),start_y+ecart*(float)j,0), Vecteur(0,0,0));
            univ.addParticle(p);
        }
    }

    //Sphere
    for(int i = 0; i < 70; i++) {
        for(int j = 0; j < 70; j++) {
            float ecart = 1.0f;
            float start_x = 90.0f;
            float start_y = 90.0f;
            if ((i-35)*(i-35) + (j-35)*(j-35) < 35*35) {
                Particule p = Particule(1, Vecteur(start_x+ecart*(float)(i),start_y+ecart*(float)j,0), Vecteur(0,-15,0));
                univ.addParticle(p);
            }
        }
    }

    //Simulation
    univ.StromerVerlet(10.0f,0.0005f);

    return 0;
}


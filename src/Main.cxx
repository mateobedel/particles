
#include "Univers.hxx"
#include "VTKWriter.hxx"

#include <iostream>

int main(int argc, char* argv[]) {

    float sigma = 1.0f;
    float epsilon = 5.0f;
    float G = -12.0f;



    int nb_vtk = VTKWriter::readVTKNumber(argc, argv);
    Univers univ = Univers(2, Vecteur(250.0f,100.0f,0.0f), 2.5*sigma, epsilon, sigma, G, BOUND_ABSORPTION, nb_vtk);

    //Système solaire
    // Particule soleil = Particule(1,        10+Vecteur(0,0,0),    Vecteur(0,0,0));
    // Particule terre = Particule(3.0e-6,    10+Vecteur(0,1,0),    Vecteur(-1,0,0));
    // Particule jupiter = Particule(9.55e-4, 10+Vecteur(0,5.36,0), Vecteur(-0.425, 0, 0));
    // addParticle(soleil);
    // addParticle(terre);
    // addParticle(jupiter);

    //Simulation TP4
    //Carré rouge
    for(int i = 0; i < 40; i++) {
        for(int j = 0; j < 40; j++) {
            float ecart = 1.12246204831/sigma;
            float start_x = 100.0f;
            Particule p = Particule(1, Vecteur(start_x+ecart*i,ecart*j,0), Vecteur(0,10,0));
            univ.addParticle(p);
        }
    }

    //Rectangle bleu
    for(int i = 0; i < 160; i++) {
        for(int j = 0; j < 40; j++) {
            float ecart = 1.12246204831/sigma;
            float start_x = 50.0f;
            float start_y = 50.0f;
            Particule p = Particule(1, Vecteur(start_x+ecart*(float)(i),start_y+ecart*(float)j,0), Vecteur(0,0,0));
            univ.addParticle(p);
        }
    }


    // //Simulation TP6
    // //Sol 
    // for(int i = 0; i < 250; i++) {
    //     for(int j = 0; j < 70; j++) {
    //         float ecart = 1.0f;
    //         float start_x = 0.0f;
    //         float start_y = 0.0f;
    //         Particule p = Particule(1, Vecteur(start_x+ecart*(float)(i),start_y+ecart*(float)j,0), Vecteur(0,10,0));
    //         univ.addParticle(p);
    //     }
    // }

    // //Sphere
    // for(int i = 0; i < 70; i++) {
    //     for(int j = 0; j < 70; j++) {
    //         float ecart = 1.0f;
    //         float start_x = 90.0f;
    //         float start_y = 90.0f;
    //         if ((i-35)*(i-35) + (j-35)*(j-35) < 35*35) {
    //             Particule p = Particule(1, Vecteur(start_x+ecart*(float)(i),start_y+ecart*(float)j,0), Vecteur(0,-10,0));
    //             univ.addParticle(p);
    //         }
    //     }
    // }

    univ.StromerVerlet(19.5f,0.05f);

    return 0;
}


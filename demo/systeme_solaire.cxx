#include "Vecteur.hxx"
#include "Univers.hxx"
#include "Particule.hxx"
#include "VTKWriter.hxx"


int main(int argc, char* argv[]) {

     //Paramètres
    float sigma = 0.0f;
    float epsilon = 0.0f;
    float G = 0.0f;

    //Lecture des arguments
    int nb_vtk = VTKWriter::readVTKNumber(argc, argv);

    //Initialisation de l'univers
    Univers u = Univers(2, Vecteur(80.0f,80.0f,0.0f), 80.0f, epsilon, sigma, G, BOUND_ABSORPTION, nb_vtk);


    // Système solaire simplifié (unité de distance centrée à 40, masses réduites)
    Particule soleil = Particule(1,        Vecteur(40, 40, 0),    Vecteur(0, 0, 0));
    Particule terre  = Particule(3.0e-6,   Vecteur(40+0, 40+1, 0),    Vecteur(-1, 0, 0));
    Particule jupiter= Particule(9.55e-4,  Vecteur(40+0, 40+5.36, 0), Vecteur(-0.425, 0, 0));
    Particule haley  = Particule(1e-14,    Vecteur(40+34.75, 40+0, 0),Vecteur(0, 0.0296, 0));

    u.addParticle(soleil);
    u.addParticle(terre);
    u.addParticle(jupiter); 
    u.addParticle(haley);

    //Simulation
    u.StromerVerlet(100.0f,0.50f);

    return 0;
}
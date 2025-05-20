#include "Univers.hxx"
#include "Particule.hxx"
#include "VTKWriter.hxx"

int main(int argc, char* argv[]) {

    float sigma = 1.0f;
    float epsilon = 5.0f;
    float G = 0.0f;

    int nb_vtk = VTKWriter::readVTKNumber(argc, argv);

    // Univers 2D,  taille 250x100
    Univers univ = Univers(2, Vecteur(250.0f, 100.0f, 0.0f), 2.5f, epsilon, sigma, G, BOUND_ABSORPTION, nb_vtk);


    // Ajout du carré rouge
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            float ecart = 1.12246204831 / sigma;
            float start_x = 100.0f;
            Particule p(1.0f, Vecteur(start_x + ecart * i, ecart * j, 0), Vecteur(0, 10, 0));
            univ.addParticle(p);
        }
    }

    // Ajout du rectangle bleu
    for (int i = 0; i < 160; i++) {
        for (int j = 0; j < 40; j++) {
            float ecart = 1.12246204831 / sigma;
            float start_x = 50.0f;
            float start_y = 50.0f;
            Particule p(1.0f, Vecteur(start_x + ecart * i, start_y + ecart * j, 0), Vecteur(0, 0, 0));
            univ.addParticle(p);
        }
    }


    // Simulation
    univ.StromerVerlet(2.0f, 0.01f); 

    return 0;

}
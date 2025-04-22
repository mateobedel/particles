
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "Univers.hxx"


int main() {

    float sigma = 1.0f;
    float epsilon = 5.0f;

    Univers univ = Univers(2, 10000, Vecteur(250.0f,100.0f,0.0f), 2.5, epsilon, sigma, BOUND_PERIODIC);

    // //Distribution aléatoire uniforme sur [0,1]
    // std::random_device rd;
    // std::mt19937 mt(rd());
    // std::uniform_real_distribution<float> dist(0.0, 1.0);


    // //Generation aléatoire des particules
    // for (int i = 0; i < nb_particules; i++) {
    //     float masse = 1.0f;
    //     Vecteur rdmPos = Vecteur(
    //         dist(mt)*Ld.x, 
    //         dimension>1 ? dist(mt)*Ld.y : 0.0f,
    //         dimension>2 ? dist(mt)*Ld.z : 0.0f
    //     );
    //     Vecteur vit = Vecteur(0.0f, 0.0f, 0.0f);
    //     Particule p = Particule(masse, rdmPos, vit);
    //     addParticle(p);
    // }

    //Système solaire
    // Particule soleil = Particule(1,        10+Vecteur(0,0,0),    Vecteur(0,0,0));
    // Particule terre = Particule(3.0e-6,    10+Vecteur(0,1,0),    Vecteur(-1,0,0));
    // Particule jupiter = Particule(9.55e-4, 10+Vecteur(0,5.36,0), Vecteur(-0.425, 0, 0));
    // addParticle(soleil);
    // addParticle(terre);
    // addParticle(jupiter);

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

    univ.StromerVerlet(4.0f,0.01f);

    return 0;
}


#include "Vecteur.hxx"
#include "Univers.hxx"
#include "Particule.hxx"
#include <gtest/gtest.h>

TEST(UniversTest, CollisionGroupesParticules) {
    float sigma = 1.0f;
    float epsilon = 5.0f;

    // Univers 2D, boîte de taille 250x100, 10000 particules max
    Univers univ = Univers(10000, Vecteur(250.0f, 100.0f, 0.0f), 2.5f, epsilon, sigma, 1.0f, BOUND_REFLEXION);


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

    // Sauvegarde des positions initiales
    std::vector<Vecteur> positions_avant;
    for (const auto& p : univ.getParticules()) {
        positions_avant.push_back(p.getPosition());
    }

    // Simulation
    univ.StromerVerlet(2.0f, 0.01f);  // 2 secondes, pas de 0.01

    // Vérifie que certaines particules ont changé de position
    bool auMoinsUnBouge = false;
    const auto& particles_apres = univ.getParticules();
    for (size_t i = 0; i < positions_avant.size(); ++i) {
        if ((particles_apres[i].getPosition() - positions_avant[i]).norm() > 1e-3) {
            auMoinsUnBouge = true;
            break;
        }
    }

    EXPECT_TRUE(auMoinsUnBouge);  // Il doit y avoir mouvement (interaction)
}

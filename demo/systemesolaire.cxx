#include "Vecteur.hxx"
#include "Univers.hxx"
#include "Particule.hxx"
#include <gtest/gtest.h>


TEST(UniversTest, OrbitesStablesSystemeSolaireSimplifie) {

    Univers u = Univers(2, Vecteur(250.0f,100.0f,0.0f), 2.5, 1.0f, 1.0f, 1, BOUND_REFLEXION);

    // Système solaire simplifié (unité de distance centrée à 10, masses réduites)
    Particule soleil = Particule(1,        10 + Vecteur(0, 0, 0),    Vecteur(0, 0, 0));
    Particule terre  = Particule(3.0e-6,   10 + Vecteur(0, 1, 0),    Vecteur(-1, 0, 0));
    Particule jupiter= Particule(9.55e-4,  10 + Vecteur(0, 5.36, 0), Vecteur(-0.425, 0, 0));
    u.addParticle(soleil);
    u.addParticle(terre);
    u.addParticle(jupiter);

    float dt = 0.01f;
    float t_end = 10.0f;
    std::vector<float> distTerre, distJupiter;

    for (float t = 0; t < t_end; t += dt) {
        u.StromerVerlet(dt, 0.1*dt);
        Vecteur posSoleil = u.getParticules()[0].getPosition();
        Vecteur posTerre  = u.getParticules()[1].getPosition();
        Vecteur posJupiter= u.getParticules()[2].getPosition();
        
        distTerre.push_back((posTerre - posSoleil).norm());
        distJupiter.push_back((posJupiter - posSoleil).norm());
    }

    auto moyenne = [](const std::vector<float>& v) {
        return std::accumulate(v.begin(), v.end(), 0.0f) / v.size();
    };

    float moyenneTerre = moyenne(distTerre);
    float moyenneJupiter = moyenne(distJupiter);

    for (float d : distTerre)
        EXPECT_NEAR(d, moyenneTerre, 0.05); 
    
    for (float d : distJupiter)
        EXPECT_NEAR(d, moyenneJupiter, 0.05);
}
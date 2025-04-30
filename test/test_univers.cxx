#include "Vecteur.hxx"
#include "Univers.hxx"
#include "Particule.hxx"
#include <gtest/gtest.h>

// Teste l'initialisation correcte d'un univers 3D et la création de cellules.
TEST(UniversTest, InitialisationCorrecte3D) {
    Univers u(3, 0, Vecteur(10, 10, 10), 1.0f, 1.0f, 1.0f, 1.0f, BOUND_REFLEXION);
    EXPECT_EQ(u.getDimension(), 3);
    EXPECT_GT(u.getCellules().size(), 0);
}

// Vérifie que la particule est ajoutée dans la bonne cellule.
TEST(UniversTest, AddParticleToCorrectCell) {
    Univers u(2, 0, Vecteur(10, 10, 0), 2.0f, 1.0f, 1.0f, 1.0f, BOUND_REFLEXION);
    Particule p(1.0f, Vecteur(1, 1, 0), Vecteur(0,0,0));
    u.addParticle(p);

    const auto& cells = u.getCellules();
    bool found = false;
    for (const auto& c : cells)
        if (!c.partInd.empty()) found = true;
    
    EXPECT_TRUE(found);
}

// Vérifie que la réflexion sur les bords repositionne correctement une particule hors limite.
TEST(UniversTest, ReflexionBoundary) {
    Univers u(2, 0, Vecteur(10, 10, 0), 1.0f, 1.0f, 1.0f, 1.0f, BOUND_REFLEXION);
    Particule p(1.0f, Vecteur(-1, 5, 0), Vecteur(0,0,0));
    Vecteur pos = p.getPosition();
    u.addParticle(p);
    u.HandleBoundaryConditions(p, pos, 0, 0, BOUND_REFLEXION);
    EXPECT_GE(p.getPosition().x, 0.001f);
}

// Vérifie que les forces calculées entre deux particules sont bien opposées.
TEST(UniversTest, CalcForcesOpposees) {
    Univers u(2, 0, Vecteur(10, 10, 0), 5.0f, 1.0f, 1.0f, 1.0f, BOUND_REFLEXION);
    Particule p1(1.0f, Vecteur(2.5, 2.5, 0), Vecteur(0, 0, 0));
    Particule p2(2.0f, Vecteur(3.0, 2.5, 0), Vecteur(0, 0, 0));
    u.addParticle(p1);
    u.addParticle(p2);

    u.calcForces();

    const auto& partList = u.getParticules();

    Vecteur f1 = partList[0].getForce();
    Vecteur f2 = partList[1].getForce();

    EXPECT_NEAR(f1.x, -f2.x, 1e-4);

}

// Vérifie que Stromer-Verlet déplace effectivement la particule sur une petite étape de temps.
TEST(UniversTest, StromerVerletDeplaceParticules) {
    Univers u(2, 0, Vecteur(10, 10, 0), 5.0f, 1.0f, 1.0f, 1.0f, BOUND_REFLEXION);
    Particule p(1.0f, Vecteur(2,2,0), Vecteur(1,0,0));
    u.addParticle(p);

    Vecteur posAvant = u.getParticules()[0].getPosition();

    u.StromerVerlet(0.01f, 0.001f); 
    Vecteur posApres = u.getParticules()[0].getPosition();

    EXPECT_NE(posAvant.x, posApres.x);
    EXPECT_NEAR(posApres.y, posAvant.y, 1e-4); 
}


TEST(UniversTest, OrbitesStablesSystemeSolaireSimplifie) {

    Univers u = Univers(2, 10000, Vecteur(250.0f,100.0f,0.0f), 2.5, 1.0f, 1.0f, 1, BOUND_REFLEXION);

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

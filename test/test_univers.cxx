#include "Vecteur.hxx"
#include "Univers.hxx"
#include "Particule.hxx"
#include <gtest/gtest.h>

// Teste l'initialisation correcte d'un univers 3D et la création de cellules.
TEST(UniversTest, InitialisationCorrecte3D) {
    Univers u(3, Vecteur(10, 10, 10), 1.0f, 1.0f, 1.0f, 1.0f, BOUND_REFLEXION);
    EXPECT_EQ(u.getDimension(), 3);
    EXPECT_GT(u.getCellules().size(), 0);
}

// Vérifie que la particule est ajoutée dans la bonne cellule.
TEST(UniversTest, AddParticleToCorrectCell) {
    Univers u(2, Vecteur(10, 10, 0), 2.0f, 1.0f, 1.0f, 1.0f, BOUND_REFLEXION);
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
    Univers u(2, Vecteur(10, 10, 0), 1.0f, 1.0f, 1.0f, 1.0f, BOUND_REFLEXION);
    Particule p(1.0f, Vecteur(-1, 5, 0), Vecteur(0,0,0));
    Vecteur pos = p.getPosition();
    u.addParticle(p);
    u.HandleBoundaryConditions(p, pos, 0, 0, BOUND_REFLEXION);
    EXPECT_GE(p.getPosition().x, 0.001f);
}

// Vérifie que les forces calculées entre deux particules sont bien opposées.
TEST(UniversTest, CalcForcesOpposees) {
    Univers u(2,  Vecteur(10, 10, 0), 5.0f, 1.0f, 1.0f, 1.0f, BOUND_REFLEXION);
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
    Univers u(2, Vecteur(10, 10, 0), 5.0f, 1.0f, 1.0f, 1.0f, BOUND_REFLEXION);
    Particule p(1.0f, Vecteur(2,2,0), Vecteur(1,0,0));
    u.addParticle(p);

    Vecteur posAvant = u.getParticules()[0].getPosition();

    u.StromerVerlet(0.01f, 0.001f); 
    Vecteur posApres = u.getParticules()[0].getPosition();

    EXPECT_NE(posAvant.x, posApres.x);
    EXPECT_NEAR(posApres.y, posAvant.y, 1e-4); 
}




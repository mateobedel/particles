#include <set>
#include <list>
#include <string>
#include <deque>
#include <vector>
#include <unordered_map>
#include <random>
#include <iostream>

#include "Particule.hxx"
#include "Vecteur.hxx"


//Calcule la force d'interaction gravitationelle (0 si i et j sont superposées)
Vecteur calcForceInteraction(std::unordered_map<std::string, Particule>& particules, std::string id_i, std::string id_j) {

    Particule& pi = particules[id_i];
    Particule& pj = particules[id_j];

    Vecteur r_ij = pj.getPosition() - pi.getPosition();;
    float norm_rij = r_ij.norm();
    if (norm_rij == 0.0f) return Vecteur(0,0,0); 

    return r_ij * (pi.getMasse() * pj.getMasse()) / (norm_rij*norm_rij*norm_rij);
}


//Calcule la force d'une particule
Vecteur calcForce(std::string id, std::unordered_map<std::string, Particule>& particules) {

    Vecteur force_total = Vecteur(0,0,0);

    for (auto [i, p] : particules) {
        if (i == id) continue;
        force_total += calcForceInteraction(particules, id, i);
        }
    
    return force_total;
}


//Algorithme de Stromer-Verlet
void StromerVerlet( std::unordered_map<std::string, Particule> &particules, float t_end, float delta_t) {

    float t = 0.0f;

    //Calcul des forces F
    std::unordered_map<std::string, Vecteur> F = {};
    std::unordered_map<std::string, Vecteur> F_old = {};
    for (auto [i,_] : particules) F[i] = calcForce(i, particules);
    
    while (t < t_end) {

        //Position
        for (auto& [i, p] : particules) {
            F_old[i] = F[i]; 
            Vecteur newPosition = p.getPosition() + delta_t*(p.getVitesse() + .5f/p.getMasse()*F_old[i]*delta_t);
            p.setPosition(newPosition);
        }

        //Calcul des forces F
        for (auto& [i,_] : particules) F[i] = calcForce(i, particules);

        //Vitesse
        for (auto& [i,p] : particules) {
            Vecteur newVitesse = p.getVitesse() + delta_t*.5f/p.getMasse()*(F[i] + F_old[i]);
            p.setVitesse(newVitesse);
        }

        //for (auto& [i,p] : particules) std::cout << p.getPosition() << std::endl;

        t += delta_t;
    }
}


int main() {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    //Collection de particules
    std::unordered_map<std::string, Particule> particules;

    particules["soleil"] = Particule(1.0f, Vecteur(0.0f,0.0f,0.0f), Vecteur(0.0f,0.0f,0.0f), "soleil"); 
    particules["terre"] = Particule(3.0e-6, Vecteur(0.0f,1.0f,0.0f), Vecteur(-1.0f,0.0f,0.0f),"terre"); 
    particules["jupiter"] = Particule(9.55e-4, Vecteur(0.0f,5.36f,0.0f), Vecteur(-0.425f,0.0f,0.0f), "jupiter"); 
    particules["haley"] = Particule(1e-14, Vecteur(34.75f,0.0f,0.0f), Vecteur(0.0f,0.0296f,0.0f), "haley"); 

    StromerVerlet(particules, 468.5, 0.015);

    return 0;
}


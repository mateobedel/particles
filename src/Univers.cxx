#include "Univers.hxx"


Univers::Univers(int n, int nb_p) : dimension(n), nb_particules(nb_p) {
            
    //Distribution aléatoire uniforme sur [0,1]
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    //Generation aléatoire des particules
    particules.reserve(nb_p);
    for (int i = 0; i < nb_p; i++) {
        float masse = 1.0f;
        Vecteur rdmPos = Vecteur(dist(mt), n>1 ? dist(mt) : 0.0f, n>2 ? dist(mt) : 0.0f);
        Vecteur vit = Vecteur(0.0f, 0.0f, 0.0f);
        particules.emplace_back(masse, rdmPos, vit);
    }
}


//Calcule la force d'interaction gravitationelle (0 si i et j sont superposées)
Vecteur Univers::calcForceInteraction(int i, int j) {

    Particule& pi = particules[i];
    Particule& pj = particules[j];

    Vecteur r_ij = pj.getPosition() - pi.getPosition();;
    float norm_rij = r_ij.norm();
    if (norm_rij == 0.0f) return Vecteur(0,0,0); 

    return r_ij * (pi.getMasse() * pj.getMasse()) / (norm_rij*norm_rij*norm_rij);
}

//Calcule la force d'une particule
Vecteur Univers::calcForce(int id) {

    Vecteur force_total = Vecteur(0,0,0);

    for (int i = 0; i < particules.size(); i++) {
        if (i == id) continue;
        force_total += calcForceInteraction(id, i);
    }
    
    return force_total;
}

//Algorithme de Stromer-Verlet
void Univers::StromerVerlet(float t_end, float delta_t) {

    float t = 0.0f;
    int n = particules.size();

    //Calcul des forces F
    std::vector<Vecteur> F(n), F_old(n);
    for (int i = 0; i < n; i++) F[i] = calcForce(i);
    
    while (t < t_end) {

        //Position
        for (int i = 0; i < n; i++) {
            F_old[i] = F[i]; 
            Vecteur newPosition = particules[i].getPosition() + delta_t*(particules[i].getVitesse() + .5f/particules[i].getMasse()*F_old[i]*delta_t);
            particules[i].setPosition(newPosition);
        }

        //Calcul des forces F
        for (int i = 0; i < n; i++) F[i] = calcForce(i);

        //Vitesse
        for (int i = 0; i < n; i++) {
            Vecteur newVitesse = particules[i].getVitesse() + delta_t*.5f/particules[i].getMasse()*(F[i] + F_old[i]);
            particules[i].setVitesse(newVitesse);
        }

        t += delta_t;
    }
}
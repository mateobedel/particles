#include "Univers.hxx"


Univers::Univers(int n, int nb_p, Vecteur l, float r){
            
    //Initialisation
    dimension = n;
    nb_particules = nb_p;
    Ld = l;
    rcut = r;

    //Grille des cellules
    Vecteur ncd = (Ld/rcut);
    


    //Distribution aléatoire uniforme sur [0,1]
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    //Generation aléatoire des particules
    particules.reserve(nb_p);
    for (int i = 0; i < nb_p; i++) {
        float masse = 1.0f;
        Vecteur rdmPos = Vecteur(dist(mt), n>1 ? dist(mt) : 0.0f, n>2 ? dist(mt) : 0.0f);
        Vecteur vit = Vecteur(0.0f, 0.0f, 0.0f);
        particules.emplace_back(masse, rdmPos, vit);
    }
}



float Univers::calcPotLennardJones(int i, int j) {

    Particule& pi = particules[i];
    Particule& pj = particules[j];

    Vecteur r_ij = pj.getPosition() - pi.getPosition();
    float norm_rij = r_ij.norm();

    float epsilon = 1.0f;
    float sigma = 1.0f;

    float sr6 = std::pow(sigma/norm_rij,6);
    return 4 * epsilon*sr6*(sr6 - 1);
}



Vecteur Univers::calcForceInteractionGrav(int i, int j) {

    Particule& pi = particules[i];
    Particule& pj = particules[j];

    Vecteur r_ij = pj.getPosition() - pi.getPosition();;
    float norm_rij = r_ij.norm();

    if (norm_rij == 0.0f) 
        return Vecteur(0,0,0);
    
    return r_ij * (pi.getMasse() * pj.getMasse()) / (norm_rij*norm_rij*norm_rij) ;
}






void Univers::calcAllForcesGrav(std::vector<Vecteur>& forces) {

    //On réduit les calculs par 2 en utilisant le fait que F_ij = -F_ji
    for (int i = 0; i < (int)particules.size(); i++) {
        for (int j = i + 1; j < (int)particules.size(); j++) {
            const Vecteur& F_ij = calcForceInteractionGrav(i, j);
            forces[i] += F_ij;  
            forces[j] -= F_ij;  
        }
    }
}

//Algorithme de Stromer-Verlet
void Univers::StromerVerlet(float t_end, float delta_t) {

    float t = 0.0f;
    int n = particules.size();

    //Calcul des forces F
    std::vector<Vecteur> F(n);
    std::vector<Vecteur> F_old(n);

    calcAllForcesGrav(F);
    
    while (t < t_end) {

        //Position
        for (int i = 0; i < n; i++) {
            F_old[i] = F[i]; 
            Vecteur newPosition = particules[i].getPosition() + delta_t*(particules[i].getVitesse() + .5f/particules[i].getMasse()*F_old[i]*delta_t);
            particules[i].setPosition(newPosition);
        }

        //Calcul des forces F
        calcAllForcesGrav(F);

        //Vitesse
        for (int i = 0; i < n; i++) {
            Vecteur newVitesse = particules[i].getVitesse() + delta_t*.5f/particules[i].getMasse()*(F[i] + F_old[i]);
            particules[i].setVitesse(newVitesse);
        }

        t += delta_t;
    }
}
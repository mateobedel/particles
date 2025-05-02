#include "Forces.hxx"
#include <cmath>

Vecteur Forces::calcForceInteractionPot(int i, int j, std::vector<Particule>& particules, float sigma6, float epsilon) {

    Particule& pi = particules[i];
    Particule& pj = particules[j];

    Vecteur r_ij = pj.getPosition() - pi.getPosition();
    float r_sq = r_ij.squared_norm();

    //Eviter les dépassement de floats
    if (r_sq < 1e-4) return Vecteur(0.0f,0.0f,0.0f);


    float sr6 = sigma6 / std::pow(r_sq, 3); // = sigma^6 / distance^6
    float force_magnitude = 24.0f * epsilon * sr6 * (1.0f - 2.0f * sr6) / r_sq;
    return r_ij * force_magnitude;
}


Vecteur Forces::calcForceInteractionGrav(int i, int j, std::vector<Particule>& particules) {

    Particule& pi = particules[i];
    Particule& pj = particules[j];

    Vecteur r_ij = pj.getPosition() - pi.getPosition();
    float r_sq = r_ij.squared_norm();

    //Eviter les dépassement de floats
    if (r_sq < 1e-6) return Vecteur(0.0f,0.0f,0.0f);

    //Possible d'optimiser cette ligne en utilisant Fast InvSqrt() de Quake III
    float inv_sqrt_r = 1.0f / std::sqrt(r_sq); 

    return r_ij * (pi.getMasse() * pj.getMasse()) * inv_sqrt_r * inv_sqrt_r * inv_sqrt_r;
}


Vecteur Forces::calcForceReflexion(int i, std::vector<Particule>& particules, float sigma, float epsilon, Vecteur fLd, int dimension) {

    const float r_cut_reflexion = 1.12246204831 * sigma ; // = 2^(1/6)*sigma

    Particule& p = particules[i];
    Vecteur position = p.getPosition();
    Vecteur force = Vecteur(0.0f, 0.0f, 0.0f);

    //Bords dimension x
    if (position.x < r_cut_reflexion) 
        force.x += calcPotentielReflexion(position.x, sigma, epsilon);
    else if (position.x  > fLd.x - r_cut_reflexion) 
        force.x -= calcPotentielReflexion(fLd.x - position.x, sigma, epsilon);
    
    //Bords dimension y
    if (dimension >= 2) {
        if (position.y < r_cut_reflexion) 
            force.y += calcPotentielReflexion(position.y, sigma, epsilon);
        else if (position.y > fLd.y - r_cut_reflexion) 
            force.y -= calcPotentielReflexion(fLd.y - position.y, sigma, epsilon);
    }

    //Bords dimension z
    if (dimension >= 3) {
        if (position.z < r_cut_reflexion) 
            force.z += calcPotentielReflexion(position.z, sigma, epsilon);
        else if (position.z > fLd.z - r_cut_reflexion) 
            force.z -= calcPotentielReflexion(fLd.z - position.z, sigma, epsilon);
    }

    return force;
}


float Forces::calcPotentielReflexion(float r, float sigma, float epsilon) {
    float s_over_2r = sigma / (2.0f * r); 
    float s_over_2r_pow6 = std::pow(s_over_2r, 6);
    return - 24.0f * epsilon * (1.0f / (2.0f * r)) * s_over_2r_pow6 * (1.0f - 2.0f * s_over_2r_pow6);
}


float Forces::calcPotentielGravitationnel(float m, float G) {
    return m*G;
}
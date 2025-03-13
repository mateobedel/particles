#pragma once

#include <string>
#include <vector>

struct Vecteur {
    public:

        float x,y,z;

        //Constructeurs
        Vecteur() : x(0.0f), y(0.0f), z(0.0f) {}
        Vecteur(float x_pos, float y_pos, float z_pos) : x(x_pos), y(y_pos), z(z_pos) {}
        Vecteur(const Vecteur& v) : x(v.x), y(v.y), z(v.z) {}

        float norm();

        //Affectation par copie
        Vecteur& operator=(const Vecteur& v);
    
        //Operations entre vecteurs :
        Vecteur operator +(const Vecteur& v);
        Vecteur operator -(const Vecteur& v);
        Vecteur operator *(const Vecteur& v);
        Vecteur operator /(const Vecteur& v);

        //Modifications d'un vecteur
        Vecteur& operator += (const Vecteur& v);
        Vecteur& operator -=(const Vecteur& v);
        Vecteur& operator *=(const Vecteur& v);
        Vecteur& operator /=(const Vecteur& v);

        //Operation entre scalaire et vecteur
        Vecteur operator +(const float f);
        Vecteur operator -(const float f);
        Vecteur operator *(const float f);
        Vecteur operator /(const float f);

        //Modifications d'un vecteur avec float
        Vecteur& operator +=(const float f);
        Vecteur& operator -=(const float f);
        Vecteur& operator *=(const float f);
        Vecteur& operator /=(const float f);

        Vecteur floor();
        Vecteur min(const float f);

};

//Operateurs externe entre scalaire et vecteur (et print)
Vecteur operator +(const float f, const Vecteur& v);
Vecteur operator -(const float f, const Vecteur& v);
Vecteur operator *(const float f, const Vecteur& v);
Vecteur operator /(const float f, const Vecteur& v);


std::ostream& operator<<(std::ostream& os, const Vecteur& v);
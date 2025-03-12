#include <string>
#include <vector>
#include <iostream>
#include <cmath>

#include "Vecteur.hxx"


float Vecteur::norm() {
    return std::sqrt(x*x + y*y + z*z);
}

//Operations entre vecteurs :

Vecteur& Vecteur::operator=(const Vecteur& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}
Vecteur Vecteur::operator +(const Vecteur& v) {
    return Vecteur(x+v.x, y+v.y, z+v.z);
}

Vecteur Vecteur::operator -(const Vecteur& v) {
    return Vecteur(x-v.x, y-v.y, z-v.z);
}

Vecteur Vecteur::operator *(const Vecteur& v) {
    return Vecteur(x*v.x, y*v.y, z*v.z);
}

Vecteur Vecteur::operator /(const Vecteur& v) {
    return Vecteur(x/v.x, y/v.y, z/v.z);
}

//Modifications d'un vecteur
Vecteur& Vecteur::operator += (const Vecteur& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vecteur& Vecteur::operator -=(const Vecteur& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vecteur& Vecteur::operator *=(const Vecteur& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Vecteur& Vecteur::operator /=(const Vecteur& v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

Vecteur& Vecteur::operator +=(const float f) {
    x += f;
    y += f;
    z += f;
    return *this;
}

Vecteur& Vecteur::operator -=(const float f) {
    x -= f;
    y -= f;
    z -= f; 
    return *this;
}

Vecteur& Vecteur::operator *=(const float f) {
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

Vecteur& Vecteur::operator /=(const float f) {
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

//Operation entre scalaire et vecteur
Vecteur Vecteur::operator +(const float f) {
    return Vecteur(x+f, y+f, z+f);
}

Vecteur Vecteur::operator -(const float f) {
    return Vecteur(x-f, y-f, z-f);
}

Vecteur Vecteur::operator *(const float f) {
    return Vecteur(x*f, y*f, z*f);
}

Vecteur Vecteur::operator /(const float f) {
    return Vecteur(x/f, y/f, z/f);
}

//Operateurs externe entre scalaire et vecteur
Vecteur operator +(const float f, const Vecteur& v) {
    return Vecteur(f+v.x, f+v.y, f+v.z);
}

Vecteur operator -(const float f, const Vecteur& v) {
    return Vecteur(f-v.x, f-v.y, f-v.z);
}

Vecteur operator *(const float f, const Vecteur& v) {
    return Vecteur(f*v.x, f*v.y, f*v.z);
}

Vecteur operator /(const float f, const Vecteur& v) {
    return Vecteur(f/v.x, f/v.y, f/v.z);
}

std::ostream& operator<<(std::ostream& os, const Vecteur& v) {
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";

}

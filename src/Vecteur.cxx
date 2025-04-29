#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "Vecteur.hxx"


float Vecteur::norm() {
    return std::sqrt(squared_norm());
}

float Vecteur::squared_norm() {
    return x*x + y*y + z*z;
}

void Vecteur::init(float f) {
    x = f;
    y = f;
    z = f;
}

void Vecteur::clamp(Vecteur min, Vecteur max, int dimension) {
    x = std::max(min.x, std::min(x, max.x));
    if (dimension >= 2) y = std::max(min.y, std::min(y, max.y));
    if (dimension >= 3) z = std::max(min.z, std::min(z, max.z));
}


//Operations entre vecteurs :

Vecteur& Vecteur::operator=(const Vecteur& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}
Vecteur Vecteur::operator +(const Vecteur& v) const {
    return Vecteur(x+v.x, y+v.y, z+v.z);
}

Vecteur Vecteur::operator -(const Vecteur& v) const {
    return Vecteur(x-v.x, y-v.y, z-v.z);
}

Vecteur Vecteur::operator *(const Vecteur& v) const {
    return Vecteur(x*v.x, y*v.y, z*v.z);
}

Vecteur Vecteur::operator /(const Vecteur& v) const {
    return Vecteur(x/v.x, y/v.y, z/v.z);
}

//Modifications d'un vecteur
Vecteur& Vecteur::operator +=(const Vecteur& v) {
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
    return os << v.x << " " << v.y << " " << v.z;
}

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "Univers.hxx"


int main() {

    Univers univ = Univers(2, 10000, Vecteur(16.0f,64.0f,0.0f), 2.5, 5, 1);
    univ.StromerVerlet(.1f,.001f);

    return 0;
}


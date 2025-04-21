
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "Univers.hxx"


int main() {

    Univers univ = Univers(2, 10000, Vecteur(250.0f,100.0f,0.0f), 2.5, 5, 1);
    univ.StromerVerlet(2.5f,0.05f);

    return 0;
}


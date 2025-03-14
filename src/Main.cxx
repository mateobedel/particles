
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "Univers.hxx"


int main() {

    Univers univ = Univers(3, 1000, Vecteur(250,250,250), 2.5);
    univ.StromerVerlet(100,1);

    return 0;
}


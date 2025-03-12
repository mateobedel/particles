
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "Univers.hxx"


int main() {

    Univers univ = Univers(3,128);
    univ.StromerVerlet(100,1);

    return 0;
}


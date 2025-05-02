# Simulation de particules

Ce projet simule des particules soumises à des interactions gravitationnelles et à des conditions aux limites.

## Structure du code

- `lib/` : headers (`.hxx`)
- `src/` : implémentations (`.cxx`)
- `doc/` : configuration et documentation Doxygen

## Principales classes

- `Particule` : représente une particule dans l’univers
- `Univers` : contient et met à jour l’état de toutes les particules
- `Forces` : fournit les fonctions de calcul des forces
- `VTKWriter` : écrit les sorties au format VTK

## Compilation

```bash
mkdir build && cd build
cmake ..
make
make doc
``` 


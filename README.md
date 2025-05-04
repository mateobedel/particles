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


## Lab 2

On test les performances de l'initialisation de  collections stockant notre classe de particules pour différents nombre de particules : $64, 128, . . . , 8192$ particules. 


| Particules | vector (ms) | list (ms) | deque (ms) | set (ms)   |
|------------|-------------|-----------|------------|------------|
| 64         | 0.008827    | 0.005821  | 0.001643   | 0.009377   |
| 128        | 0.007293    | 0.006352  | 0.006352   | 0.013957   |
| 256        | 0.020118    | 0.014397  | 0.008917   | 0.031690   |
| 512        | 0.026159    | 0.026110  | 0.017464   | 0.066626   |
| 1024       | 0.053140    | 0.051528  | 0.039124   | 0.117633   |
| 2048       | 0.103055    | 0.103977  | 0.093608   | 0.408374   |
| 4096       | 0.438431    | 0.458008  | 0.187725   | 0.552868   |
| 8192       | 0.469389    | 0.422621  | 0.371223   | 1.160390   |


A partir de $N = 2048$ les écarts en temps sont beaucoup plus marqués.

On choisis d'implémenter les particules dans un ```vector``` qui nous parait le choisi le plus logique étant donné que le nombre de particules restera fixe et que chaque particules aura un identifiant unique. De plus c'est une collection plutôt optimisée et flexible.

Après avoir implémenté l’algorithme de Strömer-Verlet pour la simulation des particules, on créer une simulation du système gravitationnel solaire, présent dans `demo/systeme_solaire.cxx`.

## Lab 3

On implémente une classe vecteur représentant un vecteur en 3 dimensions.
Pour représenté les autres dimensions, on fait le choix de laisser les autres composantes à 0 pour simplifier le code.

La création d'un template ```Vecteur<dimension>``` aurait était possible, mais nous avons préféré de garder une structure fichier `.cxx/.hxx` pour un code plus clair et organisé, au lieu de tout définir dans les header comme les templates l'aurait obligé.


TODO : Test de l'implémentation en terme d'insertion de particules ici pour $(2^5)^3$ particules

TODO : Test de l'implémentation  des intéractions ici pour $(2^5)^k$ particules, $k=3...7$ 

Pour diviser le nombre de calcul par deux on utilise la relation $F_{i,j} = -F_{j,i}$, en itérant seulement sur les $j < i$.


## Lab 4


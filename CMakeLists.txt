# CMakeLists.txt principal

cmake_minimum_required(VERSION 3.10)

project(MonProjet)

# Ajouter le répertoire src pour la construction du code source
add_subdirectory(src)

# Ajouter le répertoire test pour la construction des tests
add_subdirectory(test)

# Ajouter src au chemin d'inclusion
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/lib)

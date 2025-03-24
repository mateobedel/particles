cmake_minimum_required(VERSION 3.10)
project(particules)

# Configuration des sous-répertoires
add_subdirectory(lib)
add_subdirectory(src)

# Répertoire de sortie des exécutables

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
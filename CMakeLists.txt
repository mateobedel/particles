cmake_minimum_required(VERSION 3.10)
project(particules)

set(SANITIZER_FLAGS "-fsanitize=address,undefined -g")
set(GPROF_FLAGS "-pg")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

# Configuration des sous-répertoires
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)

# Répertoire de sortie des exécutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
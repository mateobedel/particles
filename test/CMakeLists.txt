cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(VotreProjet)

# Ajouter GoogleTest via FetchContent
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.10.0
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error")

# Créer un exécutable pour les tests
add_executable(test_vecteur test_vecteur.cxx)


# Lier l'exécutable des tests avec GoogleTest et les sources du projet
target_link_libraries(test_vecteur gtest_main src)

# Activer les tests
enable_testing()

include(GoogleTest)
gtest_discover_tests(test_vecteur)

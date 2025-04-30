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

# Définir les répertoires d'includes communs
set(PROJECT_INCLUDES
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/src
)

# Créer l'exécutable pour test_vecteur
add_executable(test_vecteur test_vecteur.cxx)
target_include_directories(test_vecteur PRIVATE ${PROJECT_INCLUDES})
target_link_libraries(test_vecteur gtest_main src)

# Créer l'exécutable pour test_univers
add_executable(test_univers test_univers.cxx)
target_include_directories(test_univers PRIVATE ${PROJECT_INCLUDES})
target_link_libraries(test_univers gtest_main src)

target_compile_options(gtest PRIVATE -w)

# Activer les tests
enable_testing()

include(GoogleTest)
gtest_discover_tests(test_vecteur)
gtest_discover_tests(test_univers)

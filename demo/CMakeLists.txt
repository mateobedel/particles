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
add_executable(collision collision.cxx)
target_include_directories(collision PRIVATE ${PROJECT_INCLUDES})
target_link_libraries(collision gtest_main src)

# Créer l'exécutable pour test_univers
add_executable(systemesolaire systemesolaire.cxx)
target_include_directories(systemesolaire PRIVATE ${PROJECT_INCLUDES})
target_link_libraries(systemesolaire gtest_main src)

target_compile_options(gtest PRIVATE -w)

# Activer les tests
enable_testing()

include(GoogleTest)
gtest_discover_tests(collision)
gtest_discover_tests(systemesolaire)

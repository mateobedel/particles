# CMakeLists.txt dans le répertoire src/

# Ajouter des fichiers sources pour la bibliothèque ou l'exécutable
# Si tu as plusieurs fichiers sources, tu peux les lister ici.
add_library(src
    Vecteur.cxx
    Main.cxx
)

# Cible principale si tu veux un exécutable
add_executable(MonProjet Main.cxx)

# Lier l'exécutable aux bibliothèques ou objets nécessaires
target_link_libraries(MonProjet src)

target_include_directories(src PUBLIC ${CMAKE_SOURCE_DIR}/src)

include_directories(${CMAKE_SOURCE_DIR}/lib)
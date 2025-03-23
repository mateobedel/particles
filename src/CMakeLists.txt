# Créer la bibliothèque 'src' (sans Main.cxx)
add_library(src STATIC
    Univers.cxx
    Vecteur.cxx
    VTKWriter.cxx
)

# Créer l'exécutable MonProjet (avec Main.cxx)
add_executable(MonProjet Main.cxx)

# Lier les dépendances
target_link_libraries(MonProjet PRIVATE src lib)

# Inclure les répertoires des en-têtes
target_include_directories(src PUBLIC
    ${CMAKE_SOURCE_DIR}/lib   # Pour les .hxx dans lib/
    ${CMAKE_SOURCE_DIR}/src   # Pour les .hxx dans src/
)

# Inclure les en-têtes pour l'exécutable
target_include_directories(MonProjet PRIVATE
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/src
)
# Créer la bibliothèque 'src' (sans Main.cxx)
add_library(src STATIC
    Univers.cxx
    Vecteur.cxx
    VTKWriter.cxx
    Forces.cxx
)

# Créer l'exécutable MonProjet (avec Main.cxx)
add_executable(particules Main.cxx)

# Lier les dépendances
target_link_libraries(particules PRIVATE src lib)

# Inclure les répertoires des en-têtes
target_include_directories(src PUBLIC
    ${CMAKE_SOURCE_DIR}/lib   # Pour les .hxx dans lib/
    ${CMAKE_SOURCE_DIR}/src   # Pour les .hxx dans src/
)

# Inclure les en-têtes pour l'exécutable
target_include_directories(particules PRIVATE
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/src
)

set_target_properties(particules PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
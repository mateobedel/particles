#pragma once

#include "Univers.hxx"

/**
 * @class VTKWriter
 * @brief Classe utilitaire pour exporter les données de l'univers au format VTK.
 */
class VTKWriter {

    private:

        /**
         * @brief Écrit l'en-tête du fichier VTK (.vtu).
         * @param file Flux de sortie.
         * @param univers Univers contenant les données à exporter.
         */
        static void writeHeader(std::ofstream& file, Univers& univers);

        /**
         * @brief Écrit les données des particules dans le fichier VTK.
         * @param file Flux de sortie.
         * @param univers Univers contenant les particules.
         */
        static void writeParticlesData(std::ofstream& file, Univers& univers);

    public:

        /**
         * @brief Gère l'option d'éxécution -nb_vtk
         * @param argc Nombre d'arguments.
         * @param agrv Les arguments.
         * @return Le nombre de fichier vtk à générer
        */
        static int readVTKNumber(int argc, char* argv[]);



        /**
         * @brief Écrit un fichier VTK (.vtu) à partir de l'univers donné.
         * @param filename Nom du fichier VTK à générer.
         * @param univers Référence à l'univers à exporter.
         */
        static void write(const std::string& filename, Univers& univers);


        /**
         * @brief Génère les indices de pas de temps où écrire des fichiers VTK.
         *
         * @param vtkNumber Nombre total de fichiers VTK à générer (>= 0).
         * @param steps Nombre total d'étapes de simulation (t_end / delta_t).
         * @return Un vecteur contenant les indices de pas de temps où écrire un fichier.
         */
        static std::vector<int> genOutputSteps(int vtkNumber, int steps);


        /**
         * @brief Écrit un fichier VTK à l'étape actuelle si elle correspond à un moment d'export.
         *
         * @param step Numéro d'étape actuel de la simulation.
         * @param t Temps actuel de la simulation.
         * @param outSteps Vecteur des étapes où une écriture est prévue.
         * @param nextOut Référence à l’indice du prochain pas d’écriture dans `outSteps`.
         * @param u Référence constante à l'univers à exporter.
         */
        static void writeOnOutSteps(int step, float t, const std::vector<int>& outSteps, Univers& u);
};
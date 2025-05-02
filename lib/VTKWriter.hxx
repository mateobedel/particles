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
         * @brief Écrit un fichier VTK (.vtu) à partir de l'univers donné.
         * @param filename Nom du fichier VTK à générer.
         * @param univers Référence à l'univers à exporter.
         */
        static void write(const std::string& filename, Univers& univers);
};
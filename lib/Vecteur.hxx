#pragma once

#include <string>
#include <vector>

/**
 * @struct Vecteur
 * @brief Représente un vecteur 1D 2D ou 3D de float avec opérations usuelles.
 * 
 * Si un vecteur est en 1D, ses deux dernières composantes seront 0.0f, 
 * si il est en 2D, sa troisième composante sera 0.0f.
 * 
 */
struct Vecteur {
    public:

        float x,y,z;

        /// @brief Constructeur nul.
        Vecteur() : x(0.0f), y(0.0f), z(0.0f) {}

        /// @brief Constructeur avec composantes.
        Vecteur(float x_pos, float y_pos, float z_pos) : x(x_pos), y(y_pos), z(z_pos) {}

        /// @brief Constructeur par copie.
        Vecteur(const Vecteur& v) : x(v.x), y(v.y), z(v.z) {}

        /**
         * @brief Retourne la norme du vecteur.
         */
        float norm();

        /**
         * @brief Retourne la norme au carré.
         */
        float squared_norm();

        /**
         * @brief Initialise chaque composante à une valeur donnée.
         * @param f Valeur à assigner.
         */
        void init(float f);

        /**
         * @brief Contraint chaque composante entre des bornes données.
         * @param min Vecteur minimum.
         * @param max Vecteur maximum.
         * @param dimension Dimension à considérer (1, 2 ou 3).
         */
        void clamp(Vecteur min, Vecteur max, int dimension);

        /// @brief Affectation par copie.
        Vecteur& operator=(const Vecteur& v);
    
        //Operations entre vecteurs :
        Vecteur operator +(const Vecteur& v) const;
        Vecteur operator -(const Vecteur& v) const;
        Vecteur operator *(const Vecteur& v) const;
        Vecteur operator /(const Vecteur& v) const;

        //Modifications d'un vecteur
        Vecteur& operator += (const Vecteur& v);
        Vecteur& operator -=(const Vecteur& v);
        Vecteur& operator *=(const Vecteur& v);
        Vecteur& operator /=(const Vecteur& v);

        //Operation entre scalaire et vecteur
        Vecteur operator +(const float f);
        Vecteur operator -(const float f);
        Vecteur operator *(const float f);
        Vecteur operator /(const float f);

        //Modifications d'un vecteur avec float
        Vecteur& operator +=(const float f);
        Vecteur& operator -=(const float f);
        Vecteur& operator *=(const float f);
        Vecteur& operator /=(const float f);

};

//Operateurs externe entre scalaire et vecteur (et print)
Vecteur operator +(const float f, const Vecteur& v);
Vecteur operator -(const float f, const Vecteur& v);
Vecteur operator *(const float f, const Vecteur& v);
Vecteur operator /(const float f, const Vecteur& v);

/**
 * @brief Affiche un vecteur sur un flux de sortie.
 * @param os Le flux de sortie.
 * @param v Le vecteur à afficher.
 * @return Le flux modifié.
 */
std::ostream& operator<<(std::ostream& os, const Vecteur& v);
// #############################################################################
// # File image_processing.cpp
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file image_processing.cpp
 * @brief Transformation de l'image codec-V1 en format PBM (codec P4)
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"

/**
 * @brief Fonction pour écrire une image binaire dans un file_input PBM
 *
 * @param input_image_path Chemin vers l'image d'entrée
 * @param output_pbm_path Chemin vers le file_input PBM de sortie
 */
void write_to_PBM(const std::string &input_image_path, const std::string &output_pbm_path)
{
    // Lire l'image
    cv::Mat image = cv::imread(input_image_path, cv::IMREAD_GRAYSCALE); // En niveaux de gris
    if (image.empty())
    {
        std::cerr << "Erreur : Impossible de lire l'image : " << input_image_path << std::endl;
        return;
    }

    // Ouvrir le file_input PBM pour écriture
    std::ofstream pbm_file(output_pbm_path, std::ios::binary); // Sortie binaire
    if (!pbm_file.is_open())
    {
        std::cerr << "Erreur : Impossible d'ouvrir le file_input pour écriture : " << output_pbm_path << std::endl;
        return;
    }

    // Écrire l'en-tête PBM
    int width = image.cols;
    int height = image.rows;
    pbm_file << "P4\n"
            << width << " " << height << "\n"; // En-tête PBM pour format binaire

    // Écrire les données de pixels au format PBM
    // PBM nécessite le conditionnement de 8 pixels par octet pour les images binaires
    for (int row = 0; row < height; ++row)
    {
        unsigned char byte = 0;
        int bitCount = 0;

        for (int col = 0; col < width; ++col)
        {
            // Convertir le pixel en niveaux de gris en bit (1 pour blanc, 0 pour noir)
            unsigned char bit = (image.at<unsigned char>(row, col) > 127) ? 0 : 1;
            byte = (byte << 1) | bit; // Emballer le bit dans l'octet
            bitCount++;

            if (bitCount == 8)
            {
                pbm_file.write(reinterpret_cast<char *>(&byte), 1);
                byte = 0;
                bitCount = 0;
            }
        }

        // Écrire les bits restants si la largeur n'est pas un multiple de 8
        if (bitCount > 0)
        {
            byte <<= (8 - bitCount); // Décalage à gauche pour compléter l'octet
            pbm_file.write(reinterpret_cast<char *>(&byte), 1);
        }
    }

    pbm_file.close();
    std::cout << "file_input PBM sauvegardé à " << output_pbm_path << std::endl;
}

/**
 * @brief Fonction principale pour transformer l'image codec-V1 du workflow automatic vers PBM
 *
 * @param argc Nombre d'arguments
 * @param argv Tableau d'arguments
 * @return int Code de retour
 */
int main(int argc, char *argv[])
{
    const char *input_image_path = "images/codec-V1.jpeg"; // À TESTER AUSSI POUR JPEG
    const char *output_pbm_path = "pbms/codec-V1.pbm";

    write_to_PBM(input_image_path, output_pbm_path);

    return 0;
}

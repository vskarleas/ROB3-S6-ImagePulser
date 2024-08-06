// #############################################################################
// # File image_processing.cpp
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################


/**
 * @file image_processing_manual.cpp
 * @brief Utilisation de l'image_processing en mode manuel
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
 * @brief Image vers PBM en codec P4
 * 
 * @param input_image_path Le chemin de l'image d'entrée
 * @param output_pbm_path Le chemin du fichier PBM de sortie
 */
void write_to_PBM(const std::string &input_image_path, const std::string &output_pbm_path)
{
    // Read the image
    cv::Mat image = cv::imread(input_image_path, cv::IMREAD_GRAYSCALE); // Grayscale
    if (image.empty())
    {
        std::cerr << "Error: Could not read the image: " << input_image_path << std::endl;
        return;
    }

    // Open the PBM file for writing
    std::ofstream pbm_file(output_pbm_path, std::ios::binary); // Binary output
    if (!pbm_file.is_open())
    {
        std::cerr << "Error: Could not open file for writing: " << output_pbm_path << std::endl;
        return;
    }

    // Write the PBM header
    int width = image.cols;
    int height = image.rows;
    pbm_file << "P4\n"
             << width << " " << height << "\n"; // PBM header for binary format

    // Write the pixel data in PBM format
    // PBM requires packing 8 pixels per byte for binary images
    for (int row = 0; row < height; ++row)
    {
        unsigned char byte = 0;
        int bitCount = 0;

        for (int col = 0; col < width; ++col)
        {
            // Convert grayscale pixel to a bit (1 for white, 0 for black)
            unsigned char bit = (image.at<unsigned char>(row, col) > 127) ? 0 : 1;
            byte = (byte << 1) | bit; // Pack the bit into the byte
            bitCount++;

            if (bitCount == 8)
            {
                pbm_file.write(reinterpret_cast<char *>(&byte), 1);
                byte = 0;
                bitCount = 0;
            }
        }

        // Write remaining bits if the width is not a multiple of 8
        if (bitCount > 0)
        {
            byte <<= (8 - bitCount); // Left-shift to complete the byte
            pbm_file.write(reinterpret_cast<char *>(&byte), 1);
        }
    }

    pbm_file.close();
    std::cout << "PBM file saved to " << output_pbm_path << std::endl;
}

/**
 * @brief Fonction principale pour tester l'écriture d'une image en PBM
 *
 * @param argc Nombre d'arguments
 * @param argv Tableau d'arguments
 * @return int Code de retour
 */
int main(int argc, char **argv)
{
    printf("Here are the available images inside the images folder that can be tranformed to PBM (codec P4) format: \n\n");
    system("ls images");
    printf("==========================================\nEnter the name of the image's file WITH any extension (.jpeg, .png etc)\n");
    
    char name[256];
    scanf("%255s", name); // Pas de overflow

    //Longeur final du nom
    size_t exit_file_len = strlen(name) + 10;
    char exit_file[exit_file_len];

    // Creation du nom de l'image via la concatenation des informations
    size_t file_input_len = strlen("images/") + strlen(name) + 1; // +1 pour /n
    char *file_input = (char *)malloc(file_input_len);

    if (file_input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    snprintf(file_input, file_input_len, "images/%s", name);
    snprintf(exit_file, exit_file_len, "pbms/%s.pbm", strtok(name, "."));

    write_to_PBM(file_input, exit_file);

    free(file_input);

    return 0;
}

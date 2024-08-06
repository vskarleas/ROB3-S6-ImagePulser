// #############################################################################
// # file_input cartoon_manual.cpp
// # Projet en C - Polytech Sorbonne - 2023/2024 - S6
// # Auteurs : Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - Tous droits réservés.
// #############################################################################

/**
 * @file cartoon_manual.cpp
 * @brief Application du filtre cartoon en manuel
 *
 */

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/**
 * @brief Mettre une image en manual pour etre modifié par le filtre cartoon
 * 
 * @param input_file le file_input de l'image
 * @param output_file la destination de l'image
 */
void cartoon_effect(const std::string &input_file, const std::string &output_file)
{
    // Charger l'image
    Mat img = imread(input_file);
    if (img.empty())
    {
        std::cerr << "Erreur de chargement de l'image : " << input_file << std::endl;
        return;
    }

    // Appliquer le filtre bilatéral
    Mat img_bilateral;
    bilateralFilter(img, img_bilateral, 9, 75, 75);

    // Convertir en niveaux de gris
    Mat gray;
    cvtColor(img_bilateral, gray, COLOR_BGR2GRAY);

    // Appliquer le flou médian
    Mat gray_blurred;
    medianBlur(gray, gray_blurred, 7);

    // Détecter les contours
    Mat edges;
    adaptiveThreshold(gray_blurred, edges, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 9, 2);

    // Convertir les contours en couleur
    Mat edges_colored;
    cvtColor(edges, edges_colored, COLOR_GRAY2BGR);

    // Combiner les contours avec l'image originale
    Mat cartoon;
    bitwise_and(img_bilateral, edges_colored, cartoon);

    // Enregistrer le résultat
    imwrite(output_file, cartoon);
}

int main(int argc, char **argv)
{
    printf("Here are the available images inside the images folder that can be Cartoonized! \n\n");
    system("ls images");
    printf("==========================================\nEnter the name of the image's file WITH any extension (.jpeg, .png etc)\n");
    
    char name[256];
    scanf("%255s", name); //Faire attention à overflow du nom

    //Calcul de la taille du nom de "exit_file"
    size_t exit_file_len = strlen(name) + 20;
    char exit_file[exit_file_len];

    // Creation du nom de l'image via la concatenation des informations
    size_t file_input_len = strlen("images/") + strlen(name) + 1; // +1 for the null terminator
    char *file_input = (char *)malloc(file_input_len);

    if (file_input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    snprintf(file_input, file_input_len, "images/%s", name);
    snprintf(exit_file, exit_file_len, "images/cartoonized-%s", name);

    // Application du filtre cartoon
    cartoon_effect(file_input, exit_file);
    free(file_input);

    return 0;
}

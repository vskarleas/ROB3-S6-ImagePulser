// #############################################################################
// # File mask.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file mask.c
 * @brief Test pour l'image masque
 *
 */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "contour.h"
#include "image.h"

int main(int argc, char **argv)
{
    /* Testing that the mask image is correct */
    printf("Starting Test 6\n");
    printf("Enter the name of the image's file without any extension (pbm)\n");
    char name[256];
    scanf("%s", name);

    char *no_extension = strtok(name, ".");
    char *file_input = malloc(strlen("pbms/") + strlen(no_extension) + 4);
    strcpy(file_input, "pbms/");
    strcat(file_input, no_extension);
    strcat(file_input, ".pbm");

    char *exit_file=malloc(strlen(name)+4);

    strcpy(exit_file,name);
    strcat(exit_file,".txt");
    
    Image I;
    I = read_image_file(file_input);
    image_to_terminal(I);

    // Test number 6
    printf("=====================\n");
    printf("Test du mask de l'image\n");
    printf("=====================\n");
    Image mask;
    mask = mask_image(I);
    image_to_terminal(mask);

    // Test number 7
    /* Test de verifications que la lecture des multiples contours ainsi que la creation du postscript des multiples contours marche aussi */
    printf("Starting Test 7\n");
    printf("=====================\n");
    printf("Test du multiple contours de l'image:\n");
    Liste_Contours liste;
    liste = creer_liste_Contours_vide();
    liste = algo_contours(mask);
    contours_data(liste);
    create_postscript_contours(liste, exit_file, image_height(I), image_width(I), "masks/"); //Mode remplisage only

    printf("=====================\n");
    return 0;
}

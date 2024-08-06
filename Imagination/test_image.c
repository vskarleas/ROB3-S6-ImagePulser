// #############################################################################
// # File test_image.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file test_image.c
 * @brief Test pour la vérification des la création de l'image négative
 *
 */

#include <stdint.h>
#include <string.h>
#include<stdlib.h>
#include"error.h"
#include"image.h"

/* Test de verification si la fonction de negation de l'image marche et si la fonction d'affichage de pbm marche aussi */
int main(int argc, char **argv)
{
    if (argc!=2)
    {
        printf("Image file is missing as argument. Please give an image path as argument and try again.\n");
        exit(-10);
    }
    // Test number 1
    printf("==========\n");
    printf("Test 1\n");
    printf("==========\n");
    Image I;
    char file_input[100];
    strcpy(file_input, argv[1]);
    I = read_image_file(file_input);
    image_to_terminal(I);

    printf("\n");
    printf("\n");
    // Test number 2
    Image neg;
    printf("==========\n");
    printf("Test 2\n");
    printf("==========\n");
    neg = negative_image(I);
    image_to_terminal(neg);

    return 0;
}
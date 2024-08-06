// #############################################################################
// # File test_postscript.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file test_postscript.c
 * @brief Test pour la vérification des l'ecriture des images en postscript (.eps)
 *
 */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "contour.h"
#include "image.h"

int main(int argc, char **argv)
{
    if (argc != 1)
    {
        printf("No arguments are required for this test\n");
        exit(-10);
    }
    // Test number 5
    printf("Starting Test 5\n");
    Image I;
    printf("Enter the name of the image's file without any extension (pbm)\n");
    char name[256];
    scanf("%s", name);
    printf("Enter 1[stroke] or 2[fill]\n");
    int id;
    int res = 0;
    scanf("%d", &id);

    while (res >= 0)
    {
        if (id == 1 || id == 2)
        {
            res = -1;
        }
        else
        {
            printf("Please type 1 for [stroke] or 2 for [fill]\n");
            scanf("%d", &id);
            res++;
        }
    }

    char *file_input = malloc(strlen(name) + 4);
    char *exit_file = malloc(strlen(name) + 4);
    strcpy(file_input, name);
    strcat(file_input, ".pbm");

    strcpy(exit_file, name);
    strcat(exit_file, ".txt");

    I = read_image_file(file_input);
    image_to_terminal(I);

    printf("=====================\n");
    printf("Test du PostScript\n");
    printf("=====================\n");
    Contour k;
    k = algo_contour(I, exit_file, "contours/simple/"); // 1 here will be controlled from a variable on Tache 5 where more contours are required to be added on the same file
    
    /* Test de creation du postscript pour un contour (contour donne par l'algo_contour) */
    /* LATER WE ARE USING algo_contours POUR LA LECTURE DES MULTIPLES LECTURES AINSI QUE LA
    CREATION DU file_input POSTSCRIPT (EPS) POUR CEUX CONTOURS */
    if (id == 1)
    {
        create_postscript(k, exit_file, image_height(I), image_width(I));
        printf("Text files should have been written with title %s.txt and %s.eps in mode stroke\n", name, name);
    }
    else
    {
        create_postscript_fill(k, exit_file, image_height(I), image_width(I));
        printf("Text files should have been written with title %s.txt and %s.eps in mode fill\n", name, name);
    }
    printf("=====================\n");

    return 0;
}

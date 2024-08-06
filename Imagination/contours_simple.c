// #############################################################################
// # file_input contours_simple.c
// # Projet en C - Polytech Sorbonne - 2023/2024 - S6
// # Auteurs : Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - Tous droits réservés.
// #############################################################################

/**
 * @file contours_simple.c
 * @brief Test pour la détection d'un seul contour
 *
 */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "contour.h"
#include "image.h"

/**
 * @brief Implémentation de test pour la détection d'un contour
 * 
 * @param argc Nombre d'arguments de la ligne de commande.
 * @param argv Tableau des arguments de la ligne de commande.
 * @return int Code de retour du programme.
 */
int main(int argc, char **argv)
{
    if (argc != 1)
    {
        printf("Aucun argument n'est requis pour ce test\n");
        exit(-10);
    }

    // Début du test numéro 4
    printf("Début du Test 4\n");
    Image I;
    printf("Entrez le nom du file_input de l'image sans extension (pbm)\n");
    char name[256];
    scanf("%s", name);

    // Préparation de la recherche du file_input selon son nom
    char *no_extension = strtok(name, ".");
    char *file_input = malloc(strlen("pbms/") + strlen(no_extension) + 4);
    strcpy(file_input, "pbms/");
    strcat(file_input, no_extension);
    strcat(file_input, ".pbm");

    char *exit_file = malloc(strlen(name) + 4);
    strcpy(exit_file, name);
    strcat(exit_file, ".txt");

    // Lecture de l'image
    I = read_image_file(file_input);
    image_to_terminal(I);

    // Vérification de la création du file_input .txt pour les contours d'une image
    printf("=====================\n");
    printf("Test du contour\n");
    printf("=====================\n");
    algo_contour(I, exit_file, "contours/simple/"); // Le file_input sera contrôlé par une variable dans la Tache 5 où plusieurs contours seront ajoutés dans le même file_input
    printf("Le file_input texte devrait avoir été écrit avec le titre %s\n", exit_file); // Le file_input est géré dans la fonction algo_contour
    printf("=====================\n");
    return 0;
}


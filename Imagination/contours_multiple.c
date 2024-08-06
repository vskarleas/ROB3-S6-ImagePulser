// #############################################################################
// # File contours_multiple.c
// # Projet en C - Polytech Sorbonne - 2023/2024 - S6
// # Auteurs : Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - Tous droits réservés.
// #############################################################################

/**
 * @file contours_multiple.c
 * @brief Test pour la détection de multiples de contours
 *
 */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "contour.h"
#include "image.h"

/**
 * @brief Implémentation de tests pour la détection de multiples contours ainsi que pour la création de l'image masque.
 * 
 * @param argc Nombre d'arguments de la ligne de commande.
 * @param argv Tableau des arguments de la ligne de commande.
 * @return int Code de retour du programme.
 */
int main(int argc, char **argv)
{
    // Test pour vérifier que l'image masque est correcte
    printf("Début du Test 6\n");
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
    Image I;
    I = read_image_file(file_input);

    // Test de vérification de la lecture des multiples contours ainsi que la création du postscript des multiples contours
    printf("Début du Test 7\n");
    printf("=====================\n");
    printf("Test des multiples contours de l'image:\n");

    // Création d'une liste chaînée de contours
    Liste_Contours liste;
    liste = creer_liste_Contours_vide();
    liste = algo_contours(I);

    // Écriture des contours dans un file_input texte
    pbm_contour_to_txt(liste, exit_file, "contours/multiple/");
    contours_data(liste);

    // Affichage du succès de l'écriture du file_input texte
    printf("Le file_input texte devrait avoir été écrit avec le titre %s\n", exit_file);
    printf("=====================\n");
    return 0;
}


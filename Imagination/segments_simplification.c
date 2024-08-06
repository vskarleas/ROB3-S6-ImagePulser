// #############################################################################
// # file_input segments_simplification.c
// # Projet en C - Polytech Sorbonne - 2023/2024 - S6
// # Auteurs : Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - Tous droits réservés.
// #############################################################################

/**
 * @file segments_simplification.c
 * @brief Application de segments_simplification sur codec-V1.pbm
 *
 */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "contour.h"
#include "image.h"

int main(int argc, char **argv)
{
    // Gestion des erreurs et des arguments incorrects
    if (argc != 2)
    {
        printf("Erreur lors de la réception de l'argument pour segments_simplification\n");
        exit(-19);
    }

    // Codec d'image utilisé par défaut pour le nommage
    char name[9] = "codec-V1";
    double d = atoi(argv[1]); // Convertir l'argument en double

    char *file_input = "pbms/codec-V1.pbm";
    char exit_file[(strlen(name) + 20)];

    // Mise à jour du nom de l'image simplifiée utilisé pour les sauvegardes
    snprintf(exit_file, (strlen(name) + 21), "%s-simp-taille%.2f.txt", name, d);

    // Lecture de la version PBM de l'image
    Image I;
    I = read_image_file(file_input);

    // Initialisations pour la détection des contours. Il y a deux listes chaînées en parallèle. Une pour l'image lue et une pour l'image simplifiée
    Liste_Contours liste;
    liste = creer_liste_Contours_vide();
    liste = algo_contours(I); // detection des contours
    contours_data(liste);
    printf("\n");
    printf("\n");

    // Liste chaînée contenant les contours simplifiés
    Liste_Contours simple;
    simple = creer_liste_Contours_vide(); // l'élément de chaque liste de contours est une liste de points
    Contour el;
    el = creer_liste_Point_vide();

    Cellule_Liste_Contours *al; // utilisé pour se déplacer dans la liste chaînée de contours
    al = liste.first;
    while (al != NULL)
    {
        // mettre la liste chaînée dans un format statique
        Tableau_Point T = sequence_points_liste_vers_tableau(al->data);

        // Simplification par segments
        el = simplification_douglas_peucker(T, 0, (T.taille) - 1, d);

        // Une fois qu'une simplification est faite, on ajoute le segment simplifié à la liste de contours en parallèle
        ajouter_element_liste_Contours(&simple, el);
        al = al->suiv;
    }

    printf("Après la simplification par segments :\n");

    // Sauvegarde des journaux dans leur dossier spécifié
    pbm_contour_to_txt(simple, exit_file, "contours/multiple/");

    // Affichage des résultats de la simplification par segments
    contours_data_simplification(simple);

    // Création du file_input Postscript
    create_postscript_contours(simple, exit_file, image_height(I), image_width(I), "simplifications/segments/"); // Mode remplissage uniquement

    // Préparation de la commande pour la visualisation via Evince
    char command[100];
    strcpy(command, "evince simplifications/segments/");
    strcat(command, exit_file);
    strcat(command, ".eps &"); // Exécution de la commande en arrière-plan

    // Evince et message de vérification
    system(command);
    printf("L'image simplifiée est enregistrée sous simplifications/segments/%s.eps et elle est maintenant ouverte dans une fenêtre Evince.", exit_file);

    return 0;
}

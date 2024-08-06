// #############################################################################
// # File segments_simplification_manual.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file segments_simplification_manual.c
 * @brief Application de la simplification par segments sur codec-V1.pbm
 *
 */

#include <stdint.h>
#include <string.h>
#include<stdlib.h>

#include "contour.h"
#include "image.h"

/* Test de verification de la methode de simplification par segments */
int main(int argc, char **argv)
{
    printf("Here are the available images inside the PBM folder that you can use: \n\n");
    system("ls pbms");

    printf("\n==========================\nEnter the name of the image's file without any extension (pbm)\n");
    char name[256];
    scanf("%s", name);
    double d;
    printf("D=");
    scanf("%lf", &d);
    printf("\n");

    char *no_extension = strtok(name, ".");
    char *file_input = malloc(strlen("pbms/") + strlen(no_extension) + 4);
    strcpy(file_input, "pbms/");
    strcat(file_input, no_extension);
    strcat(file_input, ".pbm");

    char exit_file[(strlen(name)+20)];

    //updating simplified image name used for saving purposes
    if (d != 0.5)
    {
        snprintf(exit_file, (strlen(name)+20), "%s-simp-taille%.0f.txt", name, d );
    }
    //TO BE ADDED: Filter with strtok that changes the name of the file to be saved for numbers smaller than 1
    else
    {
        snprintf(exit_file, (strlen(name)+20), "%s-simp-taille%.0f-5.txt", name, d );
    }
    
    Image I;
    I = read_image_file(file_input);

    Liste_Contours liste;
    liste = creer_liste_Contours_vide();
    liste = algo_contours(I);
    contours_data(liste);
    printf("\n");
    printf("\n");

    Liste_Contours simple;
    simple = creer_liste_Contours_vide();
    Contour el;
    el = creer_liste_Point_vide();

    Cellule_Liste_Contours *al;
    al = liste.first;
    while (al != NULL)
    {
        Tableau_Point T = sequence_points_liste_vers_tableau(al->data);
        
        //Simplification par segments
        el = simplification_douglas_peucker(T, 0,(T.taille)-1, d);
        ajouter_element_liste_Contours(&simple, el);
        al = al->suiv;
    }

    printf("Apres la simplification par segments:\n");
    pbm_contour_to_txt(simple, exit_file, "contours/multiple/");
    contours_data_simplification(simple);
    create_postscript_contours(simple, exit_file, image_height(I), image_width(I), "simplifications/segments/"); //Mode remplisage only
    
    //Préparation de la commande pour la visualisation via Evince
    char command[100];
    strcpy(command, "evince simplifications/segments/");
    strcat(command, exit_file);
    strcat(command, ".eps &"); //Exécution de la commande en arrière-plan

    //Evince et message de vérification
    system(command);
    printf("L'image simplifiée est enregistrée sous simplifications/segments/%s.eps et elle est maintenant ouverte dans une fenêtre Evince.", exit_file);
    
    return 0;

}

// #############################################################################
// # File bezier2_simplification_manual.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file bezier2_simplification_manual.c
 * @brief Utilisation de bezier2_simplification en manuel
 *
 */

#include <stdint.h>
#include <string.h>
#include<stdlib.h>

#include "contour.h"
#include "image.h"

/**
 * @brief Verifier que la simplifcation par courbe bezier des degrees 2 soit valide
 * 
 */
int main(int argc, char **argv)
{
    printf("Here are the available images inside the PBM folder that you can use: \n\n");
    system("ls pbms");

    //Choix de l'image pour tester
    printf("\n==========================\nEnter the name of the image's file without any extension (pbm)\n");
    char name[256];
    double d = 0.0;
    scanf("%s", name);
    printf("D=");

    //Distance seuil passe en terminal par l'utilisateur
    scanf("%lf", &d);
    printf("\n");

    //Creation du nom de l'image via la concatenation des informations
    char *no_extension = strtok(name, ".");
    char *file_input = malloc(strlen("pbms/") + strlen(no_extension) + 4);
    strcpy(file_input, "pbms/");
    strcat(file_input, no_extension);
    strcat(file_input, ".pbm");

    char exit_file[(strlen(name)+20)];

    //Creation du fichier de sortie des contours
     if (d != 0.5)
    {
        snprintf(exit_file, (strlen(name)+20), "%s-deg2-taille%.0f.txt", name, d );
    }
    else
    {
        snprintf(exit_file, (strlen(name)+20), "%s-deg2-taille%.0f-5.txt", name, d );
    }

    
    
    //Lecture de l'image 
    Image I;
    I = read_image_file(file_input);

    //Ceation d'une liste chaine de contours
    Liste_Contours liste;
    liste = creer_liste_Contours_vide();

    //Detection des contours
    liste = algo_contours(I);
    contours_data(liste);
    printf("\n");
    printf("\n");

    printf("Apres la simplification par courbe de bezier de degre 2:\n");

    //Creation d'une liste chaine de contours simplifies
    Liste_Contours simple;
    simple = creer_liste_Contours_vide();
    Contour el;
    el = creer_liste_Point_vide();

    //Tranformation de chaque cellule de la liste chaine de contours en tableau de points pour acceler la processus de lecture de donnes
    Cellule_Liste_Contours *al;
    al = liste.first;
    while (al != NULL)
    {
        Tableau_Point T = sequence_points_liste_vers_tableau(al->data);

        //Simplification des contours par courbe de bezier de degre 2 via Douglas Peucker algorithm
        el = simplification_douglas_peucker_bezier2(al->data, 0,(T.taille)-1, d);

        //Ajout des contours simplifies dans la liste chaine de contours simplifies en format points dynamics
        ajouter_element_liste_Contours(&simple, el);
        al = al->suiv;
    }

    //Affichage des donnes apres la simplification 
    contours_data_bezier(simple);

    //Creation du file_input postscript EPS pour visualisation 
    create_postscript_contours_bezier2(simple, exit_file, image_height(I), image_width(I), "simplifications/bezier/"); //Mode remplisage seulment

    //Preparation de la command pour effectuer une visualization via Evince
    char command[100];
    strcpy(command, "evince simplifications/bezier/");
    strcat(command, exit_file);
    strcat(command, ".eps &"); //tout en autorisant la completion de la commande d'etre completé au background

    //Appell Evince et affiche rmessage de verification
    system(command);
    printf("Simplified image is saved at simplifications/bezier/%s.eps and it is now opened on an Evince window.", exit_file);

    return 0;

}

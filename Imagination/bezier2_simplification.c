// #############################################################################
// # File bezier2_simplification.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file bezier2_simplification.c
 * @brief Application de bezier2 sur codec-V1.pbm
 *
 */

#include <stdint.h>
#include <string.h>
#include<stdlib.h>

#include "contour.h"
#include "image.h"

/**
 * @brief Simplification de l'image codec-V1 selon les courbes de bezier de degre 2 tout en l'affichant grâce à Evince via terminal sub-process
 * 
 */
int main(int argc, char **argv)
{
    //Handling errors and wrong arguments
    if (argc != 2)
    {
        printf("Error receiving argument for bezier2_simplification\n");
        exit(-20);
    }

    //Image utilisé par defaut par le workflow automatic
    char name[9] = "codec-V1";

    //Distance seuil passé en argument
    double d = atof(argv[1]);

    char *file_input = "pbms/codec-V1.pbm";
    char exit_file[(strlen(name)+20)];

    //Creation du fichier de sortie des contours
    snprintf(exit_file, (strlen(name)+20), "%s-deg2-taille%.0f.txt", name, d );
    
    //Lecture de l'image capture par le workflow automatic (image_capture et image_processing)
    Image I;
    I = read_image_file(file_input);

    //Ceation d'une liste chaine de contours
    Liste_Contours liste;
    liste = creer_liste_Contours_vide();

    //Detection des contours et affichage des donnes avant la simplification
    liste = algo_contours(I);
    contours_data(liste);
    printf("\n");
    printf("\n");

    //Creation d'une liste chaine de contours pour sauvegarder les points simplifies
    printf("Apres la simplification par courbe de bezier de degre 2:\n");
    Liste_Contours simple;
    simple = creer_liste_Contours_vide();
    Contour el;
    el = creer_liste_Point_vide();


    //Initialisation de la cellule qui va faire la lecture de chaque case de la liste chaine
    Cellule_Liste_Contours *al;
    al = liste.first;
    while (al != NULL)
    {
        Tableau_Point T = sequence_points_liste_vers_tableau(al->data);

        //Simplification par courbe de bezier de degre 2
        el = simplification_douglas_peucker_bezier2(al->data, 0,(T.taille)-1, d);
        ajouter_element_liste_Contours(&simple, el);
        al = al->suiv;
    }

    //Affichage des donnes apres la simplification for terminal inspection. No logs saved in that case
    contours_data_bezier(simple);
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

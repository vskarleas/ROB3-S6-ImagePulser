// #############################################################################
// # File bezier3_simplification_manual.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################


/**
 * @file bezier3_simplification_manual.c
 * @brief Utilisation de bezier3_simplification en manuel
 *
 */

#include <stdint.h>
#include <string.h>
#include<stdlib.h>

#include "contour.h"
#include "image.h"

/**
 * @brief Verifier que la simplifcation par courbe bezier des degrees 3 soit valide
 *  
 */
int main(int argc, char **argv)
{
    printf("Here are the available images inside the PBM folder that you can use: \n\n");
    system("ls pbms");

    printf("\n==========================\nEnter the name of the image's file without any extension (pbm)\n");
    char name[256];
    double d = 0.0;
    scanf("%s", name);

    //Distance seuil passe en terminal
    printf("D=");
    scanf("%lf", &d);
    printf("\n");

    //Creation du nom de l'image via la concatenation des informations
    char *no_extension = strtok(name, ".");
    char *file_input = malloc(strlen("pbms/") + strlen(no_extension) + 4);
    strcpy(file_input, "pbms/");
    strcat(file_input, no_extension);
    strcat(file_input, ".pbm");

    char exit_file[(strlen(name)+20)];

    //Automatic traitment of output files (eps and txt)
    if (d != 0.5)
    {
        snprintf(exit_file, (strlen(name)+20), "%s-deg3-taille%.0f.txt", name, d );
    }
    else
    {
        snprintf(exit_file, (strlen(name)+20), "%s-deg3-taille%.0f-5.txt", name, d );
    }
    
    //Lecture de l'image choisi par l'utilisateur
    Image I;
    I = read_image_file(file_input);

    Liste_Contours liste;
    liste = creer_liste_Contours_vide();
    liste = algo_contours(I);
    contours_data(liste);
    printf("\n");
    printf("\n");

    //Creation d'une liste chaine de contours pour sauvegarder les points simplifies
    printf("Apres la simplification par courbe de bezier de degre 3:\n");
    Liste_Contours simple;
    simple = creer_liste_Contours_vide();

    //Creation du type de cellules pour la liste chaine des contours
    Contour el;
    el = creer_liste_Point_vide();

    Cellule_Liste_Contours *al;
    al = liste.first;
    while (al != NULL)
    {
        Tableau_Point T = sequence_points_liste_vers_tableau(al->data);

        //Simplification par courbe de bezier de degre 3
        el = simplification_douglas_peucker_bezier3(al->data, 0,(T.taille)-1, d);
        ajouter_element_liste_Contours(&simple, el);
        al = al->suiv;
    }

    //Affichage des donnes apres la simplification 
    contours_data_bezier3(simple);
    create_postscript_contours_bezier3(simple, exit_file, image_height(I), image_width(I), "simplifications/bezier/"); //Mode remplisage seulment

    //Preparing command for visualization via Evince
    char command[100];
    strcpy(command, "evince simplifications/bezier/");
    strcat(command, exit_file);
    strcat(command, ".eps &"); //tout en autorisant la completion de la commande d'etre completé au background

    //Appell Evince et affiche rmessage de verification
    system(command);
    printf("Simplified image is saved at simplifications/bezier/%s.eps and it is now opened on an Evince window.", exit_file);

    return 0;

}

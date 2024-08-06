#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @file previewer.c
 * @brief Ouverture de l'image codec-V1 via Evince sur le terminal
 *
 */

/**
 * @brief Affichage de l'image via l'interface graphique Evince
 * 
 */
int main(int argc, char **argv)
{
    //Preparing command for visualization via Evince
    char command[100];
    strcpy(command, "evince images/codec-V1.jpeg");

    //Appell Evince et affiche l'image codec-V1.jpeg à l'interieur du workflow automatic
    system(command);

    return 0;
}
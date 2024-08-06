// #############################################################################
// # File image.h
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file image.h
 * @brief Déclaration des fonctions pour image.c
 *
 */

#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "error.h"

/**
 * @enum Pixel
 * @brief Type énuméré représentant la couleur d'un pixel.
 *
 * Cette énumération définit deux valeurs possibles pour les pixels : BLANC (0) et NOIR (1).
 */
typedef enum {BLANC=0, NOIR=1} Pixel;

/**
 * @struct Image
 * @brief Structure représentant une image PBM.
 *
 * Cette structure contient les dimensions de l'image (hauteur et largeur) ainsi qu'un pointeur vers un tableau de pixels.
 */
typedef struct Image_
{
    UINT the_height_of_the_image; /**< Hauteur de l'image */
    UINT the_width_of_the_image;  /**< Largeur de l'image */
    Pixel* pointer_to_pixel_array; /**< Pointeur vers le tableau de pixels */
} Image;

/**
 * @brief Crée une image PBM de dimensions L x H avec tous les pixels blancs.
 *
 * @param L Largeur de l'image.
 * @param H Hauteur de l'image.
 * @return Objet Image représentant l'image créée.
 */
Image create_image(UINT L, UINT H);

/**
 * @brief Supprime l'image spécifiée.
 *
 * Cette fonction libère la mémoire allouée au tableau de pixels de l'image spécifiée.
 *
 * @param p_I Pointeur vers l'objet Image représentant l'image à supprimer.
 */
void delete_image(Image *p_I);

/**
 * @brief Renvoie la valeur du pixel aux coordonnées spécifiées dans l'image.
 *
 * Cette fonction récupère la valeur du pixel aux coordonnées spécifiées dans l'image.
 *
 * @param I Objet Image représentant l'image.
 * @param x La coordonnée x du pixel (basée sur 1).
 * @param y La coordonnée y du pixel (basée sur 1).
 * @return La valeur du pixel aux coordonnées spécifiées.
 *
 * Si les coordonnées spécifiées sont en dehors des limites de l'image, la fonction renvoie la valeur d'un pixel blanc.
 */
Pixel get_pixel_image(Image I, int x, int y);

/**
 * @brief Change la valeur du pixel aux coordonnées spécifiées dans l'image.
 *
 * Cette fonction modifie la valeur du pixel aux coordonnées spécifiées dans l'image à la valeur spécifiée.
 *
 * @param I Objet Image représentant l'image.
 * @param x La coordonnée x du pixel (basée sur 1).
 * @param y La coordonnée y du pixel (basée sur 1).
 * @param v La valeur à laquelle définir le pixel.
 *
 * Si les coordonnées spécifiées sont en dehors des limites de l'image, la fonction ne fait rien.
 */
void set_pixel_image(Image I, int x, int y, Pixel v);

/**
 * @brief Renvoie la largeur de l'image spécifiée.
 *
 * @param I Objet Image représentant l'image.
 * @return Largeur de l'image.
 */
UINT image_width(Image I);

/**
 * @brief Renvoie la hauteur de l'image spécifiée.
 *
 * @param I Objet Image représentant l'image.
 * @return Hauteur de l'image.
 */
UINT image_height(Image I);

/**
 * @brief Lit une image PBM à partir du file_input spécifié.
 *
 * Cette fonction lit une image PBM à partir du file_input spécifié et la renvoie en tant qu'objet Image.
 * Elle prend en charge les file_inputs avec les en-têtes suivant :
 * - Ligne 1 : P1 ou P4
 * - Zéro, une ou plusieurs lignes commençant par #
 * - Zéro, un ou plusieurs séparateurs
 * - Largeur de l'image
 * - Un ou plusieurs séparateurs
 * - Hauteur de l'image
 * - Un ou plusieurs séparateurs
 * - Pixels de l'image
 *
 * @param name_f Le nom du file_input contenant l'image PBM.
 * @return Objet Image représentant l'image lue.
 */
Image read_image_file(char *name_f);

/**
 * @brief Lit une image PBM à partir du file_input spécifié qui est codé sous le codec P1.
 *
 * Cette fonction lit une image PBM à partir du file_input spécifié et la renvoie en tant qu'objet Image.
 *
 * @param name_f Le nom du file_input contenant l'image PBM.
 * @return Objet Image représentant l'image lue.
 */
Image read_image_file_P1(char *name_f);

/**
 * @brief Lit une image PBM à partir du file_input spécifié qui est codé sous le codec P4.
 *
 * Cette fonction lit une image PBM à partir du file_input spécifié et la renvoie en tant qu'objet Image.
 *
 * @param name_f Le nom du file_input contenant l'image PBM.
 * @return Objet Image représentant l'image lue.
 */
Image read_image_file_P4(char *name_f);

/**
 * @brief Affiche l'image spécifiée à l'écran.
 *
 * Cette fonction affiche l'image spécifiée sur le terminal.
 *
 * @param I Objet Image représentant l'image à afficher.
 */
void image_to_terminal(Image I);

/**
 * @brief Calcule l'image négative de l'image spécifiée.
 *
 * Cette fonction calcule et renvoie l'image négative de l'image spécifiée. L'image d'origine n'est pas modifiée.
 *
 * @param I Objet Image représentant l'image d'origine.
 * @return Objet Image représentant l'image négative.
 */
Image negative_image(Image I);

#endif /* _IMAGE_H_ */


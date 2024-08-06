// #############################################################################
// # File contour.h
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file contour.h
 * @brief Déclaration des fonctions pour contour.c
 *
 */

#ifndef _CONTOUR_H_
#define _CONTOUR_H_

#include <stdbool.h>
#include "geometry.h"
#include "image.h"
#include "sequence_point.h"

typedef enum {Nord, Est, Sud, Ouest} Orientation;

typedef struct {
  int x, y;
  Orientation o;
} Robot;

/**
 * @brief Initialise le robot à une position donnée avec une orientation spécifique.
 * 
 * @param r Pointeur vers le robot à initialiser.
 * @param x Position horizontale de départ du robot.
 * @param y Position verticale de départ du robot.
 * @param o Orientation initiale du robot.
 */

void init_robot(Robot *r, int x, int y, Orientation o);

/**
 * @brief Avance le robot d'une position dans la direction de son orientation actuelle.
 * 
 * @param r Pointeur vers le robot à déplacer.
 */

void move_forward(Robot *r);

/**
 * @brief Tourne le robot à gauche (changement d'orientation).
 * 
 * @param r Pointeur vers le robot à tourner.
 */

void turn_left(Robot *r);

/**
 * @brief Tourne le robot à droite (changement d'orientation).
 * 
 * @param r Pointeur vers le robot à tourner.
 */

void turn_right(Robot *r);

/**
 * @brief Récupère la position actuelle du robot.
 * 
 * @param r Pointeur vers le robot dont la position est demandée.
 * @param x Pointeur pour stocker la coordonnée x de la position.
 * @param y Pointeur pour stocker la coordonnée y de la position.
 */

void position(Robot *r, int *x, int *y);

/**
 * @brief Récupère la coordonnée x de la position actuelle du robot.
 * 
 * @param r Pointeur vers le robot concerné.
 * @return Coordonnée x de la position du robot.
 */

int abscissa(Robot *r);

/**
 * @brief Récupère la coordonnée y de la position actuelle du robot.
 * 
 * @param r Pointeur vers le robot concerné.
 * @return Coordonnée y de la position du robot.
 */
int ordinate(Robot *r);

/**
 * @brief Récupère l'orientation actuelle du robot.
 * 
 * @param r Pointeur vers le robot.
 * @return Orientation actuelle du robot.
 */
Orientation orient(Robot *r);


/**
 * @brief Récupère la position de la case directement devant le robot.
 * 
 * @param r Pointeur vers le robot.
 * @param x Pointeur pour stocker la coordonnée x de la case devant.
 * @param y Pointeur pour stocker la coordonnée y de la case devant.
 */
void position_forward(Robot *r, int *x, int *y);


/**
 * @brief Calcule la nouvelle orientation du robot en fonction de son environnement immédiat.
 * 
 * @param r Pointeur vers le robot.
 * @param x Coordonnée x de la case à examiner.
 * @param y Coordonnée y de la case à examiner.
 * @param I Image dans laquelle le robot évolue.
 */
void new_orientation(Robot *r, int x, int y, Image I);

/**
 * @brief Trouve les coordonnées du premier pixel noir avec un voisin blanc au-dessus.
 * 
 * @param I Image à examiner.
 * @return Point Coordonnées du pixel de départ trouvé.
 */
Point find_departure_pixel(Image I);

/**
 * @brief Crée un masque de l'image mettant en évidence les pixels de départ pour les contours.
 * 
 * @param I Image originale.
 * @return Image Masque créé.
 */
Image mask_image(Image I);

/**
 * @brief Vérifie si l'image est entièrement blanche.
 * 
 * @param I Image à vérifier.
 * @return true Si l'image est entièrement blanche, false sinon.
 */
bool image_white(Image I);

/**
 * @brief Calcule et extrait les contours d'une image.
 * 
 * @param I Image à traiter.
 * @param file_name Nom de file_input de sauvegarde des résultats.
 * @param repository Chemin du dossier de sauvegarde.
 * @return Contour Premier contour trouvé dans l'image.
 */
Contour algo_contour(Image I, char *file_name, char *repository);

/**
 * @brief Extrait tous les contours d'une image.
 * 
 * @param I Image à traiter.
 * @return Liste_Contours Liste de tous les contours trouvés.
 */
Liste_Contours algo_contours(Image I);

/**
 * @brief Sauvegarde les contours extraits dans un file_input texte.
 * 
 * @param c Liste des contours à sauvegarder.
 * @param file_name Nom du file_input.
 * @param repository Chemin du dossier de sauvegarde.
 */
void pbm_contour_to_txt(Liste_Contours c, char *file_name, char *repository);

/**
 * @brief Affiche les données des contours sur le terminal.
 *
 * Cette fonction imprime des informations détaillées sur chaque contour de la liste, telles que le nombre de points par contour,
 * directement sur le terminal pour une référence rapide et le débogage.
 *
 * @param c Liste des contours dont les données doivent être affichées.
 */
void contours_data(Liste_Contours c);

/**
 * @brief Affiche les données des contours simplifiés sur le terminal.
 *
 * Destinée à être utilisée après l'application d'un algorithme de simplification aux contours, cette fonction imprime le nombre réduit
 * de points par contour sur le terminal.
 *
 * @param c Liste des contours simplifiés.
 */
void contours_data_simplification(Liste_Contours c);

/**
 * @brief Affiche des informations sur les courbes de Bézier pour les contours sur le terminal.
 *
 * Spécifique à la tâche 7.1, cette fonction imprime des détails sur l'approximation des contours utilisant des courbes de Bézier de degré 2.
 *
 * @param c Liste des contours approximés à l'aide de courbes de Bézier.
 */
void contours_data_bezier(Liste_Contours c);

/**
 * @brief Affiche des informations sur les courbes de Bézier de degré 3 sur le terminal.
 *
 * Spécifique à la tâche 7.2, cette fonction fournit des détails sur les contours approximés utilisant des courbes de Bézier de degré 3.
 *
 * @param c Liste des contours approximés à l'aide de courbes de Bézier.
 */
void contours_data_bezier3(Liste_Contours c);

/**
 * @brief Génère un file_input EPS contenant la représentation graphique d'un contour en mode trait.
 *
 * @param c Contour à représenter.
 * @param file_name Nom du file_input EPS.
 * @param height Hauteur de l'image.
 * @param width Largeur de l'image.
 */
void create_postscript(Contour c, char *file_name, int height, int width);

/**
 * @brief Génère un file_input EPS contenant la représentation graphique d'un contour en mode remplissage.
 *
 * @param c Contour à remplir.
 * @param file_name Nom du file_input EPS.
 * @param height Hauteur de l'image.
 * @param width Largeur de l'image.
 */
void create_postscript_fill(Contour c, char *file_name, int height, int width);

/**
 * @brief Génère un file_input EPS pour une liste de contours donnés.
 *
 * @param c Liste des contours.
 * @param file_name Nom du file_input.
 * @param height Hauteur de l'image.
 * @param width Largeur de l'image.
 * @param repository Emplacement de sauvegarde.
 */
void create_postscript_contours(Liste_Contours c, char *file_name, int height, int width, char *repository);

/**
 * @brief Simplifie un contour en utilisant la méthode de simplification des segments de Douglas-Peucker.
 *
 * @param T Tableau de points du contour.
 * @param j1 Indice de début du segment à simplifier.
 * @param j2 Indice de fin du segment à simplifier.
 * @param d Seuil de distance pour la simplification.
 * @return Contour Contour simplifié.
 */
Contour simplification_douglas_peucker(Tableau_Point T, int j1, int j2, double d);

/**
 * @brief Calcule le point sur une courbe de Bézier de degré 2.
 *
 * @param b2 Courbe de Bézier de degré 2.
 * @param t Paramètre t, 0 ≤ t ≤ 1.
 * @return Point Point sur la courbe.
 */
Point calcul_ct_bezier2(Bezier2 b2, double t);

/**
 * @brief Calcule le point sur une courbe de Bézier de degré 3.
 *
 * @param b3 Courbe de Bézier de degré 3.
 * @param t Paramètre t, 0 ≤ t ≤ 1.
 * @return Point Point sur la courbe.
 */
Point calcul_ct_bezier3(Bezier3 b3, double t);

/**
 * @brief Convertit une courbe de Bézier de degré 2 en une courbe de degré 3.
 *
 * @param b2 Courbe de Bézier de degré 2 à convertir.
 * @return Bezier3 Courbe de Bézier de degré 3 résultante.
 */
Bezier3 conversion_bezier2_to_bezier3 (Bezier2 b2);

/**
 * @brief Approxime un contour par une courbe de Bézier de degré 2.
 *
 * @param c Contour à approximer.
 * @param j1 Indice de début du contour.
 * @param j2 Indice de fin du contour.
 * @return Bezier2 Courbe de Bézier de degré 2 résultante.
 */
Bezier2 bezier2_approximation(Contour c, int j1, int j2);

/**
 * @brief Calcule la distance entre un point et une courbe de Bézier de degré 2.
 *
 * @param P1 Point à mesurer.
 * @param b2 Courbe de Bézier de degré 2.
 * @param ti Paramètre t, 0 ≤ t ≤ 1, pour le calcul sur la courbe.
 * @return double Distance calculée.
 */
double distance_point_bezier2(Point P1, Bezier2 b2, double ti);

/**
 * @brief Simplifie un contour par la méthode des courbes de Bézier de degré 2.
 *
 * @param C Contour à simplifier.
 * @param j1 Indice de début du contour.
 * @param j2 Indice de fin du contour.
 * @param d Seuil de distance pour la simplification.
 * @return Contour Contour simplifié.
 */
Contour simplification_douglas_peucker_bezier2(Contour C, int j1, int j2,double d);

/**
 * @brief Crée un file_input EPS pour des courbes de Bézier de degré 2.
 *
 * @param c Liste des contours.
 * @param file_name Nom du file_input.
 * @param height Hauteur de l'image.
 * @param width Largeur de l'image.
 * @param repository Emplacement de sauvegarde.
 */
void create_postscript_contours_bezier2(Liste_Contours c, char *file_name, int height, int width, char *repository);

/**
 * @brief Approxime un contour par une courbe de Bézier de degré 3.
 *
 * @param c Contour à approximer.
 * @param j1 Indice de début du contour.
 * @param j2 Indice de fin du contour.
 * @return Bezier3 Courbe de Bézier de degré 3 résultante.
 */
Bezier3 bezier3_approximation(Contour c, int j1, int j2);

/**
 * @brief Calcule la distance entre un point et une courbe de Bézier de degré 3.
 *
 * @param P1 Point à mesurer.
 * @param b3 Courbe de Bézier de degré 3.
 * @param ti Paramètre t, 0 ≤ t ≤ 1, pour le calcul sur la courbe.
 * @return double Distance calculée.
  */
double distance_point_bezier3(Point P1, Bezier3 b3, double ti);

/**
 * @brief Simplifie un contour par la méthode des courbes de Bézier de degré 3.
 *
 * @param C Contour à simplifier.
 * @param j1 Indice de début du contour.
 * @param j2 Indice de fin du contour.
 * @param d Seuil de distance pour la simplification.
 * @return Contour Contour simplifié.
 */
Contour simplification_douglas_peucker_bezier3(Contour C, int j1, int j2,double d);

/**
 * @brief Crée un file_input EPS pour des courbes de Bézier de degré 3.
 *
 * @param c Liste des contours.
 * @param file_name Nom du file_input.
 * @param height Hauteur de l'image.
 * @param width Largeur de l'image.
 * @param repository Emplacement de sauvegarde.
 */
void create_postscript_contours_bezier3(Liste_Contours c, char *file_name, int height, int width, char *repository);

#endif /* _CONTOUR_H_ */
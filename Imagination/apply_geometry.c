// #############################################################################
// # File apply_geometry.c
// # Projet en C - Polytech Sorbonne - 2023/2024 - S6
// # Auteurs : Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - Tous droits réservés.
// #############################################################################

/**
 * @file apply_geometry.c
 * @brief Tests pour les fonctions de géometrie 2D du fichier geometry.c
 *
 */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "geometry.h"

/**
 * @brief Utilisé pour implémenter des tests concernant les opérations d'algèbre linéaire.
 * 
 */
int main(int argc, char **argv)
{
    printf("Test des fonctions de géométrie dans le plan à deux dimensions\n");

    // Test numéro 3

    /* Initialisation des points pour les tests */
    Point A, B, C;
    A = set_point(1.0, -3.0);
    B = set_point(4.0, 1.0);
    C = add_point(A, B);
    printf("Points utilisés dans ce test :\n");
    printf("A : (%f, %f)\n", A.x, A.y);
    printf("B : (%f, %f)\n", B.x, B.y);
    printf("==========\n");
    printf("Test de l'addition de points\n");
    printf("%f %f \n", C.x, C.y);
    printf("\n");

    printf("\n");
    printf("----------\n");

    /* Initialisation des vecteurs pour les tests */
    Vecteur V, I, Z;
    V = set_vecteur(1.0, 2.0);
    I = set_vecteur(0.0, 5.0);
    printf("Vecteurs utilisés dans ce test :\n");
    printf("Vecteur V : (%f -> %f)\n", V.x, V.y);
    printf("Vecteur I : (%f -> %f)\n", I.x, I.y);
    printf("==========\n");
    Z = add_vecteur(V, I);
    printf("Test de l'addition de vecteurs\n");
    printf("%f %f \n", Z.x, Z.y);
    printf("\n");

    double a = 3; // Scalaire utilisé pour les opérations
    Z = produit_vect(V, a);
    printf("Test de la multiplication d'un vecteur par un scalaire\n");
    printf("%f %f \n", Z.x, Z.y);
    printf("\n");

    C = produit(A, a);
    printf("Test de la multiplication d'un point par un scalaire\n");
    printf("%f %f \n", C.x, C.y);
    printf("\n");

    double res;
    res = produit_scalaire(V, I);
    printf("Test du produit scalaire\n");
    printf("%f \n", res);
    printf("\n");

    res = norm(I);
    printf("Test de la norme d'un vecteur\n");
    printf("%f \n", res);
    printf("\n");

    res = distance(A, B);
    printf("Test de la distance entre deux points\n");
    printf("%f \n", res);
    printf("\n");

    // Test numéro 8
    printf("Test de la distance point-segment pour la Tâche 6\n");
    Segment S;
    S.A = set_point(0.0, 6.0);
    S.B = set_point(0.0, 6.0);
    printf("Points utilisés dans ce test :\n");
    printf("A : (%f, %f)\n", S.A.x, S.A.y);
    printf("B : (%f, %f)\n", S.B.x, S.B.y);
    printf("==========\n");
    Point P1 = set_point(0.00, 6.0);
    double distance_seg = distance_point_segment(P1, S);
    printf("%f distance point-segment\n\n", distance_seg);
}

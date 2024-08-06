// #############################################################################
// # File test_approx3.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file test_approx3.c
 * @brief Test pour l'approximation d'un segment pour une courbe de Bézier de degré 3
 *
 */

#include <stdint.h>
#include <string.h>
#include<stdlib.h>

#include "contour.h"
#include "image.h"

/* Test qui nous aide à verfier si la fonction bezier3_approximation
(approximation de contours vers courbe bezier 3) est correct */
int main(int argc, char **argv)
{
    // Test number 10
    printf("Starting Test 10\n");
    //Cas pour deux points
    printf("For n = 1\n");
    Contour c;
    c = creer_liste_Point_vide();
    int i = 0;
    while (i<=1)
    {
        Point A;
        double x, y;
        printf("x pour point A:\n");
        scanf("%lf", &x);
        printf("y pour point A:\n");
        scanf("%lf", &y);
        A = set_point(x, y);
        ajouter_element_liste_Point(&c,A);
        printf("================================================\n");
        i++;
    }
    Bezier3 b3;
    int j1, j2;
    printf("j1:\n");
    scanf("%d", &j1);
    printf("j2:\n");
    scanf("%d", &j2);
    b3 = bezier3_approximation(c, j1, j2);
    printf("--------------------------------\n");
    printf("C0: (%f, %f)\n", b3.A.x, b3.A.y);
    printf("C1: (%f, %f)\n", b3.B.x, b3.B.y);
    printf("C2: (%f, %f)\n", b3.C.x, b3.C.y);
    printf("C3: (%f, %f)\n", b3.D.x, b3.D.y);

    printf("\n\n");
    // Test number 11
    printf("Starting Test 11\n");
    //Cas pour trois points
    printf("For n = 2\n");
    c = creer_liste_Point_vide();
    i = 0;
    while (i<=2)
    {
        Point A;
        double x, y;
        printf("x pour point A:\n");
        scanf("%lf", &x);
        printf("y pour point A:\n");
        scanf("%lf", &y);
        A = set_point(x, y);
        ajouter_element_liste_Point(&c,A);
        printf("================================================\n");
        i++;
    }
    printf("j1:\n");
    scanf("%d", &j1);
    printf("j2:\n");
    scanf("%d", &j2);
    b3 = bezier3_approximation(c, j1, j2);
    printf("--------------------------------\n");
    printf("C0: (%f, %f)\n", b3.A.x, b3.A.y);
    printf("C1: (%f, %f)\n", b3.B.x, b3.B.y);
    printf("C2: (%f, %f)\n", b3.C.x, b3.C.y);
    printf("C3: (%f, %f)\n", b3.D.x, b3.D.y);

    printf("\n\n");

    // Test number 12
    printf("Starting Test 12\n");
    printf("For n = >=3\n");
    c = creer_liste_Point_vide();
    i = 0;
    //On donne 8 points (comme l'exemple sur le poly)
    while (i<=8)
    {
        Point A;
        double x, y;
        printf("x pour point A:\n");
        scanf("%lf", &x);
        printf("y pour point A:\n");
        scanf("%lf", &y);
        A = set_point(x, y);
        ajouter_element_liste_Point(&c,A);
        printf("================================================\n");
        i++;
    }
    printf("j1:\n");
    scanf("%d", &j1);
    printf("j2:\n");
    scanf("%d", &j2);
    b3 = bezier3_approximation(c, j1, j2);
    printf("--------------------------------\n");
    printf("C0: (%f, %f)\n", b3.A.x, b3.A.y);
    printf("C1: (%f, %f)\n", b3.B.x, b3.B.y);
    printf("C2: (%f, %f)\n", b3.C.x, b3.C.y);
    printf("C3: (%f, %f)\n", b3.D.x, b3.D.y);

    return 0;

}

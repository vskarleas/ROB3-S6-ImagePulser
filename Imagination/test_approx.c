// #############################################################################
// # File test_approx.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file test_approx.c
 * @brief Test pour l'approximation d'un segment pour une courbe de Bézier de degré 2
 *
 */

#include <stdint.h>
#include <string.h>
#include<stdlib.h>

#include "contour.h"
#include "image.h"

/* Test qui nous aide à verfier si la fonction bezier2_approximation
(approximation de contours vers courbe bezier 2) est correct */
int main(int argc, char **argv)
{
    // Test number 9
    printf("Starting Test 9\n");
    Contour c;
    c = creer_liste_Point_vide();
    int i = 0;
    
    //Donner 8 points (comme l'exemple sur le Poly)
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
    Bezier2 b2;
    int j1, j2;
    printf("j1:\n");
    scanf("%d", &j1);
    printf("j2:\n");
    scanf("%d", &j2);
    b2 = bezier2_approximation(c, j1, j2);
    printf("--------------------------------\n");
    printf("C0: (%f, %f)\n", b2.A.x, b2.A.y);
    printf("C1: (%f, %f)\n", b2.B.x, b2.B.y);
    printf("C2: (%f, %f)\n", b2.C.x, b2.C.y);

    return 0;

}

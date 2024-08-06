// #############################################################################
// # File geometry.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file geometry.c
 * @brief Déclaration de toutes les fonctions de la géometrie en 2D
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include "geometry.h"
/* 2D Geometry Tools */

/**
 * @brief Définir les coordonnées d'un point
 *
 * @param x Coordonnée sur l'axe x
 * @param y Coordonnée sur l'axe y
 * @return Point Un point avec les coordonnées (x, y)
 */

Point set_point(double x, double y)
{
    Point P = {x,y};
    return P;
}

/**
 * @brief Définir les coordonnées d'un vecteur
 *
 * @param x Coordonnée sur l'axe x
 * @param y Coordonnée sur l'axe y
 * @return Vecteur Un vecteur avec les coordonnées (x, y)
 */

Vecteur set_vecteur(double x, double y)
{
    Vecteur V = {x,y};
    return V;
}

/**
 * @brief Addition de deux points
 * 
 * @param P1 Premier point
 * @param P2 Deuxième point
 * @return Point Le point résultant de l'addition des deux points
 */
Point add_point(Point P1, Point P2)
{
    return set_point(P1.x+P2.x, P1.y+P2.y);
}


/**
 * @brief Addition de deux vecteurs
 * 
 * @param V1 Premier vecteur
 * @param V2 Deuxième vecteur
 * @return Vecteur Le vecteur résultant de l'addition des deux vecteurs
 */
Vecteur add_vecteur(Vecteur V1, Vecteur V2)
{
    return set_vecteur(V1.x+V2.x, V1.y+V2.y);
}

/**
 * @brief Vecteur entre deux points
 * 
 * @param A Premier point
 * @param B Deuxième point
 * @return Vecteur Le vecteur allant de A à B
 */
Vecteur vect_bipoint(Point A, Point B)
{
    Vecteur V = {B.x-A.x, B.y-A.y};
    return V;
}

/**
 * @brief Produit d'un point et d'un nombre réel
 * 
 * @param P1 Un point
 * @param a Un nombre réel
 * @return Point Le point résultant du produit scalaire
 */
Point produit(Point P1, double a)
{
    return set_point(a*P1.x, a*P1.y);
}

/**
 * @brief Produit d'un vecteur et d'un nombre réel
 * 
 * @param V1 Un vecteur
 * @param a Un nombre réel
 * @return Vecteur Le vecteur résultant du produit scalaire
 */
Vecteur produit_vect(Vecteur V1, double a)
{
    return set_vecteur(a*V1.x, a*V1.y);
}

/**
 * @brief Produit scalaire de deux vecteurs
 * 
 * @param V1 Premier vecteur
 * @param V2 Deuxième vecteur
 * @return double Le produit scalaire des deux vecteurs
 */
double produit_scalaire(Vecteur V1, Vecteur V2)
{
    return (V1.x*V2.x + V1.y*V2.y);
}

/**
 * @brief Norme d'un vecteur
 * 
 * @param V1 Un vecteur
 * @return double La norme du vecteur
 */
double norm(Vecteur V1)
{
    return (sqrt(V1.x*V1.x + V1.y*V1.y ));
}


/**
 * @brief Distance entre deux points
 * 
 * @param P1 Premier point
 * @param P2 Deuxième point
 * @return double La distance entre les deux points
 */
double distance(Point P1, Point P2)
{
    return(sqrt((P1.x-P2.x)*(P1.x-P2.x) + (P1.y-P2.y)*(P1.y-P2.y)));
}


/**
 * @brief Création d'un vecteur à partir de deux points
 * 
 * @param P1 Premier point
 * @param P2 Deuxième point
 * @return Vecteur Le vecteur créé à partir des deux points
 */
Vecteur vector_creation(Point P1, Point P2)
{
    Vecteur V;
    double res = P2.x - P1.x;
    V = set_vecteur(res, P2.y - P1.y);
    return V;
}


/**
 * @brief Distance entre un point et un segment
 * 
 * @param P1 Un point
 * @param S1 Un segment
 * @return double La distance entre le point et le segment
 */
double distance_point_segment(Point P1, Segment S1)
{
    if ((S1.A.x == S1.B.x) && (S1.A.y == S1.B.y))
    {
        return distance(P1, S1.B);
    }
    else 
    {
        double λ;

        //Details de la formule mathematique sur la documentation .
        Vecteur AP;
        Vecteur AB;
        AP = vector_creation(S1.A, P1);
        AB = vector_creation(S1.A, S1.B);
        λ = produit_scalaire(AP, AB)/produit_scalaire(AB, AB);
        if (λ < 0)
        {
            return distance(P1, S1.A);
        }
        if (λ > 1)
        {
            return distance(P1, S1.B);
        }
        else
        {
            Point Q;
            Point q;
            q = set_point(S1.B.x-S1.A.x, S1.B.y-S1.A.y);
            q = produit(q, λ);
            Q = add_point(S1.A, q);
            return distance(Q, P1);
        }
    }
}

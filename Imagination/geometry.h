// #############################################################################
// # File geometry.h
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file geometry.h
 * @brief Déclaration des fonctions pour geometry.c
 *
 */

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

//Type Vecteur 

/**
 * @brief Type Vecteur
 * 
 * Représente un vecteur en deux dimensions avec les coordonnées x et y.
 */
typedef struct Vecteur_
{
   double x,y;
} Vecteur;

/**
 * @brief Type Point
 * 
 * Représente un point en deux dimensions avec les coordonnées x et y.
 */
 typedef struct Point_
{
   double x,y;
} Point;

/**
 * @brief Profil d'un segment
 * 
 * Représente un segment de droite défini par deux points A et B.
 */
typedef struct Segment_
{
   Point A, B;
} Segment;

/**
 * @brief Profil d'une courbe de Bézier de degré 2
 * 
 * Représente une courbe de Bézier quadratique définie par trois points A, B et C.
 */
typedef struct Bezier2_
{
   Point A, B, C;
} Bezier2;

/**
 * @brief Profil d'une courbe de Bézier de degré 3
 * 
 * Représente une courbe de Bézier cubique définie par quatre points A, B, C et D.
 */
typedef struct Bezier3_
{
   Point A, B, C, D;
} Bezier3;

/**
 * @brief Initialisation d'un point
 * 
 * @param x Coordonnée x du point
 * @param y Coordonnée y du point
 * @return Point Le point créé avec les coordonnées spécifiées
 */
Point set_point(double x, double y);

/**
 * @brief Initialisation d'un vecteur
 * 
 * @param x Coordonnée x du vecteur
 * @param y Coordonnée y du vecteur
 * @return Vecteur Le vecteur créé avec les coordonnées spécifiées
 */
Vecteur set_vecteur(double x, double y);

/**
 * @brief Addition de deux points
 * 
 * @param P1 Premier point
 * @param P2 Deuxième point
 * @return Point Le point résultant de l'addition des deux points
 */
Point add_point(Point P1, Point P2);

/**
 * @brief Addition de deux vecteurs
 * 
 * @param V1 Premier vecteur
 * @param V2 Deuxième vecteur
 * @return Vecteur Le vecteur résultant de l'addition des deux vecteurs
 */
Vecteur add_vecteur(Vecteur V1, Vecteur V2);

/**
 * @brief Création d'un vecteur à partir de deux points
 * 
 * @param A Premier point
 * @param B Deuxième point
 * @return Vecteur Le vecteur créé à partir des deux points
 */
Vecteur vect_bipoint(Point A, Point B);

/**
 * @brief Produit d'un point avec un nombre réel
 * 
 * @param P1 Le point
 * @param a Le scalaire
 * @return Point Le point résultant du produit scalaire
 */
Point produit(Point P1, double a);

/**
 * @brief Produit d'un vecteur avec un nombre réel
 * 
 * @param V1 Le vecteur
 * @param a Le scalaire
 * @return Vecteur Le vecteur résultant du produit scalaire
 */
Vecteur produit_vect(Vecteur V1, double a);

/**
 * @brief Produit scalaire de deux vecteurs
 * 
 * @param V1 Premier vecteur
 * @param V2 Deuxième vecteur
 * @return double Le produit scalaire des deux vecteurs
 */
double produit_scalaire(Vecteur V1, Vecteur V2);

/**
 * @brief Norme d'un vecteur
 * 
 * @param V1 Le vecteur
 * @return double La norme du vecteur
 */
double norm(Vecteur V1);

/**
 * @brief Distance entre deux points
 * 
 * @param P1 Premier point
 * @param P2 Deuxième point
 * @return double La distance entre les deux points
 */
double distance(Point P1, Point P2);

/**
 * @brief Création d'un vecteur à partir de deux points
 * 
 * @param P1 Premier point
 * @param P2 Deuxième point
 * @return Vecteur Le vecteur créé à partir des deux points
 */
Vecteur vector_creation(Point P1, Point P2);

/**
 * @brief Distance entre un point et un segment
 * 
 * @param P1 Un point
 * @param S1 Un segment
 * @return double La distance entre le point et le segment
 */
double distance_point_segment(Point P1, Segment S1);

#endif /* _GEOM2D_H_ */

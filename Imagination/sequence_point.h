// #############################################################################
// # File sequence_point.h
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file sequence_point.h
 * @brief Déclaration des fonctions pour sequence_point.c
 *
 */

#include<stdio.h>  /* utilisation des entr�es-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */

#include "geometry.h"

/*---- le type cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
	Point data;    /* donn�e de l'�l�ment de liste */
	struct Cellule_Liste_Point_* suiv; /* pointeur sur l'�l�ment suivant */
} Cellule_Liste_Point;

/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
	unsigned int taille;        /* nombre d'�l�ments dans la liste */
	Cellule_Liste_Point *first; /* pointeur sur le premier �l�ment de la liste */
	Cellule_Liste_Point *last;  /* pointeur sur le dernier �l�ment de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Point;

/* Type de la cellule de la liste des contours */
typedef struct Cellule_Liste_Contours_
{
	Liste_Point data;    /* donn�e de l'�l�ment de liste */
	struct Cellule_Liste_Contours_* suiv; /* pointeur sur l'�l�ment suivant */
} Cellule_Liste_Contours;

/* Type de la luse des contours */
typedef struct Liste_Contours_
{
	unsigned int taille;        /* nombre d'�l�ments dans la liste */
	Cellule_Liste_Contours *first; /* pointeur sur le premier �l�ment de la liste */
	Cellule_Liste_Contours *last;  /* pointeur sur le dernier �l�ment de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Contours;

typedef Liste_Point Contour; /* type Contour = type Liste_Point */


/*---- le type tableau de point ----*/
typedef struct Tableau_Point_
{
	unsigned int taille; /* nombre d'�l�ments dans le tableau */
	Point *tab;          /* (pointeur vers) le tableau des �l�ments */
} Tableau_Point;

/* cr�er une cellule de liste avec l'�l�ment v 
   renvoie le pointeur sur la cellule de liste cr��e
   la fonction s'arrete si la cr�ation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v);

Cellule_Liste_Contours *creer_element_liste_Contours(Liste_Point v);

/* cr�er une liste vide */
Liste_Point creer_liste_Point_vide();

Liste_Contours creer_liste_Contours_vide();

/* ajouter l'�l�ment e en fin de la liste L, renvoie la liste L modifi�e */
void ajouter_element_liste_Point(Liste_Point *L, Point e);

void ajouter_element_liste_Contours(Liste_Contours *L, Liste_Point e);

/* suppression de tous les �l�ments de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L);

/* concat�ne L2 � la suite de L1, renvoie la liste L1 modifi�e */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);


/* cr�er une s�quence de points sous forme d'un tableau de points 
   � partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

/* �crire le contour L � l'�cran 
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acc�der aux �l�ments d'une
   s�quence de points par indice */
void ecrire_contour(Liste_Point L);
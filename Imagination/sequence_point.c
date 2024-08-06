// #############################################################################
// # File sequence_point.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file sequence_point.c
 * @brief Déclaration des macros telles que les listes chainées
 *
 */

#include<stdio.h>  /* utilisation des entrées-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */

#include "geometry.h"
#include "sequence_point.h"

/**
 * @brief Crée une cellule de liste avec l'élément v.
 * 
 * @param v L'élément à stocker dans la cellule de liste.
 * @return Le pointeur sur la cellule de liste créée.
 * @note La fonction s'arrête si la création n'a pas pu se faire.
 */
Cellule_Liste_Point *creer_element_liste_Point(Point v)
{
	Cellule_Liste_Point *el;
	el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-40);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}

/**
 * @brief Crée une cellule de liste des contours avec la liste de points v.
 * 
 * @param v Une liste de points.
 * @return Cellule_Liste_Contours* Pointeur sur la cellule de liste de contours créée.
 * @note La fonction s'arrête si la création n'a pas pu se faire.
 */
Cellule_Liste_Contours *creer_element_liste_Contours(Liste_Point v)
{
	Cellule_Liste_Contours *el;
	el = (Cellule_Liste_Contours *)malloc(sizeof(Cellule_Liste_Contours));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Contours : allocation impossible\n");
		exit(-50);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}

/**
 * @brief Crée une liste de points vide.
 * 
 * @return Liste_Point Une liste de points vide.
 */
Liste_Point creer_liste_Point_vide()
{
	Liste_Point L = {0, NULL, NULL};
	return L;
}

/**
 * @brief Crée une liste de contours vide.
 * 
 * @return Liste_Contours Une liste de contours vide.
 */
Liste_Contours creer_liste_Contours_vide()
{
	Liste_Contours L = {0, NULL, NULL};
	return L;
}

/**
 * @brief Ajoute l'élément e à la fin de la liste de points L.
 * 
 * @param L Pointeur sur la liste de points.
 * @param e L'élément à ajouter à la liste.
 */
void ajouter_element_liste_Point(Liste_Point *L, Point e)
{
	Cellule_Liste_Point *el;
	el = creer_element_liste_Point(e);
	if (L->taille == 0)
	{
		/* premier élément de la liste */
		L->first = L->last = el;
	}
	else
	{
		L->last->suiv = el;
		L->last = el;
	}
	L->taille++;
	return;
}

/**
 * @brief Ajoute un contour à la liste de contours L.
 * 
 * @param L Pointeur sur la liste de contours.
 * @param e Le contour à ajouter à la liste.
 */
void ajouter_element_liste_Contours(Liste_Contours *L, Liste_Point e)
{
	Cellule_Liste_Contours *el;
	el = creer_element_liste_Contours(e);
	if (L->taille == 0)
	{
		/* premier élément de la liste des contours */
		L->first = L->last = el;
	}
	else
	{
		L->last->suiv = el;
		L->last = el;
	}
	L->taille++;
	return;
}

/**
 * @brief Supprime tous les éléments de la liste de points et renvoie la liste vide.
 * 
 * @param L La liste de points à supprimer.
 * @return Liste_Point La liste de points vide.
 */
Liste_Point supprimer_liste_Point(Liste_Point L)
{
	Cellule_Liste_Point *el=L.first;
	while (el) 
	{		
		Cellule_Liste_Point *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

/**
 * @brief Concatène la liste L2 à la suite de la liste L1 et renvoie la liste L1 modifiée.
 * 
 * @param L1 La première liste de points.
 * @param L2 La deuxième liste de points.
 * @return Liste_Point La liste L1 modifiée.
 */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2)
{
	/* cas où l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier élément de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}

/**
 * @brief Crée une séquence de points sous forme d'un tableau de points à partir de la liste de points L.
 * 
 * @param L La liste de points.
 * @return Tableau_Point Le tableau de points créé à partir de la liste de points.
 */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L)
{
	Tableau_Point T;
	/* taille de T = taille de L */
	T.taille = L.taille;
	/* allocation dynamique du tableau de Point */
	T.tab = malloc(sizeof(Point) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arrêt du programme avec un message */
		fprintf(stderr, "sequence_points_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-60);
	}
	/* remplir le tableau de points T en parcourant la liste L */
	int k = 0; /* indice de l'élément dans T.tab */
	Cellule_Liste_Point *el = L.first; /* pointeur sur l'élément dans L */
	while (el) 
	{
		T.tab[k] = el->data;
		k++; /* incrémenter k */
		el = el->suiv; /* passer à l'élément suivant dans la liste chaînée */
	}
	return T;
}

/**
 * @brief Écrit le contour L à l'écran.
 * 
 * Cette fonction montre un exemple de conversion d'une liste de points en tableau de points afin de pouvoir par la suite accéder aux éléments d'une séquence de points par indice.
 * 
 * @param L La liste de points représentant le contour.
 */
void ecrire_contour(Liste_Point L)
{
	Tableau_Point TP = sequence_points_liste_vers_tableau(L);
	int k;
	int nP = TP.taille;
	printf("%d segments\n", nP-1);
	printf("%d points : [", nP);
	for (k = 0; k < nP; k++)
	{	
		Point P = TP.tab[k]; /* récupérer le point d'indice k */
		printf("(%5.1f,%5.1f)", P.x, P.y);
	} 
	printf("]\n");
	
	free(TP.tab); /* supprimer le tableau de points TP */
}




// int main()
// {
//	Contour C1,C2;
//	
//	/* initialiser C1 comme contour vide */
//	C1 = creer_liste_Point_vide();
//	printf("C1 : "); ecrire_contour(C1);
//
//	/* ajouter les points (5,3),(3,1),(7,2) et (1,6) dans C1 */
//	C1 = ajouter_element_liste_Point(C1, set_point(5.0,3.0));
//	C1 = ajouter_element_liste_Point(C1, set_point(3.0,1.0));
//	C1 = ajouter_element_liste_Point(C1, set_point(7.0,2.0));
//	C1 = ajouter_element_liste_Point(C1, set_point(1.0,6.0));
//	printf("C1 : "); ecrire_contour(C1);
//
//	/* ajouter le point (4,1) dans C1 */
//	C1 = ajouter_element_liste_Point(C1, set_point(4,1));
//	printf("C1 : "); ecrire_contour(C1);
//
//	/* cr�er le contour C2 avec les points (9,5) et (5,7) */
//	C2 = creer_liste_Point_vide();	
//	C2 = ajouter_element_liste_Point(C2, set_point(9,5));
//	C2 = ajouter_element_liste_Point(C2, set_point(5,7));
//	printf("C2 : "); ecrire_contour(C2);
//
//	/* concat�ner C2 � la suite de C1 */
//	C1 = concatener_liste_Point(C1,C2);
//	printf("C1 : "); ecrire_contour(C1);
//
//	/* supprimer le contour C1 */
//	C1 = supprimer_liste_Point(C1);
//	printf("C1 : "); ecrire_contour(C1);
// } // fin du programme

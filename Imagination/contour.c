// #############################################################################
// # File contour.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved
// #############################################################################

/**
 * @file contour.c
 * @brief Implémentation des fonctions de gestion d'un robot pour le tracé de contours dans une image.
 *
 * Ce file_input contient les définitions des fonctions nécessaires pour initialiser et manipuler
 * un robot chargé de lire et suivre les contours dans une image de type PBM (Portable Bitmap).
 */




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "geometry.h"
#include "contour.h"
#include "image.h"

/* Nous utilisons un robot pour lire les bits sur l'image pbm.
Il a besoin de coordonnées x, y et d'une orientation */

/**
 * @brief Initialise un robot avec les coordonnées et l'orientation spécifiées.
 * @param r Pointeur vers la structure Robot à initialiser.
 * @param x Coordonnée x de départ du robot.
 * @param y Coordonnée y de départ du robot.
 * @param o Orientation initiale du robot.
 * @details Cette fonction assigne la position et l'orientation initiales au robot.
 * Elle prépare le robot à naviguer dans l'image selon les consignes qui lui seront ultérieurement fournies.
 */

void init_robot(Robot *r, int x, int y, Orientation o)
{
    r->x = x;
    r->y = y;
    r->o = o;
}

/**
 * @brief Déplace le robot d'une position en avant selon son orientation.
 * @param r Pointeur vers la structure Robot.
 * @details Cette fonction modifie les coordonnées du robot en fonction de son orientation actuelle.
 * Elle permet au robot de progresser d'une unité dans la direction vers laquelle il est orienté.
 */

void move_forward(Robot *r)
{
    switch (r->o)
    {
    case Nord:
        
        r->y--;// Déplacement vers le haut.
        break;
    case Sud:
        
        r->y++;// Déplacement vers le bas.
        break;
    case Ouest:
       
        r->x--;// Déplacement vers la gauche.
        break;
    case Est:
        
        r->x++;// Déplacement vers la droite.
    }
}

/**
 * @brief Oriente le robot de 90 degrés vers la gauche par rapport à sa direction actuelle.
 * @param r Pointeur vers la structure Robot.
 * @details Cette fonction ajuste l'orientation du robot en tournant à gauche,
 * ce qui modifie son orientation de 90 degrés dans le sens antihoraire.
 */

void turn_left(Robot *r)
{
    switch (r->o)
    {
    case Nord:
        r->o = Ouest;
        break;
    case Ouest:
        r->o = Sud;
        break;
    case Sud:
        r->o = Est;
        break;
    case Est:
        r->o = Nord;
        break;
    }
}

/**
 * @brief Oriente le robot de 90 degrés vers la droite par rapport à sa direction actuelle.
 * @param r Pointeur vers la structure Robot.
 * @details Cette fonction ajuste l'orientation du robot en tournant à droite,
 * ce qui modifie son orientation de 90 degrés dans le sens horaire.
 */

void turn_right(Robot *r)
{
    switch (r->o)
    {
    case Nord:
        r->o = Est;
        break;
    case Ouest:
        r->o = Nord;
        break;
    case Sud:
        r->o = Ouest;
        break;
    case Est:
        r->o = Sud;
        break;
    }
}

/**
 * @brief Récupère et renvoie la position actuelle du robot.
 * @param r Pointeur vers la structure Robot.
 * @param x Pointeur vers la variable où sera stockée la position x actuelle.
 * @param y Pointeur vers la variable où sera stockée la position y actuelle.
 * @details Cette fonction permet d'accéder aux coordonnées actuelles du robot.
 */

void position(Robot *r, int *x, int *y)
{
    *x = r->x;
    *y = r->y;
}

/**
 * @brief Renvoie la coordonnée x de la position actuelle du robot.
 * @param r Pointeur vers la structure Robot.
 * @return La position x actuelle du robot.
 */

int abscissa(Robot *r)
{
    return r->x;
}

/**
 * @brief Renvoie la coordonnée y de la position actuelle du robot.
 * @param r Pointeur vers la structure Robot.
 * @return La position y actuelle du robot.
 */

int ordinate(Robot *r)
{
    return r->y;
}

/**
 * @brief Renvoie l'orientation actuelle du robot.
 * @param r Pointeur vers la structure Robot.
 * @return L'orientation actuelle du robot sous forme de valeur énumérée.
 */

Orientation orient(Robot *r)
{
    return r->o;
}

/**
 * @brief Calcule la position du pixel situé directement devant le robot.
 * @param r Pointeur vers le robot dont on souhaite connaître la position devant.
 * @param x Pointeur vers l'entier où stocker la coordonnée x du pixel devant le robot.
 * @param y Pointeur vers l'entier où stocker la coordonnée y du pixel devant le robot.
 * @details Cette fonction calcule la position du pixel devant le robot en fonction de son orientation actuelle
 * et met à jour les valeurs pointées par x et y avec les nouvelles coordonnées calculées.
 */

void position_forward(Robot *r, int *x, int *y)
{
    switch (r->o)
    {
    case Nord:
        *x = r->x;
        *y = r->y - 1; //prendre en compte la position du robot maintennt via r->y
        break;
    case Sud:
        *x = r->x;
        *y = r->y + 1;
        break;
    case Ouest:
        *x = r->x - 1;
        *y = r->y;
        break;
    case Est:
        *x = r->x + 1;
        *y = r->y;
    }
}
/**
 * @brief Détermine la nouvelle orientation du robot basée sur les pixels voisins.
 * @param r Pointeur vers le robot dont l'orientation doit être mise à jour.
 * @param x Coordonnée x du pixel actuel du robot.
 * @param y Coordonnée y du pixel actuel du robot.
 * @param I Image dans laquelle le robot opère.
 * @details Cette fonction ajuste l'orientation du robot en analysant les pixels voisins immédiats.
 * Le robot pivote en fonction de la couleur des pixels adjacents pour suivre le contour dans l'image.
 */

void new_orientation(Robot *r, int x, int y, Image I)
{
    Pixel pG;
    Pixel pD;
    switch (r->o)
    {
        // On traite les differents cas pour chaque orintation par rapport à la position du prochaine pixel noir
    case (Est):
        // Formule pour le calcul du voisin d’un pixel (x, y).
        // La logique est la même pour chaque orientation
        pG = get_pixel_image(I, x + 1, y);
        pD = get_pixel_image(I, x + 1, y + 1);
        if (pG == NOIR)
        {
            r->o = Nord;
            break;
        }
        else if (pD == BLANC)
        {
            r->o = Sud;
            break;
        }
        else
        {
            break;
        }
    case (Nord):
        pG = get_pixel_image(I, x, y);
        pD = get_pixel_image(I, x + 1, y);
        if (pG == NOIR)
        {
            r->o = Ouest;
            break;
        }
        else if (pD == BLANC)
        {
            r->o = Est;
            break;
        }
        else
        {
            break;
        }
    case (Sud):
        pG = get_pixel_image(I, x + 1, y + 1);
        pD = get_pixel_image(I, x, y + 1);
        if (pG == NOIR)
        {
            r->o = Est;
            break;
        }
        else if (pD == BLANC)
        {
            r->o = Ouest;
            break;
        }
        else
        {
            break;
        }
    case (Ouest):
        pG = get_pixel_image(I, x, y + 1);
        pD = get_pixel_image(I, x, y);
        if (pG == NOIR)
        {
            r->o = Sud;
            break;
        }
        else if (pD == BLANC)
        {
            r->o = Nord;
            break;
        }
        else
        {
            break;
        }
    }
}

/**
 * @brief Identifie le pixel de départ pour le tracé de contours dans une image.
 * @param I Image à analyser.
 * @return Point Coordonnées du pixel de départ trouvé dans l'image.
 * @details Cette fonction recherche le premier pixel noir ayant un voisin blanc dans l'image,
 * ce qui indique le début d'un contour potentiel.
 */

Point find_departure_pixel(Image I)
{
    //Initialisations
    int height = image_height(I);
    int width = image_width(I);
    Point depart;
    Pixel voisin;
    Pixel A;

    //Examination de tous les points dequant de l'image pour trouver le pixel de départ qui est le premier pixel noir avec un voisin blanc
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            A = get_pixel_image(I, j, i);
            switch (A)
            {
            case (BLANC):
                break;
            case (NOIR):
                if (j != width)
                {
                    voisin = get_pixel_image(I, j, i - 1);
                    if (voisin == BLANC)
                    {
                        //misa à jour du point de départ et envoie de l'information
                        depart = set_point(j, i);
                        return depart;
                    }
                }
            }
        }
    }
    // Traitment dans le cas ou aucun pixel est trouvé
    printf("Can't a pixel to get initialised. The return point is (-1.0 , -1.0)");
    // Si on detecte des nombres négatifs dans les démarches suivantes, on arrête l'operation
    depart = set_point(-1.0, -1.0);
    return depart;
}

/**
 * @brief Crée un masque de l'image identifiant le début des contours.
 * @param I Image originale à masquer.
 * @return Image Masque de l'image indiquant les départs de contours.
 * @details Cette fonction crée une image de masque indiquant les positions des pixels noirs qui sont des points de départ de contours.
 */

Image mask_image(Image I)
{
    int height = image_height(I);
    int width = image_width(I);

    Image mask;
    mask = create_image(width, height);

    Pixel voisin;
    Pixel A;

    // Parcours de l'image pour identifier les pixels qui pouraient etre le de depart d'un contour
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            A = get_pixel_image(I, j, i);
            switch (A)
            {
            case (BLANC):
                break;
            case (NOIR):
                voisin = get_pixel_image(I, j, i - 1);
                if (voisin == BLANC)
                {
                    set_pixel_image(mask, j, i, NOIR);
                }
            }
        }
    }
    return mask;
}

/**
 * @brief Vérifie si une image est entièrement blanche.
 * @param I Image à vérifier.
 * @return bool Vrai si l'image est totalement blanche, faux sinon.
 * @details Cette fonction parcourt chaque pixel de l'image pour déterminer si tous sont blancs.
 */

bool image_white(Image I)
{
    Pixel A;
    for (int i = 1; i <= image_width(I); i++)
    {
        for (int h = 1; h <= image_height(I); h++)
        {
            A = get_pixel_image(I, i, h);
            switch (A)
            {
            case (NOIR):
                return false; // false si et seulement si n'est pas blanche
            default:
                break;
            }
        }
    }
    return true;
}

// Renvoie le contour et écrit également le contour <file_input>.txt - Cette fonction sera modifiée afin d'écrire plusieurs contours dans le <file_input>.tx

/**
 * @brief Génère un contour à partir de l'image donnée et enregistre les points du contour dans un file_input texte.
 * @param I Image à partir de laquelle le contour est généré.
 * @param file_name Nom du file_input où les points du contour seront sauvegardés.
 * @param repository Chemin du répertoire où le file_input sera stocké.
 * @return Contour Liste des points formant le contour.
 * @details Identifie le pixel de départ pour le contour, initialise un robot à cette position et trace le contour en suivant les changements d'orientation du robot.
 */

Contour algo_contour(Image I, char *file_name, char *repository)
{
    // estion d'un contour spécifique
    Point depart = find_departure_pixel(I);
    if (depart.x == -1 && depart.y == -1)
    {
        fprintf(stderr, "No starting point found");
        exit(-102);
    }
    else
    {
        // Initialisation du position du robot
        Point rb = set_point(depart.x - 1, depart.y - 1);

        /* Le code pour la Partie 1 est commenté car la Partie 2 est celle requise pour le reste du projet */

        Point original_position = set_point(depart.x - 1, depart.y - 1);
        Robot robot;
        init_robot(&robot, rb.x, rb.y, Est);

        // Initialisation de la séquence des points
        Contour c;
        c = creer_liste_Point_vide();

        // Parcours du robot pour la creation du contour
        bool repeat = true;
        while (repeat)
        {
            // Faire partie du Partie 1
            ajouter_element_liste_Point(&c, rb);
            move_forward(&robot);
            rb = set_point(robot.x, robot.y);
            new_orientation(&robot, rb.x, rb.y, I);
            if ((robot.o == Est) && (original_position.x == rb.x) && (original_position.y == rb.y))
            {
                repeat = false;
            }
        }
        ajouter_element_liste_Point(&c, rb);

        // Gestion de l'écriture de file_input
        // file_input dans lequel le contour sera écrit

        FILE *fptr;

        // utilisez l'emplacement approprié si vous utilisez macOS ou Linux

        char *no_extension = strtok(file_name, ".");
        char *filename = malloc(strlen(repository) + strlen(no_extension) + 4);
        strcpy(filename, repository);
        strcat(filename, file_name);
        strcat(filename, ".txt");

        fptr = fopen(filename, "w");
        if (fptr == NULL)
        {
            printf("TXT File Error!");
            exit(100);
        }

        fprintf(fptr, "1\n");

        Tableau_Point TP = sequence_points_liste_vers_tableau(c);
        int k;
        int nP = TP.taille;
        fprintf(fptr, "\n");
        fprintf(fptr, "%d\n", nP);
        for (k = 0; k < nP; k++)
        {
            Point P = TP.tab[k];
            fprintf(fptr, "%.1f %.1f\n", P.x, P.y);
        }
        free(TP.tab);
        return c;
    }
}

/**
 * @brief Renvoie la liste de tous les contours détectés dans une image.
 * @param I Image à analyser.
 * @return Liste_Contours Liste de tous les contours trouvés.
 * @details Cette fonction applique un masque pour isoler les contours dans l'image et les trace en utilisant un robot suivant un algorithme de suivi de bordure.
 */


Liste_Contours algo_contours(Image I)
{
    // Initialisation de la liste des contours (type liste chaine)
    Liste_Contours liste;
    liste = creer_liste_Contours_vide();

    Image mask;
    // Initilisation de l'image mask
    mask = mask_image(I);
    // Tant que la nouvelle image n'est pas vide, continue de chercher pour des contours
    while (!image_white(mask))
    {
        Point depart = find_departure_pixel(mask);
        Point rb = set_point(depart.x - 1, depart.y - 1);

        Robot robot;
        init_robot(&robot, rb.x, rb.y, Est);

        Contour c;
        c = creer_liste_Point_vide();

        Point original_position = set_point(depart.x - 1, depart.y - 1);
        bool repeat = true;
        while (repeat)
        {
            ajouter_element_liste_Point(&c, rb);
            // Retrouver le pixel par rapport l'orientation du robot
            switch (robot.o)
            {
            case (Est):
                set_pixel_image(mask, robot.x + 1, robot.y + 1, BLANC);
                break;
            case (Ouest):
                set_pixel_image(mask, robot.x, robot.y + 1, BLANC);
                break;
            default:
                break;
            }
            move_forward(&robot);
            rb = set_point(robot.x, robot.y);
            new_orientation(&robot, rb.x, rb.y, I);

            if ((robot.o == Est) && (original_position.x == rb.x) && (original_position.y == rb.y))
            {
                repeat = false;
            }
        }
        ajouter_element_liste_Point(&c, rb);
        ajouter_element_liste_Contours(&liste, c);
    }
    return liste;
}

/**
 * @brief Enregistre les points de contour d'une image PBM dans un file_input texte.
 * @param c Liste des contours à enregistrer.
 * @param file_name Nom du file_input de sortie.
 * @param repository Chemin du dossier où le file_input sera enregistré.
 * @details Crée un file_input texte pour chaque contour et y écrit les coordonnées des points.
 */

void pbm_contour_to_txt(Liste_Contours c, char *file_name, char *repository)
{
    // Gestion du file_input de sortie
    char *no_extension = strtok(file_name, ".");
    char *filename = malloc(strlen(repository) + strlen(no_extension) + 4);
    strcpy(filename, repository);
    strcat(filename, file_name);
    strcat(filename, ".txt");

    FILE *fptr;
    fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("TXT File Error!");
        exit(100);
    }
    int id = 0;

    // Parcours de chaque liste de points
    Cellule_Liste_Contours *el;
    el = c.first;
    if (el == NULL)
    {
        return;
    }
    else
    {
        while (el != NULL)
        {
            id++;
            fprintf(fptr, "%d\n", id);

            //Transformation en tableau statique pour faciliter l'écriture
            Tableau_Point TP = sequence_points_liste_vers_tableau(el->data);
            int k;
            int nP = TP.taille;
            fprintf(fptr, "\n");
            fprintf(fptr, "%d\n", nP);
            for (k = 0; k < nP; k++)
            {
                Point P = TP.tab[k];
                // Ecriture des proints sur le file_input, en ordre
                fprintf(fptr, "%.1f %.1f\n", P.x, P.y);
            }
            free(TP.tab);
            fprintf(fptr, "\n");
            fprintf(fptr, "\n");
            el = el->suiv;
        }
    }
}

/* Affichage sur le terminale du nombre total de segments, ainsi que
le nombre de contours pour une liste de contours. */

/**
 * @brief Affiche le nombre total de segments et de contours d'une liste de contours.
 * @param c Liste des contours à analyser.
 * @details Calcule et affiche le nombre total de segments formés entre les points de chaque contour.
 */


void contours_data(Liste_Contours c)
{
    Cellule_Liste_Contours *el;
    el = c.first;

    // Initialisation des compteurs
    int nb = 0;
    int nb_points;
    int segments = 0;
    // Parcours de chaque liste de points

    while (el != NULL)
    {
        nb++;
        nb_points = 0;
        Cellule_Liste_Point *e;
        e = (el->data).first;
        // Parcours des points de la liste des points en question

        while (e != NULL)
        {
            nb_points++; // compteur des points totaux de tous les contours
            e = e->suiv;
        }
        // Calcule des segments
        segments = segments + (nb_points - 1);
        el = el->suiv;
    }
    printf("Nombre des contours: %d\n", nb);
    printf("Nombre des segments totals: %d\n", segments);
    printf("\n");
}

/* Affichage sur le terminal du nombre total de segments, ainsi que
le nombre de contours pour une liste de contours. Il est utilisé à
différents endroits, avant et après la méthode de simplification des segments par exemple. */

/**
 * @brief Simplifie les données de contours pour l'affichage ou l'analyse.
 * @param c Liste des contours à traiter.
 * @details Utilisé pour simplifier la représentation des contours, par exemple en réduisant le nombre de points.
 */

void contours_data_simplification(Liste_Contours c)
{
    Cellule_Liste_Contours *el;
    el = c.first;

    // Initialisation des compteurs
    int nb = 0;
    int nb_points;
    int segments = 0;
    // Parcours de chaque liste des points
    while (el != NULL)
    {
        nb++; // compteur des contours
        nb_points = 0;
        Cellule_Liste_Point *e;
        e = (el->data).first;
        // Parcours de points de la liste des points en question
        while (e != NULL)
        {
            nb_points++; // compteur des points totaux de tous les contours
            e = e->suiv;
        }
        segments = segments + nb_points; // Calcul des segments
        el = el->suiv;
    }
    // Affichage sur le terminal
    printf("Nombre des contours: %d\n", nb);
    printf("Nombre des segments totals: %d\n", segments / 2);
    printf("\n");
}

/* Affichage du nombre de contours et du nombre de courbes de Bézier de degré 2 dans le terminal*/

/**
 * @brief Affiche le nombre de courbes de Bézier de degré 2 pour chaque contour.
 * @param c Liste de contours à évaluer.
 * @details Calcule et affiche le nombre de segments transformés en courbes de Bézier de degré 2.
 */

void contours_data_bezier(Liste_Contours c)
{
    Cellule_Liste_Contours *el;
    el = c.first;

    // Initialisation des compteurs
    int nb = 0;
    int nb_beziers = 0;

    // Parcours de chaque liste des points
    while (el != NULL)
    {
        nb++;
        Cellule_Liste_Point *e;
        e = (el->data).first;
        // Parcours de points de la liste des points en question
        while (e != NULL)
        {
            // Chaque groupe de trois points correspond à une courbe de Bézier de degré 2.
            e = e->suiv;
            e = e->suiv;
            e = e->suiv;
            nb_beziers++;
        }
        el = el->suiv;
    }
    // Affichage sur le terminal
    printf("Nombre des contours: %d\n", nb);
    printf("Nombre des bezier totals: %d\n", nb_beziers);
    printf("\n");
}

/* Affichage du nombre de contours et du nombre de courbes de Bézier de degré 3 dans le terminal */

/**
 * @brief Affiche le nombre de courbes de Bézier de degré 3 pour chaque contour.
 * @param c Liste de contours à évaluer.
 * @details Calcule et affiche le nombre de segments transformés en courbes de Bézier de degré 3.
 */

void contours_data_bezier3(Liste_Contours c)
{
    Cellule_Liste_Contours *el;
    el = c.first;
    int nb = 0;
    int nb_beziers = 0;

    // Parcours de chaque liste des points
    while (el != NULL)
    {
        nb++;
        Cellule_Liste_Point *e;
        e = (el->data).first;

        // Parcours des points de la liste des points en question
        while (e != NULL)
        {
            // Chaque quadruplet de points correspond à une courbe de bezier de degré 3.
            e = e->suiv;
            e = e->suiv;
            e = e->suiv;
            e = e->suiv;
            nb_beziers++;
        }
        el = el->suiv;
    }
    // Affichage sur le terminal
    printf("Nombre des contours: %d\n", nb);
    printf("Nombre des bezier totals: %d\n", nb_beziers);
    printf("\n");
}

/* Création du file_input .eps pour la méthode de simplification de segment (trait)*/

/**
 * @brief Crée un file_input .eps représentant le contour donné en utilisant la méthode de simplification par segment (trait).
 * @param c Contour à représenter.
 * @param file_name Nom du file_input de sortie.
 * @param height Hauteur du file_input de sortie.
 * @param width Largeur du file_input de sortie.
 * @details Génère un file_input EPS avec les points du contour connectés par des lignes droites.
 */

void create_postscript(Contour c, char *file_name, int height, int width)
{
    // Extension managment
    char *no_extension = strtok(file_name, ".");
    char *with_extension = malloc(strlen(no_extension) + 4);
    strcpy(with_extension, no_extension);
    strcat(with_extension, ".eps"); // concantenation

    // File managemnent
    FILE *fptr;
    fptr = fopen(with_extension, "w");
    if (fptr == NULL)
    {
        printf("EPS File Error!");
        exit(200);
    }

    // File redaction
    fprintf(fptr, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fptr, "%%%%BoundingBox:   %d   %d   %d   %d\n", 0, 0, width, height);

    Cellule_Liste_Point *el;
    el = c.first;
    fprintf(fptr, "%.0f %.0f moveto ", el->data.x, height - el->data.y);
    el = el->suiv;
    // Parcours des pints de la liste des points passés en argument
    while (el != NULL)
    {
        fprintf(fptr, "%.0f %.0f lineto ", el->data.x, height - el->data.y);
        el = el->suiv;
    }
    fprintf(fptr, "\n");
    fprintf(fptr, "0.0 setlinewidth\n");

    // Writing and visualisation policy applied [stroke]
    fprintf(fptr, "stroke\n");
    fprintf(fptr, "showpage\n");
    fclose(fptr);
    return;
}

/* Création du file_input .eps pour la méthode de simplification de segment (fill) */

/**
 * @brief Crée un file_input .eps avec remplissage pour le contour donné.
 * @param c Contour à représenter.
 * @param file_name Nom du file_input de sortie.
 * @param height Hauteur du file_input de sortie.
 * @param width Largeur du file_input de sortie.
 * @details Génère un file_input EPS avec les points du contour connectés par des lignes droites et le contour rempli.
 */

void create_postscript_fill(Contour c, char *file_name, int height, int width)
{
    // Extension managment
    char *no_extension = strtok(file_name, ".");
    char *with_extension = malloc(strlen(no_extension) + 4);
    strcpy(with_extension, no_extension);
    strcat(with_extension, ".eps");

    // File redaction
    FILE *fptr;
    fptr = fopen(with_extension, "w");
    if (fptr == NULL)
    {
        printf("EPS File Error!");
        exit(200);
    }

    // File redaction
    fprintf(fptr, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fptr, "%%%%BoundingBox:   %d   %d   %d   %d\n", 0, 0, width, height);

    Cellule_Liste_Point *el;
    el = c.first;
    fprintf(fptr, "%.0f %.0f moveto ", el->data.x, height - el->data.y);
    el = el->suiv;

    // Parcour des points de la liste des points passés en argument
    while (el != NULL)
    {
        fprintf(fptr, "%.0f %.0f lineto ", el->data.x, height - el->data.y);
        el = el->suiv;
    }
    fprintf(fptr, "\n");

    // Politique d'écriture et de visualisation appliquée [remplir]

    fprintf(fptr, "fill\n");
    fprintf(fptr, "showpage\n");
    fclose(fptr);
    return;
}

/* Création du file_input .eps pour la méthode de simplification des segments (mode remplissage) */
/* Nous traitons la lecture d'une liste de contours et non d'un seul contour comme nous l'avons fait ci-dessous */

/**
 * @brief Génère un file_input .eps pour chaque contour de la liste, en utilisant la méthode de remplissage.
 * @param c Liste des contours.
 * @param file_name Nom de base pour les file_inputs de sortie.
 * @param height Hauteur des file_inputs de sortie.
 * @param width Largeur des file_inputs de sortie.
 * @param repository Chemin du répertoire de sortie.
 * @details Chaque contour de la liste est transformé en un file_input .eps indépendant.
 */

void create_postscript_contours(Liste_Contours c, char *file_name, int height, int width, char *repository) // Mode remplisage uniquement
{
    // Gestion des extensions
    char *no_extension = strtok(file_name, ".");
    char *filename = malloc(strlen(repository) + strlen(no_extension) + 4);
    strcpy(filename, repository);
    strcat(filename, file_name);
    strcat(filename, ".eps");

    // Gestion des file_inputs
    FILE *fptr;
    fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("Erreur de file_input EPS !");
        exit(200);
    }

    // Rédaction du file_input
    fprintf(fptr, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fptr, "%%%%BoundingBox:   %d   %d   %d   %d\n", 0, 0, width, height);
    fprintf(fptr, "\n");
    Cellule_Liste_Contours *al;
    al = c.first;

    // Parcours de la liste des contours
    while (al != NULL)
    {
        Cellule_Liste_Point *el;
        el = (al->data).first;
        fprintf(fptr, "%.0f %.0f moveto ", el->data.x, height - el->data.y);
        el = el->suiv;

        // Parcours des points de chaque contour en question
        while (el != NULL)
        {
            fprintf(fptr, "%.0f %.0f lineto ", el->data.x, height - el->data.y);
            el = el->suiv;
        }
        fprintf(fptr, "\n");
        al = al->suiv;
    }
    
    // Politique d'écriture et de visualisation appliquée [remplir]
    fprintf(fptr, "fill\n");
    fprintf(fptr, "\n");
    fprintf(fptr, "\n");
    fprintf(fptr, "showpage\n");
    fclose(fptr);
    return;
}

/* Simplification d'une image par segments de manière récursive en utilisant l'algorithme de Douglas Peucker */

/**
 * @brief Simplifie de manière récursive un contour en utilisant l'algorithme de Douglas Peucker.
 * @param T Tableau de points du contour.
 * @param j1 Index de début de l'intervalle à simplifier.
 * @param j2 Index de fin de l'intervalle à simplifier.
 * @param d Distance seuil pour la simplification.
 * @return Contour Simplifié entre les indices j1 et j2.
 * @details Cet algorithme réduit le nombre de points dans un contour en préservant sa forme générale.
 */

Contour simplification_douglas_peucker(Tableau_Point T, int j1, int j2, double d)
{
    // Création du segment
    Segment S;
    S.A = T.tab[j1];
    S.B = T.tab[j2];

    // Initialisation des variables
    double distance;
    double max_distance = 0;
    int far_away;

    // Algorithme de Douglas Peucker
    for (int i = j1 + 1; i < j2; i++)
    {
        distance = distance_point_segment(T.tab[i], S);
        if (max_distance < distance) // objectif : trouver le point le plus eloigné du segment en question qui est [j1,j2]
        {
            max_distance = distance;
            far_away = i;
        }
    }

    // Condition d'arrêt selon le seuil declaré
    if (max_distance <= d)
    {
        Contour L;
        L = creer_liste_Point_vide();
        ajouter_element_liste_Point(&L, S.A);
        ajouter_element_liste_Point(&L, S.B);
        return L;
    }
    else
    {
        // Récursivité
        Contour L1;
        L1 = creer_liste_Point_vide();
        L1 = simplification_douglas_peucker(T, j1, far_away, d);

        Contour L2;
        L2 = creer_liste_Point_vide();
        L2 = simplification_douglas_peucker(T, far_away, j2, d);

        return concatener_liste_Point(L1, L2);
    }
}

// Tâche 7
/* Calcul du point d'une courbe de Bézier de degré 2 */

/**
 * @brief Calcule un point sur une courbe de Bézier de degré 2.
 * @param b2 Courbe de Bézier de degré 2.
 * @param t Paramètre de la courbe (0 <= t <= 1).
 * @return Point sur la courbe de Bézier au paramètre t.
 */

Point calcul_ct_bezier2(Bezier2 b2, double t)
{
    Point A;
    double x, y;

    //Le calcul de deux points est disponible à la documentation du Tache 7
    x = ((1 - t) * (1 - t) * (b2.A.x)) + (2 * t * (1 - t) * (b2.B.x)) + (t * t * (b2.C.x));
    y = ((1 - t) * (1 - t) * (b2.A.y)) + (2 * t * (1 - t) * (b2.B.y)) + (t * t * (b2.C.y));
    A = set_point(x, y);
    return A;
}

/* Calcul du point d'une courbe de Bézier de degré 3 */

/**
 * @brief Calcule un point sur une courbe de Bézier de degré 3.
 * @param b3 Courbe de Bézier de degré 3.
 * @param t Paramètre de la courbe (0 <= t <= 1).
 * @return Point sur la courbe de Bézier au paramètre t.
 */

Point calcul_ct_bezier3(Bezier3 b3, double t)
{
    Point A;
    double x, y;

    //Le calcul de deux points est disponible à la documentation du Tache 7
    x = ((1 - t) * (1 - t) * (1 - t) * (b3.A.x)) + (3 * t * (1 - t) * (1 - t) * (b3.B.x)) + (3 * t * t * (1 - t) * (b3.C.x)) + (t * t * t * (b3.D.x));
    y = ((1 - t) * (1 - t) * (1 - t) * (b3.A.y)) + (3 * t * (1 - t) * (1 - t) * (b3.B.y)) + (3 * t * t * (1 - t) * (b3.C.y)) + (t * t * t * (b3.D.y));
    A = set_point(x, y);
    return A;
}

/* Conversion d'une courbe de Bézier de degré 2 en degré 3 pour l'écriture en postscript */

/**
 * @brief Convertit une courbe de Bézier de degré 2 en une courbe de Bézier de degré 3.
 * @param b2 Courbe de Bézier de degré 2.
 * @return Bezier3 Courbe de Bézier de degré 3 résultante.
 */

Bezier3 conversion_bezier2_to_bezier3(Bezier2 b2)
{
    Bezier3 b3;
    // Point C0 de départ 
    b3.A = b2.A;

    // Point C3 d'arrivée
    b3.D = b2.C;

    double x1, y1, x2, y2;
    // Point C1
    x1 = b2.A.x;
    y1 = b2.A.y;

    x2 = b2.B.x;
    y2 = b2.B.y;

    Point total;

    //Il s'agit de l'elevation du degree de la courbe de bezier de 2 à 3
    total = set_point((x1 + (2 * x2)) / 3, (y1 + (2 * y2)) / 3);
    b3.B = total;

    // Point C2
    x1 = b2.B.x;
    y1 = b2.B.y;

    x2 = b2.C.x;
    y2 = b2.C.y;

    total = set_point(((2 * x1) + x2) / 3, ((2 * y1) + y2) / 3);
    b3.C = total;

    return b3;
}

/**
 * @brief Approxime un contour par une courbe de Bézier de degré 2.
 * La fonction calcule les points de contrôle optimaux pour la courbe.
 * @param c Contour initial.
 * @param j1 Index de début du segment du contour.
 * @param j2 Index de fin du segment du contour.
 * @return Bezier2 Courbe de Bézier de degré 2 approchée.
 */

Bezier2 bezier2_approximation(Contour c, int j1, int j2)
{
    Bezier2 b2;
    int n = j2 - j1;

    Tableau_Point T = sequence_points_liste_vers_tableau(c);
    Point C0, C2;
    C0 = T.tab[j1];
    C2 = T.tab[j2];

    if (n == 1)
    {
        Point C1;
        C1 = set_point((C0.x + C2.x) / 2, (C0.y + C2.y) / 2);

        // Déclaration de la courbe Bézier de degré 2 (quadradique)
        b2.A = C0;
        b2.B = C1;
        b2.C = C2;
        return b2;
    }
    else if (n >= 2)
    {
        double n_double;
        n_double = (double)(n);

        // Calcul de a et b
        double a, b;
        a = (3 * n_double) / ((n_double * n_double) - 1);
        b = ((1 - (2 * n_double)) / (2 * (n_double + 1)));

        double x = 0;
        double y = 0;
        Point id;
        for (int i = j1 + 1; i < j2; i++)
        {
            id = T.tab[i];
            x = x + id.x;
            y = y + id.y;
        }

        // Transformer x et y en double
        double res_x, res_y;

        res_x = a * x + b * ((double)(C0.x) + (double)(C2.x));
        res_y = a * y + b * ((double)(C0.y) + (double)(C2.y));

        Point C1;
        C1 = set_point(res_x, res_y);

        // Enregistrement des points vers la courbe Bézier b2
        b2.A = C0;
        b2.B = C1;
        b2.C = C2;
        return b2;
    }
    else
    {
        // Enregistrement des points vers la courbe Bézier b2
        b2.A = set_point(-1, -1);
        b2.B = set_point(-1, -1);
        b2.C = set_point(-1, -1);
        printf("Erreur avec l'approximation de la courbe Bézier2");
        return b2;
    }
}

/**

* @brief Calcule la distance entre un point et une courbe de Bézier de degré 2 à un paramètre t spécifique.
* @param P1 Point à partir duquel mesurer la distance.
* @param b2 Courbe de Bézier de degré 2.
* @param ti Paramètre de la courbe de Bézier indiquant le point spécifique à mesurer.
* @return double Distance calculée.
*/

double distance_point_bezier2(Point P1, Bezier2 b2, double ti)
{
    double result;
    Point A;

    A = calcul_ct_bezier2(b2, ti);
    result = distance(P1, A);
    return result;
}

/**
* @brief Applique la méthode de simplification de Douglas-Peucker à une approximation de Bézier de degré 2.
* @param C Contour à simplifier.
* @param j1 Indice de début de segment du contour.
* @param j2 Indice de fin de segment du contour.
* @param d Distance seuil pour la simplification.
* @return Contour Résultat de la simplification, potentiellement composé de plusieurs segments.
*/
Contour simplification_douglas_peucker_bezier2(Contour C, int j1, int j2, double d)
{
    int n = j2 - j1;

    // Creation de la courbe de Bezier
    Bezier2 b2;
    b2 = bezier2_approximation(C, j1, j2);

    Tableau_Point T = sequence_points_liste_vers_tableau(C);

    // Variable initialisations
    double distance, ti;
    double max_distance = 0; // dmax
    int far_away, j;

    // Trouver le point le plus loin
    for (int i = j1 + 1; i < j2; i++)
    {
        j = i - j1;
        ti = (double)(j) / (double)(n);
        distance = distance_point_bezier2(T.tab[i], b2, ti);
        if (max_distance < distance)
        {
            max_distance = distance;
            far_away = i;
        }
    }

    if (max_distance <= d)
    {
        Contour L;
        L = creer_liste_Point_vide();

        // Enregistre des points trouve sur la liste des points (contour)
        ajouter_element_liste_Point(&L, b2.A);
        ajouter_element_liste_Point(&L, b2.B);
        ajouter_element_liste_Point(&L, b2.C);
        return L;
    }
    else
    {
        // Recursivitée appliquée
        Contour L1;
        L1 = creer_liste_Point_vide();
        L1 = simplification_douglas_peucker_bezier2(C, j1, far_away, d);

        Contour L2;
        L2 = creer_liste_Point_vide();
        L2 = simplification_douglas_peucker_bezier2(C, far_away, j2, d);

        return concatener_liste_Point(L1, L2);
    }
}

/**
 * @brief Création d'un file_input PostScript pour les contours représentés par des courbes de Bézier de degré 2.
 * Cette fonction génère un file_input .eps qui contient les instructions pour dessiner les contours avec des courbes de Bézier.
 * 
 * @param c Liste des contours à traiter.
 * @param file_name Nom du file_input de sortie sans l'extension.
 * @param height Hauteur de la zone de dessin.
 * @param width Largeur de la zone de dessin.
 * @param repository Chemin du répertoire où le file_input sera sauvegardé.
 */

void create_postscript_contours_bezier2(Liste_Contours c, char *file_name, int height, int width, char *repository) // Mode remplisage uniquement
{
    // Extension managment
    char *no_extension = strtok(file_name, ".");
    char *with_extension = malloc(strlen(repository) + strlen(no_extension) + 4);
    strcpy(with_extension, repository);
    strcat(with_extension, file_name);
    strcat(with_extension, ".eps");

    FILE *fptr;
    fptr = fopen(with_extension, "w");
    if (fptr == NULL)
    {
        printf("EPS File Error!");
        exit(200);
    }

    fprintf(fptr, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fptr, "%%%%BoundingBox:   %d   %d   %d   %d\n", 0, 0, width, height);
    fprintf(fptr, "\n");
    Cellule_Liste_Contours *al;
    al = c.first;
    // Parcours de contous dans une liste des contours
    while (al != NULL)
    {
        Cellule_Liste_Point *el;
        el = (al->data).first;
        Bezier3 b3;
        Bezier2 b2;

        // Initialisation des points de la courbe b2
        b2.A = el->data;
        el = el->suiv;
        b2.B = el->data;
        el = el->suiv;
        b2.C = el->data;
        b3 = conversion_bezier2_to_bezier3(b2);

        // Initialisation de la redaction du file_input eps
        fprintf(fptr, "%.3f %.3f moveto ", b3.A.x, height - b3.A.y);
        fprintf(fptr, "%.3f %.3f %.3f %.3f %.3f %.3f curveto ", b3.B.x, height - b3.B.y, b3.C.x, height - b3.C.y, b3.D.x, height - b3.D.y);
        el = el->suiv;

        // Parcours des points du contour en question
        while (el != NULL)
        {
            b2.A = el->data;
            el = el->suiv;
            b2.B = el->data;
            el = el->suiv;
            b2.C = el->data;
            b3 = conversion_bezier2_to_bezier3(b2);

            // On a besoin que les points B, C, D selon la documentation des file_inputs eps quand c'est curveto qui est utilisé
            fprintf(fptr, "%.3f %.3f %.3f %.3f %.3f %.3f curveto ", b3.B.x, height - b3.B.y, b3.C.x, height - b3.C.y, b3.D.x, height - b3.D.y);
            el = el->suiv;
        }
        fprintf(fptr, "\n 2.0 setlinewidth");
        fprintf(fptr, "\n");
        al = al->suiv;
    }
    fprintf(fptr, "fill\n");
    fprintf(fptr, "\n");
    fprintf(fptr, "\n");
    fprintf(fptr, "showpage\n");
    fclose(fptr);
    return;
}
/**
 * @brief Approximation d'un contour par une courbe de Bézier de degré 3.
 * Cette fonction calcule les points de contrôle pour une courbe de Bézier de degré 3 basée sur les points du contour donné.
 * 
 * @param c Contour à approximer.
 * @param j1 Index de début du segment du contour.
 * @param j2 Index de fin du segment du contour.
 * @return Bezier3 Courbe de Bézier de degré 3 résultante.
 */

Bezier3 bezier3_approximation(Contour c, int j1, int j2)
{
    Bezier3 b3;
    int n = j2 - j1;


    Tableau_Point T = sequence_points_liste_vers_tableau(c);
    Point C0, C3;
    C0 = T.tab[j1];
    C3 = T.tab[j2];

    if (n == 1)
    {
        Point C1, C2;
        C1 = set_point((2 * C0.x + C3.x) / 3, (2 * C0.y + C3.y) / 3);
        C2 = set_point((C0.x + 2 * C3.x) / 3, (C0.y + 2 * C3.y) / 3);
        // Déclaration de la courbe de Bézier
        b3.A = C0;
        b3.B = C1;
        b3.C = C2;
        b3.D = C3;
        return b3;
    }
    else if (n == 2)
    {
        Point C1, C2, P1;
        P1 = T.tab[j1 + 1];
        C1 = set_point((4 * P1.x - C3.x) / 3, (4 * P1.y - C3.y) / 3);
        C2 = set_point((4 * P1.x - C0.x) / 3, (4 * P1.y - C0.y) / 3);
        // Déclaration de la courbe de Bézier de degré 3 (4 points)
        b3.A = C0;
        b3.B = C1;
        b3.C = C2;
        b3.D = C3;
        return b3;
    }
    else if (n > 2)
    {
        double n_double = (double)(n);

        // Calcul de a et b
        //La theorie mathematique est disponible sur la documentation du tache 7
        double a = (-15 * n_double * n_double * n_double + 5 * n_double * n_double + 2 * n_double + 4) / (3 * (n_double + 2) * (3 * n_double * n_double + 1));
        double b = ((10 * n_double * n_double * n_double - 15 * n_double * n_double + n_double + 2) / (3 * (n_double + 2) * (3 * n_double * n_double + 1)));
        double lambda = (70 * n_double) / (3 * (n_double * n_double - 1) * (n_double * n_double - 4) * (3 * n_double * n_double + 1));

        // Définir la fonction alpha(i)
        double x = 0.0;
        double y = 0.0;
        Point id;
        double i_dbl, alpha;

        // Déclaration de la fonction φ(χ) intermédiaire
        for (int i = 1; i < n; i++)
        {
            i_dbl = (double)(i);
            alpha = (6 * i_dbl * i_dbl * i_dbl * i_dbl) - (8 * n_double * i_dbl * i_dbl * i_dbl) + (6 * i_dbl * i_dbl) - (4 * n_double * i_dbl) + (n_double * n_double * n_double * n_double) - (n_double * n_double);
            id = T.tab[j1 + i];
            x += alpha * id.x;
            y += alpha * id.y;
        }

        double res_x = a * ((double)C0.x) + lambda * x + b * (double)(C3.x);
        double res_y = a * ((double)C0.y) + lambda * y + b * (double)(C3.y);

        Point C1 = set_point(res_x, res_y);
        x = 0;
        y = 0;

        for (int i = 1; i < n; i++)
        {
            i_dbl = n_double - (double)(i);
            alpha = (6 * i_dbl * i_dbl * i_dbl * i_dbl) - (8 * n_double * i_dbl * i_dbl * i_dbl) + (6 * i_dbl * i_dbl) - (4 * n_double * i_dbl) + (n_double * n_double * n_double * n_double) - (n_double * n_double);
            id = T.tab[j1 + i];
            x += alpha * ((double)id.x);
            y += alpha * ((double)id.y);
        }

        res_x = b * ((double)C0.x) + lambda * x + a * (double)(C3.x);
        res_y = b * ((double)C0.y) + lambda * y + a * (double)(C3.y);
        Point C2 = set_point(res_x, res_y);

        // Déclaration de la courbe de Bézier de degré 3 (4 points)
        b3.A = C0;
        b3.B = C1;
        b3.C = C2;
        b3.D = C3;
        return b3;
    }
    else
    {
        // Traitement des cas d'erreur
        // ON TOMBE JAMAIS DANS CETTE PARTIE DU CODE, MAIS SI ON Y TOMBE
        // ON PEUT DÉTECTER PLUS FACILEMENT L'ERREUR
        b3.A = set_point(-1, -1);
        b3.B = set_point(-1, -1);
        b3.C = set_point(-1, -1);
        b3.D = set_point(-1, -1);
        printf("Erreur avec l'approximation de la courbe Bézier3");
        return b3;
    }
}

/**
 * @brief Calcule la distance entre un point donné et une courbe de Bézier de degré 3 à un paramètre t spécifique.
 * 
 * @param P1 Point pour lequel calculer la distance.
 * @param b3 Courbe de Bézier de degré 3.
 * @param ti Valeur du paramètre t.
 * @return double Distance entre le point et la courbe.
 */

double distance_point_bezier3(Point P1, Bezier3 b3, double ti)
{
    double result;
    Point A;


    A = calcul_ct_bezier3(b3, ti);
    result = distance(P1, A);
    return result;
}

/**
 * @brief Simplification directe par approximation des contours vers courbes de Bézier de degré 3
 * 
 * Cette fonction simplifie un contour en utilisant une approximation par une courbe de Bézier de degré 3,
 * en appliquant l'algorithme de Douglas-Peucker pour calculer la distance entre les points du contour et
 * la courbe de Bézier. Elle vise à réduire le nombre de points tout en conservant la forme générale du contour.
 * 
 * @param C Contour à simplifier.
 * @param j1 Indice de début du segment de contour à traiter.
 * @param j2 Indice de fin du segment de contour à traiter.
 * @param d Seuil de distance pour la simplification.
 * @return Contour simplifié sous forme de points de Bézier de degré 3.
 */

Contour simplification_douglas_peucker_bezier3(Contour C, int j1, int j2, double d)
{
    int n = j2 - j1;

    // Création de la courbe de Bézier
    Bezier3 b3;
    b3 = bezier3_approximation(C, j1, j2);

    Tableau_Point T = sequence_points_liste_vers_tableau(C);

    // Initialisation des variables
    double distance, ti;
    double max_distance = 0; // dmax
    int far_away, j;

    for (int i = j1 + 1; i < j2; i++)
    {
        j = i - j1;
        ti = (double)(j) / (double)(n);
        distance = distance_point_bezier3(T.tab[i], b3, ti);
        if (max_distance < distance)
        {
            max_distance = distance;
            far_away = i;
        }
    }

    // Application de l'algorithme de Douglas Peucker
    if (max_distance <= d) // Condition d'arrêt de la récursivité pour un seuil donne
    {
        Contour L;
        L = creer_liste_Point_vide();
        ajouter_element_liste_Point(&L, b3.A);
        ajouter_element_liste_Point(&L, b3.B);
        ajouter_element_liste_Point(&L, b3.C);
        ajouter_element_liste_Point(&L, b3.D);
        return L;
    }
    else
    {
        // Récursivité appliquée
        Contour L1;
        L1 = creer_liste_Point_vide();
        L1 = simplification_douglas_peucker_bezier3(C, j1, far_away, d);

        Contour L2;
        L2 = creer_liste_Point_vide();
        L2 = simplification_douglas_peucker_bezier3(C, far_away, j2, d);

        return concatener_liste_Point(L1, L2);
    }
}

/**
 * @brief Création du file_input EPS pour liste des contours simplifiés par la méthode des courbes de Bézier de degré 3
 * 
 * Cette fonction génère un file_input EPS qui contient la représentation des contours d'une image, simplifiés par des courbes de Bézier de degré 3.
 * Elle sauvegarde chaque contour en utilisant les courbes de Bézier pour une représentation vectorielle précise.
 * 
 * @param c Liste des contours à traiter.
 * @param file_name Nom du file_input pour la sauvegarde.
 * @param height Hauteur de l'image originale.
 * @param width Largeur de l'image originale.
 * @param repository Chemin du dossier où le file_input sera sauvegardé.
 */
 
void create_postscript_contours_bezier3(Liste_Contours c, char *file_name, int height, int width, char *repository) // Mode remplissage uniquement
{
    // Gestion des extensions
    char *no_extension = strtok(file_name, ".");
    char *with_extension = malloc(strlen(repository) + strlen(no_extension) + 4);
    strcpy(with_extension, repository);
    strcat(with_extension, file_name);
    strcat(with_extension, ".eps");

    // Gestion de l'accès au file_input
    FILE *fptr;
    fptr = fopen(with_extension, "w");
    if (fptr == NULL)
    {
        printf("Erreur de file_input EPS !");
        exit(200);
    }

    // Écriture des introductions de file_input
    fprintf(fptr, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fptr, "%%%%BoundingBox:   %d   %d   %d   %d\n", 0, 0, width, height);
    fprintf(fptr, "\n");

    Cellule_Liste_Contours *al = c.first;
    while (al != NULL)
    {
        Cellule_Liste_Point *el = (al->data).first;
        Bezier3 b3;

        // Passage des points à la courbe de Bézier
        b3.A = el->data;
        el = el->suiv;
        b3.B = el->data;
        el = el->suiv;
        b3.C = el->data;
        el = el->suiv;
        b3.D = el->data;

        // La commande moveto est utilisée une seule fois
        fprintf(fptr, "%.3f %.3f moveto ", b3.A.x, height - b3.A.y);
        // C'est pourquoi nous ajoutons seulement les points B, C, D pour la syntaxe curveto
        fprintf(fptr, "%.3f %.3f %.3f %.3f %.3f %.3f curveto ", b3.B.x, height - b3.B.y, b3.C.x, height - b3.C.y, b3.D.x, height - b3.D.y);
        el = el->suiv;

        // Répéter pour chaque courbe sur le contour spécifique
        while (el != NULL)
        {
            b3.A = el->data;
            el = el->suiv;
            b3.B = el->data;
            el = el->suiv;
            b3.C = el->data;
            el = el->suiv;
            b3.D = el->data;
            fprintf(fptr, "%.3f %.3f %.3f %.3f %.3f %.3f curveto ", b3.B.x, height - b3.B.y, b3.C.x, height - b3.C.y, b3.D.x, height - b3.D.y);
            el = el->suiv;
        }

        fprintf(fptr, "\n2.0 setlinewidth");
        fprintf(fptr, "\n");
        al = al->suiv;
    }

    // Mode d'écriture de file_input
    fprintf(fptr, "fill\n");
    fprintf(fptr, "\n");
    fprintf(fptr, "showpage\n");
    fclose(fptr);
    return;
}

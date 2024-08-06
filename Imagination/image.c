// #############################################################################
// # File image.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved
// #############################################################################

/**
 * @file image.c
 * @brief Déclarations de fonctions pour le module Image
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "error.h"
#include "image.h"

/**
 * @def PIXEL_INDEX(_I, _x, _y)
 * @brief Calcule l'indice d'un pixel dans une image PBM à partir de ses coordonnées.
 *
 * Cette macro calcule l'indice d'un pixel dans le tableau de pixels de l'image en fonction de ses coordonnées x et y.
 *
 * @param _I L'objet Image représentant l'image PBM.
 * @param _x La coordonnée x du pixel (basée sur 1).
 * @param _y La coordonnée y du pixel (basée sur 1).
 * @return L'index du pixel dans le tableau de pixels de l'image.
 *
 * Cette macro est utile pour accéder efficacement aux valeurs de pixels individuels dans l'image. Il considère l'indexation basée sur 0 pour le tableau de pixels et ajuste les coordonnées en conséquence.
 */
 
#define PIXEL_INDEX(_I, _x, _y) ((_x) - 1) + (_I).the_height_of_the_image *((_y) - 1)

/**
 * @brief Crée une image PBM vide avec les dimensions spécifiées.
 *
 * Cette macro calcule l'indice d'un pixel dans le tableau de pixels de l'image en fonction de ses coordonnées x et y.
 *
 * @param L Largeur de l'image.
 * @param H Hauteur de l'image.
 * @return Objet Image représentant l'image créée (tous les pixels en blanc).
 *
 */
Image create_image(UINT L, UINT H)
{
	Image I;
	UINT i;

	I.the_height_of_the_image = L;
	I.the_width_of_the_image = H;

	/* allocation dynamique d'un tableau de L*H Pixel*/
	I.pointer_to_pixel_array = (Pixel *)malloc(sizeof(Pixel) * L * H);

	/* test si le tableau a ete correctement alloue */
	if (I.pointer_to_pixel_array == (Pixel *)NULL)
	{
		FATAL_ERROR("Imposible to create the requested image");
	}

	/* remplir le tableau avec des pixels blancs */
	for (i = 0; i < L * H; i++)
		I.pointer_to_pixel_array[i] = BLANC;

	return I;
}

/**
 * @brief Supprime l'image spécifiée.
 *
 * Cette fonction libère la mémoire allouée au tableau de pixels de l'image spécifiée.
 *
 * @param p_I Pointeur vers l'objet Image représentant l'image à supprimer.
 */
void delete_image(Image *p_I)
{
	free(p_I->pointer_to_pixel_array);
	p_I->the_height_of_the_image = 0;
	p_I->the_width_of_the_image = 0;
}

/**
 * @brief Obtient la valeur du pixel aux coordonnées spécifiées dans l'image.
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
Pixel get_pixel_image(Image I, int x, int y)
{
	if (x < 1 || x > I.the_height_of_the_image || y < 1 || y > I.the_width_of_the_image)
		return BLANC;
	return I.pointer_to_pixel_array[PIXEL_INDEX(I, x, y)];
}

/**
 * @brief Définit la valeur du pixel aux coordonnées spécifiées dans l'image.
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
void set_pixel_image(Image I, int x, int y, Pixel v)
{
	if (x < 1 || x > I.the_height_of_the_image || y < 1 || y > I.the_width_of_the_image)
		return;
	I.pointer_to_pixel_array[PIXEL_INDEX(I, x, y)] = v;
}

/**
 * @brief Obtient la largeur de l'image spécifiée.
 *
 * Cette fonction récupère la largeur de l'image spécifiée.
 *
 * @param I Objet Image représentant l'image.
 * @return La largeur de l'image.
 */
UINT image_width(Image I)
{
	return I.the_height_of_the_image;
}

/**
 * @def image_height(Image I)
 * @brief Obtient la hauteur de l'image spécifiée.
 *
 * Cette fonction récupère la hauteur de l'image spécifiée.
 *
 * @param I Objet Image représentant l'image.
 * @return La hauteur de l'image.
 */
UINT image_height(Image I)
{
	return I.the_width_of_the_image;
}


/**
 * @brief Vérifie l'en-tête d'un file_input image PBM codé au format P1.
 *
 * Cette fonction valide l'en-tête d'un file_input image PBM supposé être au format P1.
 * Il vérifie les éléments suivants :
 * - Numéro magique "P1" (sensible à la casse) sur la première ligne.
 * - Zéro ou plusieurs lignes de commentaires commençant par '#'.
 *
 * @param f Pointeur vers le descripteur de file_input ouvert pour l'image PBM.
 *
 * @see header_file_pbm_generic
 */
void header_file_pbm_P1(FILE *f)
{
	char *ligne;
	size_t n;
	size_t line_l;

	/* position at the beginning of the file */
	fseek(f, 0, SEEK_SET);

	/* reading and testing line 1 */
	ligne = (char *)NULL;
	n = 0;
	line_l = getline(&ligne, &n, f);

	/* the line is correct if and iff
	case - file created under Linux: line = {'P','1',10}
	either a string of 3 characters (the last one is the null character)
	case - file created under Windows: line = {'P','1',13, 10}
	either a string of 4 characters (the last one is the null character)
	*/
	if (line_l < 3)
	{
		FATAL_ERROR("header_file_pbm_generic : ligne 1 incorrecte\n");
	}
	if ((ligne[0] != 'P') || (ligne[1] != '1'))
	{
		FATAL_ERROR("header_file_pbm_generic : ligne 1 incorrecte\n");
	}
	free(ligne);

	/* read all lines starting with # */
	bool boucle_ligne_commentaire = true;
	do
	{
		/* test end of file first */
		if (feof(f))
		{
			FATAL_ERROR("header_file_pbm_generic : fin file_input inattendue\n");
		}

		/* read a character and test against '#' */
		char c;
		fscanf(f, "%c", &c);
		if (c == '#')
		{
			/* read the rest of the line */
			ligne = (char *)NULL;
			n = 0;
			line_l = getline(&ligne, &n, f);
			free(ligne);
		}
		else
		{
			/* go back one character in f */
			fseek(f, -1, SEEK_CUR);
			boucle_ligne_commentaire = false;
		}
	} while (boucle_ligne_commentaire);
}

/**
 * @brief Valide l'en-tête d'un file_input image PBM.
 *
 * Cette fonction effectue des vérifications génériques sur l'en-tête d'un file_input image PBM. Il est généralement utilisé
 * pour les formats comme P1 et P4. La vérification du format spécifique peut être effectuée par des fonctions telles que
 * `header_file_pbm_P1` spécialement conçu pour P1. Ici, nous utilisons le formulaire générique pour tout.
 *
 * Les éléments d'en-tête suivants sont vérifiés :
 * - Numéro magique "P1" ou "P4" (sensible à la casse) sur la première ligne.
 * - Zéro ou plusieurs lignes de commentaires commençant par '#'.
 *
 * @param f Pointeur vers le descripteur de file_input ouvert pour l'image PBM.
 */
void header_file_pbm_generic(FILE *f)
{
	fseek(f, 0, SEEK_SET);

	char *ligne = NULL;
	size_t n = 0;
	ssize_t line_l = getline(&ligne, &n, f);

	if (line_l < 3 || (ligne[0] != 'P') || (ligne[1] != '1' && ligne[1] != '4'))
	{
		FATAL_ERROR("header_file_pbm_generic : ligne 1 incorrecte\n");
	}
	free(ligne);

	// Ignore lines with comments
	bool in_comments = true;
	while (in_comments)
	{
		if (feof(f))
		{
			FATAL_ERROR("header_file_pbm_generic : fin file_input inattendue\n");
		}

		char c;
		if (fscanf(f, "%c", &c) != 1)
		{
			FATAL_ERROR("header_file_pbm_generic : fin file_input inattendue\n");
		}

		if (c == '#')
		{
			/* Read the rest of the line */
			ligne = NULL;
			line_l = getline(&ligne, &n, f);
			free(ligne);
		}
		else
		{
			/* Return one character back */
			fseek(f, -1, SEEK_CUR);
			in_comments = false;
		}
	}
}

/**
 * @brief Lit une image PBM à partir du file_input spécifié ou arrête l'opération en cas d'erreur.
 *
 * Cette fonction lit une image PBM à partir du file_input spécifié et la renvoie en tant qu'objet Image.
 *
 * @param name_f Le nom du file_input contenant l'image PBM.
 * @return Objet Image représentant l'image lue.
 *
 * Si une erreur se produit lors de la lecture du file_input, le programme s'arrête avec un message d'erreur.
 *version acceptant les file_inputs avec
  - ligne 1 : P1 ou P4
  - zéro, une ou plusieurs lignes commençant toutes par #
  - zéro, un ou plusieurs séparateurs
  - la largeur
  - un ou plusieurs séparateurs
  - la hauteur
  - un ou plusieurs séparateurs
  - les pixels de l'image
 */
Image read_image_file(char *name_f)
{
	FILE *f = fopen(name_f, "r");
	if (f == NULL)
	{
		FATAL_ERROR("read_image_file: ouverture du file_input impossible\n");
	}

	char magic[3];
	if (fscanf(f, "%2s", magic) != 1)
	{
		FATAL_ERROR("read_image_file: lecture du magic number impossible\n");
	}

	fclose(f); // Close the file after reading magic number 1 or 4 (codecs)

	if (strcmp(magic, "P1") == 0)
	{
		return read_image_file_P1(name_f);
	}
	else if (strcmp(magic, "P4") == 0)
	{
		return read_image_file_P4(name_f);
	}
	else
	{
		FATAL_ERROR("read_image_file: file format not recognised\n");
	}
}


/**
 * @brief Lit une image PBM à partir du file_input spécifié qui est codé sous le codec P1.
 *
 * Cette fonction lit une image PBM à partir du file_input spécifié et la renvoie en tant qu'objet Image.
 *
 * @param name_f Le nom du file_input contenant l'image PBM.
 * @return Objet Image représentant l'image lue.
 *
 */
Image read_image_file_P1(char *name_f)
{
	FILE *f;
	UINT L, H;
	UINT x, y;
	int res_fscanf;
	Image I;

	/* opening file name_f for reading */
	f = fopen(name_f, "r");
	if (f == (FILE *)NULL)
	{
		FATAL_ERROR("read_image_file : opening the file was impossible\n");
	}

	/* header processing and shutdown on error */
	header_file_pbm_generic(f);

	/* reading dimensions */
	res_fscanf = fscanf(f, "%d", &L);
	if (res_fscanf != 1)
	{
		FATAL_ERROR("read_image_file : incorrect L dimension\n");
	}
	res_fscanf = fscanf(f, "%d", &H);
	if (res_fscanf != 1)
	{
		FATAL_ERROR("read_image_file : incorrect H dimension\n");
	}

	/* creation de l'image de dimensions L x H */
	I = create_image(L, H);

	/* reading pixels from the file
	only the characters '0' (WHITE) or '1' (BLACK)
	must be taken into account */
	x = 1;
	y = 1;
	while (!feof(f) && y <= H)
	{
		char c;
		int res;

		/* read a character passing characters other than '0' and '1' */
		res = fscanf(f, "%c", &c);

		//error treatment
		if (res < 0)
		{
			printf("read_image_file : erreur de lecture de carcater - ERROR 301\n");
		}
		while (!feof(f) && !(c == '0' || c == '1'))
		{
			res = fscanf(f, "%c", &c);
		}
		if (!feof(f))
		{
			set_pixel_image(I, x, y, c == '1' ? NOIR : BLANC);
			x++;
			if (x > L)
			{
				x = 1;
				y++;
			}
		}
	}

	/* close file */
	fclose(f);

	return I;
}


/**
 * @brief Lit une image PBM à partir du file_input spécifié qui est codée sous le codec P1.
 *
 * Cette fonction lit une image PBM à partir du file_input spécifié et la renvoie en tant qu'objet Image.
 *
 * @param name_f Le nom du file_input contenant l'image PBM.
 * @return Objet Image représentant l'image lue.
 *
 */
Image read_image_file_P4(char *name_f)
{
	FILE *f = fopen(name_f, "rb"); // Note the binary mode
	if (f == NULL)
	{
		FATAL_ERROR("read_image_file : unable to open file\n");
	}

	header_file_pbm_generic(f);

	int L, H;
	if (fscanf(f, "%d", &L) != 1)
	{
		FATAL_ERROR("read_image_file : incorrect L dimension\n");
	}
	if (fscanf(f, "%d", &H) != 1)
	{
		FATAL_ERROR("read_image_file : incorrect H dimension\n");
	}

	/* Move past newline or spaces after dimensions */
	fgetc(f); // To get to the first data byte

	Image I = create_image(L, H);

	/* Read pixel data */
	for (int y = 1; y <= H; y++)
	{
		int bytes_per_row = (L + 7) / 8; // Calcul du nombre de bytes pour chaque ligne

		//Allocation de la memoire
		unsigned char *row_data = malloc(bytes_per_row);
		if (fread(row_data, 1, bytes_per_row, f) != bytes_per_row)
		{
			FATAL_ERROR("read_image_file : lecture des pixels échouée\n");
		}

		// Extraction des données du pixel par les octets binaires
		for (int x = 1; x <= L; x++)
		{
			int byte_idx = (x - 1) / 8;
			int bit_idx = 7 - ((x - 1) % 8); // 7 because high bits are first
			int pixel = (row_data[byte_idx] & (1 << bit_idx)) ? NOIR : BLANC;
			set_pixel_image(I, x, y, pixel);
		}

		free(row_data); // Clean up memory -> SOS
	}

	fclose(f);
	return I;
}

/**
 * @brief Écrit une image PBM sur le terminal.
 *
 *
 * @param I Objet Image représentant l'image à écrire.
 */
void image_to_terminal(Image I)
{
	int height = image_height(I);
	int width = image_width(I);
	Pixel A;
	for (int i = 1; i <= height; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			A = get_pixel_image(I, j, i);
			switch (A)
			{
			case (BLANC):
				printf("0");
				break;
			default:
				printf("1");
				break;
			}
		}
		printf("\n");
	}
}


/**
 * @brief Calcule le négatif de l'image spécifiée.
 *
 * Cette fonction calcule le négatif de l'image spécifiée. Cela ne modifie pas l'existant
 *
 * @param I Objet Image représentant l'image.
 * @return Objet Image représentant le négatif de l'image.
 */
Image negative_image(Image I)
{
	int height = image_height(I);
	int width = image_width(I);
	Pixel A;

	// Initialisations
	Image negative;
	negative = create_image(width, height);

	for (int i = 1; i <= height; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			A = get_pixel_image(I, j, i);
			switch (A)
			{
			//Logique d'inversion des pixels
			case (BLANC):
				set_pixel_image(negative, j, i, NOIR);
				break;
			default:
				set_pixel_image(negative, j, i, BLANC);
				break;
			}
		}
	}
	return negative;
}
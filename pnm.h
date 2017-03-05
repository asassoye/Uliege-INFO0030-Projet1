/**
 * pnm.h
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 * 
 * @author: Sassoye Andrew 20160135
 * @date: 
 * @projet: INFO0030 Projet 1
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiplies
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __PNM__
#define __PNM__

/**
 * Déclaration du type opaque RGB
 *
 */
typedef struct RGB_t RGB;

/**
 * Déclaration du type union Pixel
 *
 */
typedef union Pixel_t Pixel;

/**
 * Definition du type Format
 */
typedef enum Format_t {
    PBM, PGM, PPM
} Format;

/**
 * Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;


/**
 * load_pnm
 *
 * Charge une image PNM depuis un fichier.
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param filename le chemin vers le fichier contenant l'image.
 *
 * @pre: image != NULL, filename != NULL
 * @post: image pointe vers l'image chargée depuis le fichier.
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *    -4 Erreur diverse
 *
 */
int load_pnm(PNM **image, char *filename);


/**
 * write_pnm
 *
 * Sauvegarde une image PNM dans un fichier.
 *
 * @param image un pointeur sur PNM.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: image != NULL, filename != NULL
 * @post: le fichier filename contient l'image PNM image.
 *
 * @return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 *
 */
int write_pnm(PNM *image, char *filename);

/**
 * free_matrix
 *
 * Libere la memoire d'une matrice
 *
 * @param matrix un pointeur sur la matrice
 * @param columns le nombre de colonnes de la matrice
 *
 * @pre: matrix != NULL, columns > 0
 * @post: a liberé la memoire de la matrice
 *
 * @return:
 *      0 Succes
 */
int free_matrix(Pixel **matrix, unsigned int columns);

/**
 * help_pnm
 *
 * Donne les instructions pour la manipulation du programme.
 *
 * @pre: /
 * @post: Affiche les instructions
 */
void help_pnm(void);

#endif // __PNM__


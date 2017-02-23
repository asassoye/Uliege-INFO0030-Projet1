/**
 * pnm.c
 * 
 * Ce fichier contient les définitions de types et 
 * les fonctions de manipulation d'images PNM.
 * 
 * @author: Sassoye Andrew 20160135
 * @date: 23/02/2017
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pnm.h"
#include "verifications.h"
#include "error.h"

#ifndef __ANSI_
#define __ANSI_

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#endif


/**
 * Definition du type RGB
 */
struct RGB_t {
    unsigned short red;
    unsigned short green;
    unsigned short blue;
};

/**
 * Definition du type Pixel
 */

union Pixel_t {
    unsigned short pixel;
    RGB pixel_rgb;
};


/**
 * Définition du type opaque PNM
 */
struct PNM_t {
    Format format;
    unsigned short width;
    unsigned short height;
    unsigned short limits;
    Pixel **matrix;
};

static int create_pbm_matrix(PNM **image, FILE *file);

static int create_pgm_matrix(PNM **image, FILE *file);

static int create_ppm_matrix(PNM **image, FILE *file);

static int create_pbm_matrix(PNM **image, FILE *file) {
    (*image)->format = PBM; //On donne le format PGM a la structure

    char magical[3];

    if (fscanf(file, "%s", magical) != 1) {
        return error(0x7CF); //Fichier malformé
    }

    if (strcmp(magical, "P1") != 0) {
        return error(0x7CF); //Fichier malformé
    }


    if (fscanf(file, "%hu %hu", &(*image)->height, &(*image)->width) != 2) {
        return error(0x7CF); //Fichier malformé
    }


    (*image)->matrix = malloc(sizeof(*(*image)->matrix) * (*image)->height);

    if ((*image)->matrix == NULL) {
        free(*image);
        *image = NULL;
        return error(0x7CD); //Pas assez de mémoire
    } else {
        for (int i = 0; i < (*image)->height; i++) {
            (*image)->matrix[i] = malloc(sizeof(*(*image)->matrix[i]) * (*image)->width);
            if ((*image)->matrix[i] == NULL) {
                free_matrix((*image)->matrix, (*image)->width);
                return error(0x7CD); //Pas assez de mémoire
            }
            for (int j = 0; j < (*image)->width; j++) {
                if (fscanf(file, "%hu", &((*image)->matrix[i][j].pixel)) != 1) {

                    free_matrix((*image)->matrix, (*image)->width);

                    return error(0x7CF); //Fichier malformé
                }
            }
        }
    }
    return 0;
}

static int create_pgm_matrix(PNM **image, FILE *file) {
    (*image)->format = PGM; //On donne le format PGM a la structure

    char magical[3];

    if (fscanf(file, "%s", magical) != 1) {
        return error(0x7CF); //Fichier malformé
    }

    if (strcmp(magical, "P2") != 0) {
        return error(0x7CF); //Fichier malformé
    }


    if (fscanf(file, "%hu %hu", &(*image)->height, &(*image)->width) != 2) {
        return error(0x7CF); //Fichier malformé
    }

    if (fscanf(file, "%hu", &(*image)->limits) != 1) {
        return error(0x7CF); //Fichier malformé
    }

    (*image)->matrix = malloc(sizeof(*(*image)->matrix) * (*image)->height);

    if ((*image)->matrix == NULL) {
        free(*image);
        *image = NULL;
        return error(0x7CD); //Pas assez de mémoire
    } else {
        for (int i = 0; i < (*image)->height; i++) {
            (*image)->matrix[i] = malloc(sizeof(*(*image)->matrix[i]) * (*image)->width);
            if ((*image)->matrix[i] == NULL) {
                free_matrix((*image)->matrix, (*image)->width);
                return error(0x7CD); //Pas assez de mémoire
            }
            for (int j = 0; j < (*image)->width; j++) {
                if (fscanf(file, "%hu", &((*image)->matrix[i][j].pixel)) != 1) {

                    free_matrix((*image)->matrix, (*image)->width);

                    return error(0x7CF); //Fichier malformé
                }
            }
        }
    }
    return 0;
}

static int create_ppm_matrix(PNM **image, FILE *file) {
    (*image)->format = PPM; //On donne le format PPM a la structure

    char magical[3];

    if (fscanf(file, "%s", magical) != 1) {
        return error(0x7CF); //Fichier malformé
    }

    if (strcmp(magical, "P3") != 0) {
        return error(0x7CF); //Fichier malformé
    }

    if (fscanf(file, "%hu %hu", &(*image)->height, &(*image)->width) != 2) {
        return error(0x7CF); //Fichier malformé
    }

    if (fscanf(file, "%hu", &(*image)->limits) != 1) {
        return error(0x7CF); //Fichier malformé
    }


    (*image)->matrix = malloc(sizeof(*(*image)->matrix) * (*image)->height);

    if ((*image)->matrix == NULL) {
        free(*image);
        *image = NULL;
        return error(0x7CD); //Pas assez de mémoire
    } else {
        for (int i = 0; i < (*image)->height; i++) {
            (*image)->matrix[i] = malloc(sizeof(*(*image)->matrix[i]) * (*image)->width);
            for (int j = 0; j < (*image)->width; j++) {
                if (fscanf(file, "%hu", &((*image)->matrix[i][j].pixel_rgb.red)) != 1) {
                    free_matrix((*image)->matrix, (*image)->width);

                    return error(0x7CF); //Fichier malformé
                }
                if (fscanf(file, "%hu", &((*image)->matrix[i][j].pixel_rgb.green)) != 1) {
                    free_matrix((*image)->matrix, (*image)->width);

                    return error(0x7CF); //Fichier malformé
                }
                if (fscanf(file, "%hu", &((*image)->matrix[i][j].pixel_rgb.blue)) != 1) {
                    free_matrix((*image)->matrix, (*image)->width);

                    return error(0x7CF); //Fichier malformé
                }
            }
        }
    }
    return 0;
}

/************
 *
 * KORIAN:
 * NE GERE PAS ENCORE LES LIGNES A IGNORER (# Commentaire)
 * FICHIER DOIT SE TROUVER DANS LE MEME REPERTOIRE
 * (TEMPORAIRE)
 *
 **********/
int load_pnm(PNM **image, char *filename) {
    /*
     * Verifie si l'utilisateur a utilisé un caractere non-autorisé dans le nom du fichier
     */
    if (verify_illegal_caracters(filename) != 0) {
        return error(0x7D3); // Utilisation d'un caractere illegal
    }

    /*
     * Verifie l'extension et renvoi une erreur si elle n'est pas correcte
     */
    char *extension = get_extension(filename);
    if (extension == NULL) {
        return error(0x7CC); //Mauvaise extension
    }

    /*
     * On essaye d'alouer de la memoire pour la strucure PNM, si ca ne fonctionne pas, on renvoi une erreur
     */
    *image = malloc(sizeof(PNM));
    if (*image == NULL) {
        return error(0x7CD); //Pas assez de mémoire
    }

    /*
     * On ouvre le fichier donne et si on ne sait pas l'ouvir on envoi une erreur
     */
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return error(0x7CE); // Chargement du fichier impossible
    }

    /*
     * Execute la fonction adequat par rapport au format pour creer la matrice de l'image
     */
    int result;
    if (strcmp(extension, "PBM") == 0) {
        result = create_pbm_matrix(image, file);
        if (result != 0) return result;

    } else if (strcmp(extension, "PGM") == 0) {
        result = create_pgm_matrix(image, file);
        if (result != 0) return result;

    } else if (strcmp(extension, "PPM") == 0) {
        result = create_ppm_matrix(image, file);
        if (result != 0) return result;
    }

    /*
     * On ferme le fichier et on renvoi que tout s'est bien passé!
     */
    fclose(file);
    return 0;
}

int write_pnm(PNM *image, char *filename) {
    /*
     * On verifie si l'utilisateur n'utilise pas des caracteres illegals dans le nom du fichier
     */
    if (verify_illegal_caracters(filename) != 0) {
        return error(0x7D3); // Utilisation d'un caractere illegal
    }

    /*
     * On recupere l'extension du nom du fichier et on verifie si il correspond avec le format
     * qu'on essaye d'enregister. Dans le cas contraire on renvoi une erreur
     */
    char *extension = get_extension(filename);
    if (extension == NULL) {
        return error(0x7D0); //Mauvaise extension
    }
    if (verify_type(image->format, extension) != 0) {
        return error(0x7D4);
    }

    /*
     * On verifie qu'on essaye pas de donner un nom trop long au fichier
     */
    if (strlen(filename) > FILENAME_MAX) {
        return error(0x7D0); //Nom de fichier trop long
    }

    /*
     * On creer le fichier vide, si il y a une erreur, on l'affice a l'ecran
     */
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        return error(0x7D2); //Imopssible de creer le fichier
    }

    /*
     * On ecrit le fichier par rapport a son format
     */
    if (image->format == PBM) {
        if (fprintf(file, "%s", "P1\n") <= 0) {
            return error(0x7D5); //Impossible d'ecrire le fichier
        }
        if (fprintf(file, "%hu %hu\n", image->height, image->width) <= 0) {
            return error(0x7D5); //Impossible d'ecrire le fichier
        }

        int k = 0;
        for (int i = 0; i < image->height; i++) {
            for (int j = 0; j < image->width; j++) {
                /*
                 * On ecrit le pixel et on renvoi une erreur si il y a eu un probleme
                 */
                if (fprintf(file, "%hu ", image->matrix[i][j].pixel) <= 0) {
                    return error(0x7D5); //Impossible d'ecrire le fichier
                }

                /*
                 * On evite les lignes trop longues
                 */
                k++;
                if (k % 39 == 0) {
                    fprintf(file, "\n");
                }
            }
        }


    } else if (image->format == PGM) {
        fprintf(file, "P2\n");
        fprintf(file, "%hu %hu\n", image->height, image->width);
        fprintf(file, "%hu\n", image->limits);


        for (int i = 0; i < image->height; i++) {
            for (int j = 0; j < image->width; j++) {
                fprintf(file, "%hu ", image->matrix[i][j].pixel);
                if (j % 39 == 0) {
                    fprintf(file, "\n");
                }
            }
        }

    } else if (image->format == PPM) {
        fprintf(file, "P3\n");
        fprintf(file, "%hu %hu\n", image->height, image->width);
        fprintf(file, "%hu\n", image->limits);


        for (int i = 0; i < image->height; i++) {
            for (int j = 0; j < image->width; j++) {
                fprintf(file, "%hu ", image->matrix[i][j].pixel_rgb.red);
                fprintf(file, "%hu ", image->matrix[i][j].pixel_rgb.green);
                fprintf(file, "%hu ", image->matrix[i][j].pixel_rgb.blue);
                if (j % 12 == 0) {
                    fprintf(file, "\n");
                }
            }
        }
    }

    /*
     * On ferme le fichier et on renvoi un OK :)
     */
    fclose(file);
    return 0;
}

int free_matrix(Pixel **matrix, unsigned int columns) {
    for (unsigned int i = 0; i < columns; i++)
        free(matrix[i]);
    free(matrix);
    matrix = NULL;
    return 0;
}

void help_pnm(void) {
    printf(ANSI_COLOR_CYAN "Usage:\n" ANSI_COLOR_RESET);
    printf("\t./pnm [options] [arguments] filepath\n\n");
    printf(ANSI_COLOR_CYAN "Options:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "\t-h" ANSI_COLOR_RESET "\t Display this help message\n");
    printf(ANSI_COLOR_GREEN "\t-f" ANSI_COLOR_RESET "\t Format used (PBM, PGM or PPM)\n\n");
}


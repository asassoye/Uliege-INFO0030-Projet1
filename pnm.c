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
#include <assert.h>

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
 * create_pbm_matrix
 *
 * Charge un fichier PBM en memoire
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param file le pointeur vers le fichier en memoire
 *
 * @pre: image != NULL, filename != NULL
 * @post: Le fichier est chargé dans la memoire
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *    -4 Erreur diverse
 *
 */
static int create_pbm_matrix(PNM **image, FILE *file);

/**
 * create_pgm_matrix
 *
 * Charge un fichier PGM en memoire
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param file le pointeur vers le fichier en memoire
 *
 * @pre: image != NULL, filename != NULL
 * @post: Le fichier est chargé dans la memoire
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *    -4 Erreur diverse
 *
 */
static int create_pgm_matrix(PNM **image, FILE *file);

/**
 * create_ppm_matrix
 *
 * Charge un fichier PPM en memoire
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param file le pointeur vers le fichier en memoire
 *
 * @pre: image != NULL, filename != NULL
 * @post: Le fichier est chargé dans la memoire
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *    -4 Erreur diverse
 *
 */
static int create_ppm_matrix(PNM **image, FILE *file);

/**
 * ignore_comment
 *
 * Verifie si un commentaire est présent et si cest le cas, lit le commentaire complet
 *
 * @param file le pointeur vers le fichier en memoire
 *
 * @pre: image != NULL, filename != NULL
 * @post: Le fichier est chargé dans la memoire
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *    -4 Erreur diverse
 *
 */
static int ignore_comment(FILE *file);


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



static int create_pbm_matrix(PNM **image, FILE *file) {
    (*image)->format = PBM; //On donne le format PGM a la structure

    char magical[3];

    ignore_comment(file);

    if (fscanf(file, "%s", magical) != 1) {
        return error(0x7CF); //Fichier malformé
    }

    if (strcmp(magical, "P1") != 0) {
        return error(0x7CF); //Fichier malformé
    }

    ignore_comment(file);

    if (fscanf(file, "%hu %hu", &(*image)->height, &(*image)->width) != 2) {
        return error(0x7CF); //Fichier malformé
    }

    ignore_comment(file);

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

    ignore_comment(file);

    if (fscanf(file, "%s\n", magical) != 1) {
        return error(0x7CF); //Fichier malformé
    }

    if (strcmp(magical, "P2") != 0) {
        return error(0x7CF); //Fichier malformé
    }


    ignore_comment(file);

    if (fscanf(file, "%hu %hu", &(*image)->height, &(*image)->width) != 2) {
        return error(0x7CF); //Fichier malformé
    }

    ignore_comment(file);

    if (fscanf(file, "%hu", &(*image)->limits) != 1) {
        return error(0x7CF); //Fichier malformé
    }

    ignore_comment(file);

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

    ignore_comment(file);

    if (fscanf(file, "%s\n", magical) != 1) {
        return error(0x7CF); //Fichier malformé
    }

    ignore_comment(file);

    if (strcmp(magical, "P3") != 0) {
        return error(0x7CF); //Fichier malformé
    }

    ignore_comment(file);

    if (fscanf(file, "%hu %hu", &(*image)->height, &(*image)->width) != 2) {
        return error(0x7CF); //Fichier malformé
    }

    ignore_comment(file);

    if (fscanf(file, "%hu", &(*image)->limits) != 1) {
        return error(0x7CF); //Fichier malformé
    }


    ignore_comment(file);


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

static int ignore_comment(FILE *file) {
        assert(file != NULL);

        char character = '\0';
        if(fscanf(file, "#%c", &character) != 0){
            while(character != '\n'){
                fscanf(file, "%c", &character);
            }
            return -1;
        }else {
            return 0;
        }

}


int load_pnm(PNM **image, char *filename) {

    if (verify_illegal_caracters(filename) != 0) {
        return error(0x7D3); // Utilisation d'un caractere illegal
    }


    char *extension = get_extension(filename);
    if (extension == NULL) {
        return error(0x7CC); //Mauvaise extension
    }


    *image = malloc(sizeof(PNM));
    if (*image == NULL) {
        return error(0x7CD); //Pas assez de mémoire
    }


    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return error(0x7CE); // Chargement du fichier impossible
    }


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


    fclose(file);
    return 0;
}

int write_pnm(PNM *image, char *filename) {

    if (verify_illegal_caracters(filename) != 0) {
        return error(0x7D3); // Utilisation d'un caractere illegal
    }


    char *extension = get_extension(filename);
    if (extension == NULL) {
        return error(0x7D0); //Mauvaise extension
    }
    if (verify_type(image->format, extension) != 0) {
        return error(0x7D4);
    }


    if (strlen(filename) > FILENAME_MAX) {
        return error(0x7D0); //Nom de fichier trop long
    }


    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        return error(0x7D2); //Imopssible de creer le fichier
    }


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

                if (fprintf(file, "%hu ", image->matrix[i][j].pixel) <= 0) {
                    return error(0x7D5); //Impossible d'ecrire le fichier
                }


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


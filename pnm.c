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
 * Déclaration du type opaque RGB
 *
 */
typedef struct RGB_t RGB;

/**
 * Déclaration du type opaque Pixel
 *
 */
typedef struct Pixel_t Pixel;

/**
 * Déclaration du type opaque Format
 *
 */
typedef enum Format_t Format;


/**
 * Definition du type RGB
 */
static struct RGB_t {
    unsigned short red;
    unsigned short green;
    unsigned short blue;
};

/**
 * Definition du type Pixel
 */
static struct Pixel_t {
    union {
        unsigned short pixel;
        RGB pixel_rgb;
    };
};

/**
 * Definition du type Format
 */
static enum Format_t {
    PBM, PGM, PPM
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


int load_pnm(PNM **image, char *filename) {

    char *extension = get_extension(filename);

    if (extension == NULL) {
        return error(0x7CC); //Mauvaise extension
    }

    *image = malloc(sizeof(PNM));

    /*
     * On verifie qu'on a bien su allouer la memoire necessaire, sinon on arrete l'execution
     */
    if (*image == NULL) {
        return error(0x7CD); //Pas assez de mémoire
    }


    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return error(0x7CE); // Chargement du fichier impossible
    }

    if (strcmp(extension, "PBM") == 0) {
        (*image)->format = PBM; //On donne le format PBM a la structure

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

            return error(0x7CD); //Pas assez de memoire
        } else {
            for (int i = 0; i < (*image)->height; i++) {
                (*image)->matrix[i] = malloc(sizeof(*(*image)->matrix[i]) * (*image)->width);
                for (int j = 0; j < (*image)->width; j++) {
                    if (fscanf(file, "%hu", &((*image)->matrix[i][j].pixel)) != 1) {
                        free(*image);
                        free((*image)->matrix); //TODO: free recursif :)

                        return error(0x7CF); //Fichier malformé
                    }
                }
            }
        }


    } else if (strcmp(extension, "PGM") == 0) {

        (*image)->format = PGM; //On donne le format PGM a la structure

        char magical[3];

        if (fscanf(file, "%s", magical) != 1) {
            return error(0x7CF); //Fichier malformé
        }

        if (strcmp(magical, "P2") != 0) {
            printf(ANSI_COLOR_RED "Error: Your file is corrupted! (Corresponding magical number)\n" ANSI_COLOR_RESET);
            return error(0x7CF); //Fichier malformé
        }


        if (fscanf(file, "%hu %hu", &(*image)->height, &(*image)->width) != 2) {
            printf(ANSI_COLOR_RED "Error: Your file is corrupted! (Impossible to define dimensions)\n" ANSI_COLOR_RESET);
            return error(0x7CF); //Fichier malformé
        }

        if (fscanf(file, "%hu", &(*image)->limits) != 1) {
            printf("Error: Your file is corrupted (limits)");
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
                    free(*image);
                    *image = NULL;
                    return error(0x7CD); //Pas assez de mémoire
                }
                for (int j = 0; j < (*image)->width; j++) {
                    if (fscanf(file, "%hu", &((*image)->matrix[i][j].pixel)) != 1) {

                        free(*image);
                        free((*image)->matrix); //TODO: free recursif :)

                        return error(0x7CF); //Fichier malformé
                    }
                }
            }
        }


    } else if (strcmp(extension, "PPM") == 0) {
        (*image)->format = PPM; //On donne le format PPM a la structure

        char magical[3];

        if (fscanf(file, "%s", magical) != 1) {
            return error(0x7CF); //Fichier malformé
        }

        if (strcmp(magical, "P3") != 0) {
            printf("Error: Your file is corrupted! (magical)");
            return error(0x7CF); //Fichier malformé
        }

        if (fscanf(file, "%hu %hu", &(*image)->height, &(*image)->width) != 2) {
            printf("Error: Your file is corrupted (size)");
            return error(0x7CF); //Fichier malformé
        }

        if (fscanf(file, "%hu", &(*image)->limits) != 1) {
            printf("Error: Your file is corrupted (Limits)");
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
                        free(*image);
                        free((*image)->matrix); //TODO: free recursif :)

                        return error(0x7CF); //Fichier malformé
                    }
                    if (fscanf(file, "%hu", &((*image)->matrix[i][j].pixel_rgb.green)) != 1) {
                        free(*image);
                        free((*image)->matrix); //TODO: free recursif :)

                        return error(0x7CF); //Fichier malformé
                    }
                    if (fscanf(file, "%hu", &((*image)->matrix[i][j].pixel_rgb.blue)) != 1) {
                        free(*image);
                        free((*image)->matrix); //TODO: free recursif :)

                        return error(0x7CF); //Fichier malformé
                    }
                }
            }
        }
    }

    fclose(file);
    return 0;
}

int write_pnm(PNM *image, char *filename) {

    char *extension = get_extension(filename);
    if (extension == NULL) {
        return error(0x7D0); //Mauvaise extension
    }

    if (strlen(filename) > FILENAME_MAX) {
        return error(0x7D0); //Nom de fichier trop long
    }

    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        return error(0x7D2); //Imopssible de creer le fichier
    }

    if (image->format == PBM) {
        fprintf(file, "P1\n");
        fprintf(file, "%hu %hu\n", image->height, image->width);

        for (int i = 0; i < image->height; i++) {
            for (int j = 0; j < image->width; j++) {
                fprintf(file, "%hu ", image->matrix[i][j].pixel);
                if (j % 39 == 0) {
                    fprintf(file, "\n");
                }
            }
        }

        fclose(file);

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

        fclose(file);
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

        fclose(file);
    }

    return 0;
}


void help_pnm() {
    printf(ANSI_COLOR_CYAN "Usage:\n" ANSI_COLOR_RESET);
    printf("\tcommand [options] [arguments] filepath\n\n");
    printf(ANSI_COLOR_CYAN "Options:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "\t-h" ANSI_COLOR_RESET "\t Display this help message\n");
    printf(ANSI_COLOR_GREEN "\t-f" ANSI_COLOR_RESET "\t Format used (PBM, PGM or PPM)\n\n");

}

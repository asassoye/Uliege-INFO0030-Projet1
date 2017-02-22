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

/**
 * Definition du type RGB
 */
typedef struct RGB_t {
    unsigned short red;
    unsigned short green;
    unsigned short blue;
} RGB;

/**
 * Definition du type ImageMatrix
 */
typedef struct Pixel_t {
    union {
        unsigned short pixel;
        RGB pixel_rgb;
    };
} Pixel;

typedef enum Format_t {
    PBM, PGM, PPM
} Format;

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
        printf("EXTENSION FAULT\n");
        return -2;
    }

    *image = malloc(sizeof(PNM));

    /*
     * On verifie qu'on a bien su allouer la memoire necessaire, sinon on arrete l'execution
     */
    if (*image == NULL) {
        printf("MALLOC\n");
        return NULL; //TODO: bon type de retour
    }

    printf("Filename: %s\n", filename);

    FILE *file = fopen(filename, "r");
    printf("hey");

    if (file == NULL) {
        printf("Impossible to load %s\n", filename);
        return -2;
    }
    if (strcmp(extension, "PBM") == 0) {
        (*image)->format = PBM; //On donne le format PBM a la structure

        char magical[3];

        if (fscanf(file, "%s", magical) != 1) {
            return -3; //Le fichier est malforme
        }

        if (strcmp(magical, "P1") != 0) {
            printf("Error: Your file is corrupted!");
            return -3; //Le fichier est malforme
        }

        if (fscanf(file, "%hu %hu", &(*image)->height, &(*image)->width) != 2) {
            printf("Error: Your file is corrupted");
            return -3; //Le fichier est malforme
        }


        Pixel **loading = malloc(sizeof(*loading) * (*image)->height);

        if (loading == NULL) {
            printf("Error: Not enough memory!");
            return -1;
        } else {
            for (int i = 0; i < (*image)->height; i++) {
                loading[i] = malloc(sizeof(*loading[i]) * (*image)->width);
                for (int j = 0; j < (*image)->width; j++) {
                    if (fscanf(file, "%hu", &(loading[i][j].pixel)) != 1) {
                        printf("Error: Your file is corrupted");
                        return -3;
                    }
                }
            }
        }

        (*image)->matrix = loading;
    }


    fclose(file);
    return 0;
}

int write_pnm(PNM *image, char *filename) {

    /* Insérez le code ici */

    return 0;
}


void help_pnm() {
    printf("-h for help\n"
                   "-f choose format\n");
}

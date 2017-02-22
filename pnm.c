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

    printf("%s", extension);
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


        (*image)->matrix = malloc(sizeof(*(*image)->matrix) * (*image)->height);

        if ((*image)->matrix == NULL) {
            free(*image);
            *image = NULL;
            printf("Error: Not enough memory!");
            return -1;
        } else {
            for (int i = 0; i < (*image)->height; i++) {
                (*image)->matrix[i] = malloc(sizeof(*(*image)->matrix[i]) * (*image)->width);
                for (int j = 0; j < (*image)->width; j++) {
                    if (fscanf(file, "%hu", &((*image)->matrix[i][j].pixel)) != 1) {
                        printf("Error: Your file is corrupted");
                        free(*image);
                        free((*image)->matrix); //TODO: free recursif :)

                        return -3;
                    }
                }
            }
        }



    }else if (strcmp(extension, "PGM") == 0) {

        (*image)->format = PGM; //On donne le format PGM a la structure

        char magical[3];

        if (fscanf(file, "%s", magical) != 1) {
            return -3; //Le fichier est malforme
        }

        if (strcmp(magical, "P2") != 0) {
            printf("Error: Your file is corrupted! (magical)");
            return -3; //Le fichier est malforme
        }



        if (fscanf(file, "%hu %hu", &(*image)->height, &(*image)->width) != 2) {
            printf("Error: Your file is corrupted (size)");
            return -3; //Le fichier est malforme
        }

        if (fscanf(file, "%hu", &(*image)->limits) != 1) {
            printf("Error: Your file is corrupted (limits)");
            return -3; //Le fichier est malforme
        }

        (*image)->matrix = malloc(sizeof(*(*image)->matrix) * (*image)->height);

        if ((*image)->matrix == NULL) {
            free(*image);
            *image = NULL;
            printf("Error: Not enough memory!");
            return -1;
        } else {
            for (int i = 0; i < (*image)->height; i++) {
                (*image)->matrix[i] = malloc(sizeof(*(*image)->matrix[i]) * (*image)->width);
                if ((*image)->matrix[i] == NULL) {
                    free(*image);
                    *image = NULL;
                    printf("Error: Not enough memory!");
                    return -1;
                }
                for (int j = 0; j < (*image)->width; j++) {
                    if (fscanf(file, "%hu", &((*image)->matrix[i][j].pixel)) != 1) {
                        printf("Error: Your file is corrupted (pixels)");
                        free(*image);
                        free((*image)->matrix); //TODO: free recursif :)

                        return -3;
                    }
                }
            }
        }



    } else if (strcmp(extension, "PPM") == 0) {
        (*image)->format = PPM; //On donne le format PPM a la structure

        char magical[3];

        if (fscanf(file, "%s", magical) != 1) {
            return -3; //Le fichier est malforme
        }

        if (strcmp(magical, "P3") != 0) {
            printf("Error: Your file is corrupted! (magical)");
            return -3; //Le fichier est malforme
        }

        if (fscanf(file, "%hu %hu", &(*image)->height, &(*image)->width) != 2) {
            printf("Error: Your file is corrupted (size)");
            return -3; //Le fichier est malforme
        }

        if (fscanf(file, "%hu", &(*image)->limits) != 1) {
            printf("Error: Your file is corrupted (Limits)");
            return -3; //Le fichier est malforme
        }

        printf("%hu %hu", (*image)->height, (*image)->width);

        (*image)->matrix = malloc(sizeof(*(*image)->matrix) * (*image)->height);

        if ((*image)->matrix == NULL) {
            free(*image);
            *image = NULL;
            printf("Error: Not enough memory!");
            return -1;
        } else {
            for (int i = 0; i < (*image)->height; i++) {
                (*image)->matrix[i] = malloc(sizeof(*(*image)->matrix[i]) * (*image)->width);
                for (int j = 0; j < (*image)->width; j++) {
                    if (fscanf(file, "%hu", &((*image)->matrix[i][j].pixel_rgb.red)) != 1) {
                        printf("Error: Your file is corrupted (RED)");
                        free(*image);
                        free((*image)->matrix); //TODO: free recursif :)

                        return -3;
                    }
                    if (fscanf(file, "%hu", &((*image)->matrix[i][j].pixel_rgb.green)) != 1) {
                        printf("Error: Your file is corrupted (GREEN)");
                        free(*image);
                        free((*image)->matrix); //TODO: free recursif :)

                        return -3;
                    }
                    if (fscanf(file, "%hu", &((*image)->matrix[i][j].pixel_rgb.blue)) != 1) {
                        printf("Error: Your file is corrupted(BLUE)");
                        free(*image);
                        free((*image)->matrix); //TODO: free recursif :)

                        return -3;
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
        printf("EXTENSION FAULT\n");
        return -1;
    }

    if(strlen(filename) > FILENAME_MAX){
        printf("Error: Your filename is to long!");
        return -1;
    }

    FILE *file = fopen(filename, "w");

    if(file == NULL){
        printf("Error: Impossible to create %s", filename);
        return -2;
    }

    if(image->format == PBM){
        fprintf(file, "P1\n");
        fprintf(file, "%hu %hu\n", image->height, image->width);



        for(int i = 0; i < image->height; i++){
            for(int j = 0; j < image->width; j++){
                fprintf(file, "%hu ", image->matrix[i][j].pixel);
                if(j%39 == 0){
                    fprintf(file, "\n");
                }
            }
        }

        fclose(file);

    }else if(image->format == PGM){
        fprintf(file, "P2\n");
        fprintf(file, "%hu %hu\n", image->height, image->width);
        fprintf(file, "%hu\n", image->limits);


        for(int i = 0; i < image->height; i++){
            for(int j = 0; j < image->width; j++){
                fprintf(file, "%hu ", image->matrix[i][j].pixel);
                if(j%39 == 0){
                    fprintf(file, "\n");
                }
            }
        }

        fclose(file);
    }else if(image->format == PPM){
        fprintf(file, "P3\n");
        fprintf(file, "%hu %hu\n", image->height, image->width);
        fprintf(file, "%hu\n", image->limits);


        for(int i = 0; i < image->height; i++){
            for(int j = 0; j < image->width; j++){
                fprintf(file, "%hu ", image->matrix[i][j].pixel_rgb.red);
                fprintf(file, "%hu ", image->matrix[i][j].pixel_rgb.green);
                fprintf(file, "%hu ", image->matrix[i][j].pixel_rgb.blue);
                if(j%39 == 0){
                    fprintf(file, "\n");
                }
            }
        }

        fclose(file);
    }

    return 0;
}


void help_pnm() {
    printf("-h for help\n"
                   "-f choose format\n");
}

/**
 * pnm.c
 * 
 * Ce fichier contient les définitions de types et 
 * les fonctions de manipulation d'images PNM.
 * 
 * @author: Sassoye Andrew 20160135
 * @date: 
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pnm.h"
#include "verifications.h"


/**
 * Définition du type opaque PNM
 *
 */
struct PNM_t {
    enum{PBM, PGM, PPM} format;
    unsigned short width;
    unsigned short height;
    unsigned short max_value;
    unsigned short *pixel;

};


int load_pnm(PNM **image, char* filename) {

    char *extension = get_extension(filename);

    if(extension == NULL){
        return -2;
    }

    *image = malloc(sizeof(PNM)*1000000000000000000);

    if(*image == NULL){
        printf("COUCOU\n");
    }

    (*image)->width = 100;

    printf("size:%zu\n", sizeof(PNM));

    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Impossible to load %s\n", filename);
        return -2;
    }

    return 0;
}

int write_pnm(PNM *image, char* filename) {

   /* Insérez le code ici */

   return 0;
}


void help_pnm(){
    printf("-h for help\n"
                   "-f choose format\n");
}

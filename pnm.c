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
#include <assert.h>

#include "pnm.h"


/**
 * Définition du type opaque PNM
 *
 */
struct PNM_t {
    enum {PBM, PGM, PPM} type;
    unsigned int width, height;

};


int load_pnm(PNM **image, char* filename) {

   /* Insérez le code ici */

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

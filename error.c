/**
 * error.c
 *
 * Ce fichier contient les code erreurs et leurs valeurs de retour
 *
 * @author: Sassoye Andrew 20160135
 * @date: 23/02/2017
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <assert.h>
#include "error.h"


#ifndef __ANSI_
#define __ANSI_

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#endif

/**
 * error_print
 *
 * Affiche un message formaté a l'ecran
 *
 * @param message, pointeur sur char
 *
 * @pre: error != 0
 * @post: Affiche l'erreur formaté a l'ecran
 *
 * @return: message a afficher
 *
 */
static void error_print(char *error);

int error(int code){
    assert(code != 0);

    switch(code){
        case 0x7CC:
            error_print("Error 0x7CC: Your import file must have PBM, PGM or PPM extension!");
            return -2;
        case 0x7CD:
            error_print("Error 0x7CD: Not enough memory!");
            return -1;
        case 0x7CE:
            error_print("Error 0x7CE: Impossible to load file!");
            return -2;
        case 0x7CF:
            error_print("Error 0x7CF: Your file is corrupted!");
            return -3;
        case 0x7D0:
            error_print("Error 0x7D0: Your export file must have PBM, PGM or PPM extension!");
            return -1;
        case 0x7D1:
            error_print("Error 0x7D1: Your filename is too long!");
            return -1;
        case 0x7D2:
            error_print("Error 0x7D2: Impossible to create file!");
            return -2;
        case 0x7D3:
            error_print("Error 0x7D3: You used a illegal caracter in filename!");
            return -2;
        case 0x7D4:
            error_print("Error 0x7D4: Your file you want to save is not compatible with extension");
            return -2;
        case 0x7D5:
            error_print("Error 0x7D5: Impossible to write file");
            return -2;
        default:
            error_print("Error!");
            return -4;
    }
}

static void error_print(char *error){
    assert(error != NULL);
    printf(ANSI_COLOR_RED "%s\n\n" ANSI_COLOR_RESET, error);
}

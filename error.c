//
// Created by Andrew Sassoye on 22/02/17.
//
#include <stdio.h>
#include <stdlib.h>
#include "error.h"


#ifndef __ANSI_
#define __ANSI_

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#endif

int error(int code){
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
            return -3; //Le fichier est malforme
        case 0x7D0:
            error_print("Error 0x7D0: Your export file must have PBM, PGM or PPM extension!");
            return -1;
        case 0x7D1:
            error_print("Error 0x7D1: Your filename is too long!");
            return -1;
        case 0x7D2:
            error_print("Error 0x7D2: Impossible to create file!");
            return -2;
        default:
            error_print("Error!");
            return -5;
    }
}

void error_print(char *error){
    printf(ANSI_COLOR_RED "%s\n\n" ANSI_COLOR_RESET, error);
}
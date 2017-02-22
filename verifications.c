//
// Created by Andrew Sassoye on 20/02/17.
//

#include <stdio.h>
#include <string.h>
#include "verifications.h"

#ifndef __ANSI_
#define __ANSI_

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#endif

char *get_extension(char *file){
    const char *extension = strchr(file, '.');

    /*
     * Check if there is an extension and returns his type (if is PBM, PGM or PPM file)
     */
    if(extension != NULL && strlen(extension) != 1){
        if(strcmp(extension, ".PBM") == 0 || strcmp(extension, ".pbm") == 0){
            return "PBM";
        }else if(strcmp(extension, ".PGM") == 0 || strcmp(extension, ".pgm") == 0){
            return "PGM";
        }else if(strcmp(extension, ".PPM") == 0 || strcmp(extension, ".ppm") == 0){
            return "PPM";
        }else {
            return NULL;
        }
    }
    else {
        return NULL;
    }//end if-statement
}

int verify_type(char *type, char *file){
    char *extention = get_extension(file);

    if(extention != NULL){
        if(strcmp(type, extention) == 0){
            return 0;
        }
        else{
            printf("Error: The specified format is not the same as the file extension!");
            return NULL;
        }
    }
    else{
        return NULL;
    }//end if-statement
};


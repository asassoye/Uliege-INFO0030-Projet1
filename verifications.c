//
// Created by Andrew Sassoye on 20/02/17.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "verifications.h"
#include "error.h"
#include "pnm.h"

#ifndef __ANSI_
#define __ANSI_

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#endif

char *get_extension(char *file) {
    const char *extension = strchr(file, '.');

    /*
     * Check if there is an extension and returns his type (if is PBM, PGM or PPM file)
     */
    if (extension != NULL && strlen(extension) != 1) {
        if (strcmp(extension, ".PBM") == 0 || strcmp(extension, ".pbm") == 0) {
            return "PBM";
        } else if (strcmp(extension, ".PGM") == 0 || strcmp(extension, ".pgm") == 0) {
            return "PGM";
        } else if (strcmp(extension, ".PPM") == 0 || strcmp(extension, ".ppm") == 0) {
            return "PPM";
        } else {
            return NULL;
        }
    } else {
        return 0;
    }//end if-statement
}

int verify_type(Format format, char *extension) {
    if ((strcmp(extension, "PBM") == 0 && format == PBM) ||
        (strcmp(extension, "PGM") == 0 && format == PGM) ||
        (strcmp(extension, "PPM") == 0 && format == PPM)) {
        return 0;
    } else {
        return -1;
    }
}

int verify_illegal_caracters(char *filename) {
    char *illegal = "/\\:*?\"<>|";


    for (size_t i = 0; i < strlen(filename); i++) {
        for (size_t j = 0; j < strlen(illegal); j++) {
            if (filename[i] == illegal[j]) {
                return -1;
            }
        }
    }
    return 0;
}

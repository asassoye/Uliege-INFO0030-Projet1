//
// Created by Andrew Sassoye on 20/02/17.
//

#include <stdio.h>
#include <string.h>
#include "verifications.h"


char *get_extension(char *file){
    const char *extension = strchr(file, '.');

    /*
     * Check if there is an extension and returns his type (if is PBM, PGM or PPM file)
     */
    if(extension != NULL && strlen(extension) != 1){
        if(strcmp(extension, ".PBM")){
            return "PBM";
        }else if(strcmp(extension, ".PGM")){
            return "PGM";
        }else if(strcmp(extension, ".PPM")){
            return "PPM";
        }else {
            printf("Error: Your file must have PBM, PGM or PPM extension!");
            return NULL;
        }
    }
    else {
        printf("Error: Please give a correct file\n");
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


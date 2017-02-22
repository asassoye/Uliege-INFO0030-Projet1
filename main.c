/**
 * main.c
 * 
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: Sassoye Andrew 20160315
 * @date:
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include "pnm.h"
#include "verifications.h"

#ifndef __ANSI_
#define __ANSI_

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#endif

int main(int argc, char **argv) {

    const char *optstring = ":hf::";
    int option;

    PNM *image = NULL;

    printf(ANSI_COLOR_GREEN "\nPNM " ANSI_COLOR_RESET "v1 created by " ANSI_COLOR_CYAN "Andrew Sassoye\n\n" ANSI_COLOR_RESET);

    while (EOF != (option = getopt(argc, argv, optstring))) {
        switch (option) {
            case 'h':
                help_pnm();
                return 0;
            case 'f':
                printf(ANSI_COLOR_CYAN "Loading file...\n\n" ANSI_COLOR_RESET);
                if(load_pnm(&image, argv[argc-1]) != 0){
                    return -1;
                }
                printf(ANSI_COLOR_GREEN "File correctly load in memory!\n\n" ANSI_COLOR_RESET);

                char save;


                    printf("Do you want to save the loaded image?[y,n]");
                    scanf("%c", &save);
                    printf("\n");


                if(save == 'y'){
                    char filename[FILENAME_MAX];
                    printf("Which name do you want to give to your file?");
                    scanf("%s", filename);
                    printf("\n");
                    if(write_pnm(image, filename) == 0){
                        printf(ANSI_COLOR_GREEN "File correctly saved!\n\n" ANSI_COLOR_RESET);
                    }else {
                        return -1;
                    }
                }

                return 0;
            case '?':
                printf(ANSI_COLOR_RED "Unknown option: %c\n" ANSI_COLOR_RESET, optopt);
                return 0;
            case ':':
                printf(ANSI_COLOR_RED "Missing argument: %c\n" ANSI_COLOR_RESET, optopt);
                return 0;
            default:
                help_pnm();
                return 0;
        } //end switch
    } //end while

    return 0;
}

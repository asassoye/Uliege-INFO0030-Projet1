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


int main(int argc, char **argv) {

    const char *optstring = ":hf::";
    int option;


    PNM *image = NULL;

    load_pnm(&image, "read.pbm");



   // while (EOF != (option = getopt(argc, argv, optstring))) {
   //     switch (option) {
   //         case 'h':
   //             help_pnm();
   //             return 0;
   //         case 'f':
   //             printf("Format: %s\n", optarg);
   //             printf("fichier: %s", argv[argc-1]);
   //             return 0;
   //         case '?':
   //             printf("Unknown option: %c\n", optopt);
   //             return 0;
   //         case ':':
   //             printf("Missing argument: %c\n", optopt);
   //             return 0;
   //         default:
   //             help_pnm();
   //             return 0;
   //     } //end switch
   // } //end while

    return 0;
}

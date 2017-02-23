//
// Created by Andrew Sassoye on 20/02/17.
//

#ifndef __VERIFICATIONS_H__
#define __VERIFICATIONS_H__

#include "pnm.h"

int verify_type(Format format, char *extension);

char *get_extension(char *file);

int verify_illegal_caracters(char *filename);

#endif //__VERIFICATIONS_H__

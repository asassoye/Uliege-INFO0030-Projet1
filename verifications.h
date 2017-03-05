/**
 * error.h
 *
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions de verifications
 *
 * @author: Sassoye Andrew 20160135
 * @date:
 * @projet: INFO0030 Projet 1
 */


#ifndef __VERIFICATIONS_H__
#define __VERIFICATIONS_H__

#include "pnm.h"

/**
 * verify_type
 *
 * Verifie le type
 *
 * @param format entier format de type enum Format
 * @param extension un pointeur sur char du nom de l'extension
 *
 * @pre: /
 * @post: A verifié si le format correspond
 *
 * @return:
 *      0 succes
 *      -1 Error
 *
 */
int verify_type(Format format, char *extension);

/**
 * get_extension
 *
 * Verifie l'extnsion
 *
 * @param file pointeur vers nom du fichier
 *
 * @pre: /
 * @post: retourne l'extension
 *
 * @return:
 *      0 succes
 *      NULL erreur dans l'extension
 *
 */
char *get_extension(char *file);

/**
 * verify_illegal_Caracters
 *
 * Verifie si on utilise pas de caracteres illegals dans le nom de fichier
 *
 * @param file pointeur vers nom du fichier
 *
 * @pre: /
 * @post: a verifié le nom de fichier
 *
 * @return:
 *      0 succes
 *      -1 Utilisation de caractere illegal
 *
 */
int verify_illegal_caracters(char *filename);

#endif //__VERIFICATIONS_H__

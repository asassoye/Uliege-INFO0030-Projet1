/**
 * error.h
 *
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions d'erreur
 *
 * @author: Sassoye Andrew 20160135
 * @date:
 * @projet: INFO0030 Projet 1
 */

#ifndef __ERROR_H__
#define __ERROR_H__

/**
 * error
 *
 * Affiche une erreur a l'ecran et retourne la valeur de l'erreur.
 *
 * @param code erreur (entier)
 *
 * @pre: code != NULL
 * @post: Affiche l'erreur a l'ecran
 *
 * @return: entier erreur definit par le prof
 *
 */
int error(int code);

#endif //__ERROR_H__

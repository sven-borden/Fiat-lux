/*
    Fichier:    reflecteur.h
    Auteur:     Alix Nepveux & Sven Borden
    Date :      16 mars 2016
    Version:    1.0
    Description:Module reflecteur qui gere la structure 
*/

#ifndef REFLECTEUR_H
#define REFLECTEUR_H

#include "utilitaire.h"
//verifie les valeurs et les enregistre dans la structure
int reflecteurSet(char[]);/*ajoute un photon a partir d'une ligne*/
int addReflecteur(POINT, double);/*ajoute un photon dans la liste*/
int delReflecteur(POINT, double);/*supprime un photon de la liste*/
void printListReflecteur(void);/*imprime la liste des reflecteurs*/
void delListPhoton(void);/*nettoir la memoire en supprimant refle*/
#endif

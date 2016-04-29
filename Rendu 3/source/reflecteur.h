/*
    Fichier:    reflecteur.h
    Auteur:     Alix Nepveux & Sven Borden
    Date :      20 avril 2016
    Version:    1.1
    Description:Module reflecteur qui gere la structure 
*/

#ifndef REFLECTEUR_H
#define REFLECTEUR_H

#include <stdio.h>
#include "utilitaire.h"

/*Ajoute un reflecteur par une ligne*/
int reflecteurSet(char[]);
/*Ajoute un reflecteur dans la liste manuellement*/
int addReflecteur(POINT, POINT);
/*Supprime un reflecteur de la liste*/
int delReflecteur(int);
/*Ecrit dans un fichier la liste des reflecteurs*/
void writeReflecteur(FILE *);
/*Dessine les reflecteurs*/
void drawRefl(void);
/*Print en console la liste des reflecteurs*/
void printListReflecteur(void);
/*Supprime la liste complète des reflecteurs*/
void delListReflecteur(void);
/*Retourne le nombre de reflecteurs*/
int nbRefl(void);
/*Vérifie les intersection entre reflecteurs*/
int interReflecteur(void);
/*Vérifie les intersections entre refl et abs*/
int reflInterAbs(void);
/*Vérifie les intersections entre refl et proj*/
int reflInterProj(void);
#endif

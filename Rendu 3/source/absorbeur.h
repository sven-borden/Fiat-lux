/*
    Fichier:    absorbeur.h
    Auteur:     Alix Nepveux & Sven Borden
    Date :      16 mars 2016
    Version:    0.9
    Description:Module absorbeur qui gere cette structure  
*/

#ifndef ABSORBEUR_H
#define ABSORBEUR_H

#include <stdio.h>
#include "utilitaire.h"

/*Ajoute un absorbeur par une ligne*/
int absorbeurSet(char[]);
/*Ajoute un absorbeur dans la liste manuellement*/
int addAbsorbeur(int, POINT[]);
/*Supprime un absorbeur de la liste*/
int delAbsorveur(int);
/*Ecrit dans un fichier la liste des absorbeurs*/
void writeAbsorbeur(FILE *);
/*Dessine les absorbeurs*/
void drawAbso(void);
/*Print en console la liste des absorbeurs*/
void printListAbsorbeur(void);
/*Supprime la liste complète des absorbeurs*/
void delListAbsorbeur(void);
/*Retourne le nombre d'absorbeurs*/
int nbAbso(void);
/*Vérifie les intersection entre absorbeur et un vecteur*/
int absorbeurExt(VECTOR, int, int);
/*Calcule le point de contact pour les photons*/
POINT * absoProche(VECTOR);
#endif

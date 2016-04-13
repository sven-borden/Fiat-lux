/*
    Fichier:    absorbeur.h
    Auteur:     Alix Nepveux & Sven Borden
    Date :      16 mars 2016
    Version:    0.9
    Description:Module absorbeur qui gere cette structure  
*/

#ifndef ABSORBEUR_H
#define ABSORBEUR_H

#include "utilitaire.h"
//verifie les valeurs et les enregistre dans la structure
int absorbeurSet(char[]);
int addAbsorbeur(int, POINT[]);
int delAbsorveur(int);
void printListAbsorbeur(void);
void delListAbsorbeur(void);
#endif

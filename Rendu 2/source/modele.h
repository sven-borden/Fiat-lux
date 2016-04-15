/*
    Fichier:    main.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      16 mars 2016
    Version:    0.9
    Description:Module de simulation du projet de Programation II MT
*/
#ifndef MODELE_H
#define MODELE_H

#include "constantes.h"
//lis les donnees et dispatch les informations dans les sous modules
int modeleLecture(char fileName[]);
int modele_verification_rendu2(void);
void modeleDestroy(void);
void modeleWrite(char*);
void modeleDraw(void);
void modeleUpdate(void);
int modeleNbPhot(void);
int modeleNbRefl(void);
int modeleNbAbso(void);
int modeleNbProj(void);
#endif

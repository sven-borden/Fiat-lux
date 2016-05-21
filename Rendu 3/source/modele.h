/*
    Fichier:    modele.hc
    Auteur:     Alix Nepveux & Sven Borden
    Date :      20 avril 2016
    Version:    1.1
    Description:Module de simulation du projet de Programation II MT
*/
#ifndef MODELE_H
#define MODELE_H

#include "constantes.h"

/*Transfere la charge de lecture*/
int modeleLecture(char* fileName);
/*Vérifie les interesections (cf rendu2)*/
int modele_verification_rendu2(void);
/*Detruit la simulation actuelle*/
void modeleDestroy(void);
/*Ecrit dans un fichier l'etat actuel de la simulation*/
void modeleWrite(char*);
/*Dessine la simulation a l'etat actuel*/
void modeleDraw(void);
/*Choisi la selection*/
void modeleSelect(int8_t, double, double);
/*Deslectionne tout*/
void modeleUnselect(void);
/*Creation manuelle*/
void modeleCreation(short, short, POINT[]);
/*Met a jour la simulation*/
void modeleUpdate(void);
/*Les 4 fonctions retournent le nombre d'entité de chaque type*/
int modeleNbPhot(void);
int modeleNbRefl(void);
int modeleNbAbso(void);
int modeleNbProj(void);
/*Detruit les entité (renduFinal)*/
void modeleDestroyEntity(short entity);
/*Detruit les photons hors fenetres (renduFinal)*/
void modeleDestroyExtPhot(double, double, double, double);
/*Retourne lecture success*/
void modeleSuccess(void);
#endif

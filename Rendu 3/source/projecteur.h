/*
	Fichiers:	projecteur.h
	Autheurs:	Alix Nepveux & Sven Borden
	Date:		10 Avril 2016
	Version:	1.1
	Description:Module projecteur qui gere la structure
*/

#ifndef PROJECTEUR_H
#define PROJECTEUR_H

#include <stdio.h>
#include "utilitaire.h"

/*Ajoute un projecteur par une ligne*/
int projecteurSet(char[]);
/*Ajoute un projecteur dans la liste manuellement*/
int addProjecteur(POINT, double);
/*Supprime un projecteur de la liste*/
int delProjecteur(int);
/*Ecrit dans un fichier la liste des projecteurs*/
void writeProjecteur(FILE *);
/*Dessine les projecteurs*/
void drawProj(void);
/*Print en console la liste des projecteurs*/
void printListProjecteur(void);
/*Supprime la liste complète des projecteurs*/
void delListProjecteur(void);
/*Retourne le nombre de projecteurs*/
int nbProj(void);
/*Vérifie les intersections entre projecteur et refl*/
int projecteurExt(VECTOR, int);
/*Vérifie les projecteur avec les absorbeurs*/
int projInterAbs(void);
/*Appelle une fonction qui crée les photons de chaque projecteurs*/
void updateProjecteur(void);
#endif

/*
    Fichier:   	photon.h
    Auteur:     Alix Nepveux & Sven Borden
    Date :      20 avril 2016
    Version:    1.1
    Description:Module photon qui gere la structure photon 
*/

#ifndef PHOTON_H
#define PHOTON_H

#include <stdio.h>
#include "utilitaire.h"

/*Ajoute un photon par une ligne*/
int photonSet(char[]);
/*Ajout un photon dans la liste manuellement*/
int addPhoton(POINT, double);
/*Supprime un photon de la liste*/
int delPhoton(int);
/*Dessine les photons*/
void drawPhot(void);
/*Ecrit dans un fichier la liste des photons*/
void writePhoton(FILE *);
/*Print en console la liste des photons*/
void printListPhoton(void); 
/*Supprime la liste complète de photons*/
void delListPhoton(void); 
/*Retourn le nombre de photons*/
int nbPhot(void);
#endif

/*
    Fichier:   	reflecteur.h
    Auteur:     Alix Nepveux & Sven Borden
    Date :      30 mars 2016
    Version:    1.0
    Description:Module photon qui gere la structure photon 
*/

#ifndef PHOTON_H
#define PHOTON_H

#include "utilitaire.h"
//verifie les valeurs et les enregistre dans la structure
int photonSet(char[]);/*ajoute un photon a partir d'une ligne*/
int addPhoton(POINT, double);/*ajoute un photon dans la liste*/
int delPhoton(int);/*supprime un photon pas encore fonctionnel*/
void printListPhoton(void); /*imprime la liste des photons en mémoire*/
void delListPhoton(void); /* nettoie la mémoire en supprimant la liste de photon*/
#endif

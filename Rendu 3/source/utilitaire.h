/*
    Fichier:    utilitaire.h
    Auteur:     Alix Nepveux & Sven Borden
    Date :      16 mars 2016
    Version:    0.9
    Description:Point d'entree du projet 
*/

#ifndef UTILITAIRE_H
#define UTILITAIRE_H

//defini une structure POINT (x, y) et vecteur (point 1 point 2)
typedef struct Point POINT;
typedef struct Vector VECTOR;

struct Point
{
	double x;
	double y;
};

struct Vector
{
	POINT ptDeb;
	POINT ptFin;
};

//retourne la norme d'un vecteur
double utilitaireNormeVector(VECTOR);
//retourne la distance entre deux points
double utilitaireDistance2Points(POINT, POINT);
//calcul du produit vectoriel de deux vector
double utilitaireProduitVectoriel(VECTOR, VECTOR);
//calcul du produit scalaire
double utilitaireProduitScalaire(VECTOR, VECTOR);
/*Verifie la superposition*/
int utilitaireSuperposition(VECTOR, VECTOR);
/*Verifie l'intersection*/
POINT *utilitaireIntersection(VECTOR, VECTOR);
//swap
void utilitaireSwap(double*, double*);
#endif

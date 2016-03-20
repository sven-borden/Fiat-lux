/*
    Fichier:    main.c
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
#endif

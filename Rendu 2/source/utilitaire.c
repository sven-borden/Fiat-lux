/*
    Fichier:    utilitaire.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      16 mars 2016
    Version:    0.9
    Description:Module de base qui contient des fonctions basique
                et des structures simples 
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "utilitaire.h"

#define OUI	1
#define NON	0

double utilitaireNormeVector(VECTOR v)
{
	double xLen = v.ptFin.x - v.ptDeb.x;
	double yLen = v.ptFin.y - v.ptDeb.y;
	return sqrt(xLen*xLen + yLen*yLen); 
}

double utilitaireDistance2Points(POINT a, POINT b)
{
	double xLen = b.x - a.x;
	double yLen = b.y - a.y;
	return sqrt(xLen*xLen + yLen* yLen);
}

double utilitaireProduitVectoriel(VECTOR v, VECTOR w)
{
	return v.normeX * w.normeY - v.normeY * w.normeX;
}

double utilitaireProduitScalaire(VECTOR v, VECTOR w)
{
	return v.normeX * w.normeX + v.normeY * w.normeY; 
}

int utilitaireParalelisme(VECTOR v1, VECTOR v2)
{
	return 0;
}

int utilitaireIntersection(VECTOR v1, VECTOR v2)
{
	return 0;
}

POINT utilitaireIntersectionPt(VECTOR v1, VECTOR v2)
{
	POINT a;
	return a;
}	

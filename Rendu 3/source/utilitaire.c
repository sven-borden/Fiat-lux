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
#include "constantes.h"
#include "utilitaire.h"

#define OUI	1
#define NON	0

double determinant(VECTOR);

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

POINT * utilitaireIntersection(VECTOR v1, VECTOR v2)
{
	POINT intersection;
	int interX = 0, interY = 0;
	
	POINT *pInter = NULL;
	
	double v1x = v1.ptFin.x - v1.ptDeb.x;
	double v1y = v1.ptFin.y - v1.ptDeb.y;
	double v2x = v2.ptFin.x - v2.ptDeb.x;
	double v2y = v2.ptFin.y - v2.ptDeb.y;

	if(!fabs((v1x*v2y-v1y*v2x) <= EPSIL_PARAL))
	{
		intersection.x = (v2x * determinant(v1)
					-v1x*determinant(v2))
					/(v1x*v2y-v1y*v2x);
		intersection.y = (v1y/v1x)*intersection.x 
					+ (determinant(v1)/v1x);
		//ici c'est du test
	
		if(v1.ptDeb.x-EPSIL_CONTACT <= intersection.x &&
			intersection.x <= v1.ptFin.x+EPSIL_CONTACT)
			interX = 1;
	
		if(v1.ptDeb.x+EPSIL_CONTACT >= intersection.x &&
			intersection.x >= v1.ptFin.x-EPSIL_CONTACT)
			interX = 1;

		if(v2.ptDeb.x-EPSIL_CONTACT <= intersection.x && 
			intersection.x <= v2.ptFin.x+EPSIL_CONTACT)
			interY = 1;

		if(v2.ptDeb.x+EPSIL_CONTACT >= intersection.x &&
			intersection.x >= v2.ptFin.x-EPSIL_CONTACT)
			interY = 1;
		

		if(interX == 1 && interY == 1)
			pInter = &intersection;	
	
	}
	return pInter;
}

double determinant(VECTOR a)
{
	return a.ptFin.x*a.ptDeb.y - a.ptFin.y*a.ptDeb.x;
}

void utilitaireSwap(double *a, double *b)
{
	double c = *a;
	*a = *b;
	*b = c;
	return ;
}	

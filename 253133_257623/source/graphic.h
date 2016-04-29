/*
	Fichier:	graphic.h
	Auteurs:	Alix Nepveux & Sven Borden
	Date:		20 avril 2016
	Version:	1.1
	Description:	Module qui permet de faire du Dessin OpenGl
*/

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "utilitaire.h"

/*Dessine un photon*/
void graphicDrawPhoton(POINT, double);
/*Dessine un absorbeur*/
void graphicDrawAbsorbeur(int, POINT[]);
/*Dessine un reflecteur*/
void graphicDrawReflecteur(POINT, POINT);
/*Dessine un projecteur*/
void graphicDrawProjecteur(POINT, double);
/*Dessine le rectagle de zoom en live*/
void graphicDrawZoom(double, double, double, double);
#endif

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

#define WHITE		1
#define GREEN		2
#define RED		3
#define	BLUE		4
#define VIOLET		5
#define TURQUOISE	6
#define YELLOW		7
/*Dessine un photon*/
void graphicDrawPhoton(POINT, double);
/*Dessine un absorbeur*/
void graphicDrawAbsorbeur(int, POINT[], int8_t);
/*Dessine un reflecteur*/
void graphicDrawReflecteur(POINT, POINT, int8_t);
/*Dessine un projecteur*/
void graphicDrawProjecteur(POINT, double, int8_t);
/*Dessine le rectagle de zoom en live*/
void graphicDrawZoom(double, double, double, double);
#endif

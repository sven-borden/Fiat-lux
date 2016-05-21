/*
	Fichier:	graphic.c
	Auteurs:	Alix Nepveux & Sven Borden
	Date:		20 avril 2016
	Version:	1.1
	Description:	Module qui dessine les entités
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "constantes.h"
#include "utilitaire.h"
#include "graphic.h"

#define PISURDEUX 	M_PI/2
#define BASIC_LINE	0.7
#define MEDIUM_LINE	1.
#define FAT_LINE	2.
#define HUGE_LINE	3.
#define SELECT		1
static float	white[]	= {1.,1.,1.},
				green[]	= {0.,1.,0.},
				red[]	= {1.,0.,0.},
				blue[]	= {0.,0.,1.},
				violet[]= {1.,0.,1.},
				turquoise[]={0.,1.,1.},
				yellow[]= {1.,0.66,0.005};

void graphicColor(short color)
{
	switch(color)
	{	
		case WHITE:	glColor3fv(white);
			break;
		case GREEN:	glColor3fv(green);
			break;
		case RED:	glColor3fv(red);
			break;
		case BLUE:	glColor3fv(blue);
			break;
		case VIOLET: glColor3fv(violet);
			break;
		case TURQUOISE: glColor3fv(turquoise);
			break;
		case YELLOW: glColor3fv(yellow);
			break;
	}
}

void graphicDrawPhoton(POINT pt, double alpha)
{
	int i = 0;
	const double conv = M_PI * 2;
	double angle = 0;
	const int sides = 16;
	double diam = EPSIL_PROJ/2;
	
	glLineWidth(BASIC_LINE);
	graphicColor(VIOLET);
	glBegin(GL_LINE_LOOP);

	for(; i < sides; i++)
	{
		angle = i * conv / sides;
		glVertex2f(pt.x + (cos(angle)*diam), pt.y + (sin(angle)*diam));
	}
	glEnd();
	
	graphicColor(WHITE);
	return ;
}

void graphicDrawAbsorbeur(int nb, POINT tab[MAX_PT], int8_t selected)
{
	int i = 0;
	glLineWidth(FAT_LINE);
	if(selected == SELECT)
		graphicColor(YELLOW);
	else
		graphicColor(BLUE);
	glBegin(GL_LINE_STRIP);
	
	for(;i < nb; i++)
		glVertex2f(tab[i].x, tab[i].y);
	glEnd();
	
	graphicColor(WHITE);
	return ;	
}

void graphicDrawReflecteur(POINT a, POINT b, int8_t selected)
{
	glLineWidth(MEDIUM_LINE);
	if(selected == SELECT)
		graphicColor(YELLOW);
	else
		graphicColor(RED);
	glBegin(GL_LINES);
	
	glVertex2d(a.x, a.y);
	glVertex2d(b.x, b.y);
	
	glEnd();
	graphicColor(WHITE);
	return ;
}

void graphicDrawProjecteur(POINT a, double alpha, int8_t selected)
{
	glLineWidth(MEDIUM_LINE);
	if(selected == SELECT)
		graphicColor(YELLOW);
	else
		graphicColor(GREEN);

	POINT b;
	b.x = (cos(alpha + PISURDEUX)*(NBPH-1)*EPSIL_PROJ) + a.x;
	b.y = (sin(alpha + PISURDEUX)*(NBPH-1)*EPSIL_PROJ) + a.y;
	
	glBegin(GL_LINES);
	
	glVertex2d(a.x, a.y);
	glVertex2d(b.x, b.y);

	glEnd();

	graphicColor(WHITE);
	return ;
}

void graphicDrawZoom(double x1, double x2, double y1, double y2)
{
	if(x1 > x2)
		utilitaireSwap(&x1, &x2);
	if(y1 > y2)
		utilitaireSwap(&y1, &y2);
	glLineWidth(HUGE_LINE);
	glColor3fv(turquoise);
	glBegin(GL_LINE_LOOP);

	glVertex2d(x1, y1);
	glVertex2d(x2, y1);
	glVertex2d(x2, y2);
	glVertex2d(x1, y2);

	glEnd();
	glColor3fv(white);
	
}

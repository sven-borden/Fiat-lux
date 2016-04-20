#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "constantes.h"
#include "utilitaire.h"
#include "graphic.h"

#define PISURDEUX M_PI/2

static float 	//black[]	= {0.,0.,0.},
				white[]	= {1.,1.,1.},
				green[]	= {0.,1.,0.},
				red[]	= {1.,0.,0.},
				//yellow[]= {1.,1.,0.},
				blue[]	= {0.,0.,1.},
				violet[]= {1.,0.,1.};

void graphicDrawPhoton(POINT pt, double alpha)
{
	int i = 0;
	const double conv = M_PI * 2;
	double angle = 0;
	const int SIDES = 50;
	double diam = EPSIL_PROJ/2;
	
	glLineWidth(0.7);
	glColor3fv(blue);
	glBegin(GL_LINE_LOOP);

	for(; i < SIDES; i++)
	{
		angle = i * conv / SIDES;
		glVertex2f(pt.x + (cos(angle)*diam), pt.y + (sin(angle)*diam));
	}
	glEnd();
	
	glColor3fv(white);
	return ;
}

void graphicDrawAbsorbeur(int nb, POINT tab[MAX_PT])
{
	int i = 0;
	glLineWidth(0.7);
	glColor3fv(green);	
	glBegin(GL_LINE);
	
	for(;i < nb; i++)
		glVertex2f(tab[i].x, tab[i].y);
	glEnd();
	
	glColor3fv(white);
	return ;	
}

void graphicDrawReflecteur(POINT a, POINT b)
{
	glLineWidth(1.);
	glColor3fv(red);
	glBegin(GL_LINE);
	
	glVertex2d(a.x, a.y);
	glVertex2d(b.x, b.y);
	
	glEnd();
	glColor3fv(blue);
	return ;
}

void graphicDrawProjecteur(POINT a, double alpha)
{
	glLineWidth(1.);
	glColor3fv(violet);

	POINT b;
	b.x = (cos(alpha + PISURDEUX)*(NBPH-1)*EPSIL_PROJ) + a.x + 1.;
	b.y = (sin(alpha + PISURDEUX)*(NBPH-1)*EPSIL_PROJ) + a.y + 1.;
	
	glBegin(GL_LINE);
	
	glVertex2d(a.x, a.y);
	glVertex2d(b.x, b.y);

	glEnd();

	glColor3fv(white);
	return ;
}

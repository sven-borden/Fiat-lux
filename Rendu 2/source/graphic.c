#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glu.h>
#include "constantes.h"
#include "utilitaire.h"
#include "graphic.h"

static float 	black[]	= {0.,0.,0.},
				white[]	= {1.,1.,1.},
				green[]	= {0.,1.,0.},
				red[]	= {1.,0.,0.},
				yellow[]= {1.,1.,0.},
				blue[]	= {0.,0.,1.};

void graphicDrawPhoton(POINT pt, double alpha)
{
	int i = 0;
	const double conv = M_PI/180;
	double angle = 0;
	const int SIDES = 50, diam = EPSIL_PROJ/2;
	
	glColor3f(blue);
	glBegin(GL_LINE_LOOP);

	for(; i < SIDES; i++)
	{
		angle = i * conv;
		glVertex2f(cos(angle)*diam, sin(angle)*diam);
	}
	glEnd();
	
	glColor3f(white);
	return ;
}

void graphicDrawAbsorbeur(int nb, POINT tab[MAX_PT])
{	
	int i = 0;
	glBegin(GL_LINE);
	
	for(;i < nb; i++)
		glVertex2f(tab[i].x, tab[i].y);
	glEnd();
	
	return ;	
}

void graphicDrawReflecteur(POINT a, POINT b)
{
	glBegin(GL_LINE);
	
	glVertex2d(a.x, a.y);
	glVertex2d(b.x, b.y);
	
	glEnd();
	return ;
}

void graphicDrawProjecteur(POINT a, double alpha)
{
	/*TODO*/
	return ;
}

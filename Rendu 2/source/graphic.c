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
				violet[]= {1.,0.,1.},
				turquoise[]={0.,1.,1.};

void graphicDrawPhoton(POINT pt, double alpha)
{
	int i = 0;
	const double conv = M_PI * 2;
	double angle = 0;
	const int SIDES = 15;
	double diam = EPSIL_PROJ/2;
	
	glLineWidth(0.7);
	glColor3fv(violet);
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
	glColor3fv(blue);	
	glBegin(GL_LINES);
	
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
	glBegin(GL_LINES);
	
	glVertex2d(a.x, a.y);
	glVertex2d(b.x, b.y);
	
	glEnd();
	glColor3fv(blue);
	return ;
}

void graphicDrawProjecteur(POINT a, double alpha)
{
	glLineWidth(1.);
	glColor3fv(green);

	POINT b;
	b.x = (cos(alpha + PISURDEUX)*(NBPH-1)*EPSIL_PROJ) + a.x;
	b.y = (sin(alpha + PISURDEUX)*(NBPH-1)*EPSIL_PROJ) + a.y;
	
	glBegin(GL_LINES);
	
	glVertex2d(a.x, a.y);
	glVertex2d(b.x, b.y);

	glEnd();

	glColor3fv(white);
	return ;
}

void graphicDrawZoom(double x1, double x2, double y1, double y2)
{
	if(x1 > x2)
		utilitaireSwap(&x1, &x2);
	if(y1 > y2)
		utilitaireSwap(&y1, &y2);
	printf("POINTS \n%lf\t%lf\n%lf\t%lf\n", x1, y1, x2, y2);
	glLineWidth(3.);
	glColor3fv(turquoise);
	glBegin(GL_LINE_LOOP);

	glVertex2d(x1, y1);
	glVertex2d(x2, y1);
	glVertex2d(x2, y2);
	glVertex2d(x1, y2);

	glEnd();
	glColor3fv(white);
	
}

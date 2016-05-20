/*
    Fichier:    projecteur.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      20 avril 2016
    Version:    1.1
    Description:Module projecteur qui gere la structure
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "absorbeur.h"
#include "constantes.h"
#include "error.h"
#include "graphic.h"
#include "photon.h"
#include "utilitaire.h"
#include "projecteur.h"

#define OK      	1
#define NO      	0
#define NB_ELEM 	3
#define PROJ_VAL	1

typedef struct Projecteur PROJECTEUR;

struct Projecteur
{
	POINT pos;
	double alpha;
	unsigned int id;
	PROJECTEUR * next;
};

static int n = 0;
static unsigned int lastId = 0;
static PROJECTEUR * list;

int projecteurSet(char line[MAX_LINE])
{
	POINT pt;
	double  alpha = 0;
	if(sscanf(line, "%lf %lf %lf", &pt.x, &pt.y, &alpha) != NB_ELEM)
	{
		error_lecture_elements(ERR_PROJECTEUR, ERR_PAS_ASSEZ);
		return NO;
	}

	addProjecteur(pt, alpha);
	return OK;
}

int addProjecteur(POINT _pt, double _alpha)
{
	/*Crée un nouveau projecteur*/
	PROJECTEUR *p = (PROJECTEUR *) malloc(sizeof(PROJECTEUR));
	if(p!= NULL)
	{
		p->pos.x = _pt.x;
		p->pos.y = _pt.y;
		p->alpha = _alpha;
		p->id 	 = lastId;
		if(list != NULL)
			p->next = list;
		else
			p->next = NULL;
		list = p;
		lastId++;
		n++;
		
	}	
	else
	{
		free(p);
		p = NULL;
	}
	return (p != NULL);//retourne 1 (vrai) si est différent de NULL
}

int delProjecteur(int _id)
{
	/*TODO*/
	n--;
	return OK;
}

void drawProj(void)
{
	PROJECTEUR *p = list;
	while(p != NULL)
	{
		graphicDrawProjecteur(p->pos, p->alpha);
		p = p->next;
	}
}

void writeProjecteur(FILE * file)
{
	PROJECTEUR *p = list;
	fprintf(file, "#projecteur\n%d\n", n);
	while(p != NULL)
	{
		fprintf(file, "%lf %lf %lf\n", p->pos.x, p->pos.y, p->alpha);
		p = p->next;
	}
	fprintf(file, "FIN_LISTE\n\n");
}

void printListProjecteur(void)
{
	PROJECTEUR *p = list;
	int i = 1;
	while(p != NULL)
	{
		printf("Projecteur %d\tx = %lf\ta.y = %lf\talpha = %lf\n",
			i, p->pos.x, p->pos.y, p->alpha);
		p = p->next;
		i++;
	}
	return ;
}

int projecteurExt(VECTOR v, int idV)
{
	PROJECTEUR * p = list;
	VECTOR vp;
	POINT *inter;
	while(p != NULL)
	{
		vp.ptDeb.x = p->pos.x;
		vp.ptDeb.y = p->pos.y;
		vp.ptFin.x = (cos(p->alpha+M_PI/2)*(NBPH-1)*EPSIL_PROJ) + p->pos.x;
		vp.ptFin.y = (sin(p->alpha+M_PI/2)*(NBPH-1)*EPSIL_PROJ) + p->pos.y;

		inter = utilitaireIntersection(v, vp);
		if(inter != NULL)
		{
			error_lecture_intersection(ERR_PROJECTEUR, p->id, ERR_REFLECTEUR, idV);
			return NO;
		}
		p = p->next;
	}
	return OK;
}

int projInterAbs(void)
{
	PROJECTEUR *p = list;
	VECTOR v;
	while(p != NULL)
	{
		v.ptDeb.x = p->pos.x;
		v.ptDeb.y = p->pos.y;
		v.ptFin.x = (cos(p->alpha+M_PI/2)*(NBPH-1)*EPSIL_PROJ) + p->pos.x;
		v.ptFin.y = (sin(p->alpha+M_PI/2)*(NBPH-1)*EPSIL_PROJ) + p->pos.y;

		if(absorbeurExt(v, p->id, PROJ_VAL) == NO)
			return NO;
		p = p->next;
	}	
	return OK;
}

void delListProjecteur(void)
{
	while(list)
	{
		PROJECTEUR *p = list;
		list = p->next;
		free(p);
	}
	n = 0;
	return ;
}

int nbProj(void) { return n; }

void updateProjecteur()
{
	PROJECTEUR *p = list;
	int i = 0;
	double portionX = 0; double portionY = 0;
	POINT pt;
	while(p)
	{
		/*crées les NBPH sur chaque proj*/
		portionX = (cos(p->alpha+M_PI/2)*(NBPH)*EPSIL_PROJ)/NBPH;
		portionY = (sin(p->alpha+M_PI/2)*(NBPH)*EPSIL_PROJ)/NBPH;
		for(i = 0; i < NBPH; i++)
		{
			pt.x = portionX*i + p->pos.x;
			pt.y = portionY*i + p->pos.y;
			addPhoton(pt, p->alpha);
		}	
		p = p->next;
	}
}

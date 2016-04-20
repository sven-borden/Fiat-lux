/*
    Fichier:    reflecteur.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      16 mars 2016
    Version:    0.9
    Description:Module reflecteur qui gere la structure 
*/

#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "error.h"
#include "graphic.h"
#include "utilitaire.h"
#include "reflecteur.h"

#define OK      0
#define NO      1
#define NB_ELEM 4

typedef struct Reflecteur REFLECTEUR;

struct Reflecteur
{
	POINT a;
	POINT b;
	REFLECTEUR * next;
};

static int n = 0;
static REFLECTEUR * list;

static int reflecteurDistanceRequise(POINT, POINT);

int reflecteurSet(char line[MAX_LINE])
{
	POINT _a, _b;
	if(sscanf(line, "%lf %lf %lf %lf", 
		&_a.x, &_a.y, &_b.x, &_b.y) != NB_ELEM)
	{
		error_lecture_elements(ERR_REFLECTEUR, ERR_PAS_ASSEZ);
		return NO;
	}
    
	if(!reflecteurDistanceRequise(_a, _b))
	{
		error_lecture_point_trop_proche(ERR_REFLECTEUR, n);
		return NO;
	}

	addReflecteur(_a, _b);
	return OK;
}

int addReflecteur(POINT _ptA, POINT _ptB)
{
	/*Crée un nouveau reflecteur*/
	REFLECTEUR *r = (REFLECTEUR *) malloc(sizeof(REFLECTEUR));
	if(r != NULL)
	{
		r->a.x = _ptA.x;
		r->a.y = _ptA.y;
		r->b.x = _ptB.x;
		r->b.y = _ptB.y;
		if(list != NULL)
			r->next = list;
		else
			r->next = NULL;
		list = r;
		n++;
	}
	else
	{
		free(r);
		r = NULL;
	}
	return (r != NULL); //retourne 1 (vrai) si est different de NULL
}

int delReflecteur(int _id)
{
	/*TODO*/
	n--;
	return OK;
}

void writeReflecteur(FILE *file)
{
	REFLECTEUR *r = list;
	fprintf(file, "#reflecteur\n%d\n", n);
	while(r != NULL)
	{
		fprintf(file, "%lf %lf %lf %lf\n", r->a.x, r->a.y, r->b.x, r->b.y);
		r = r->next;
	}
	fprintf(file, "FIN_LISTE\n\n");
}

void drawRefl(void)
{
	REFLECTEUR *r = list;
	while(r != NULL)
	{
		graphicDrawReflecteur(r->a, r->b);
		r = r->next;
	}
}	

void printListReflecteur(void)
{
	REFLECTEUR *r = list;
	int i = 1;
	while(r != NULL)
	{
		printf("Reflecteur %d\ta.X = %lf\ta.Y = %lf\tb.X = %lf\tb.Y = %lf\n",
			i, r->a.x, r->a.y, r->b.x, r->b.y);
		r = r->next;
		i++;
	}	
	return ;
}

void delListReflecteur(void)
{
	while(list)
	{
		REFLECTEUR *r = list;
		list = r->next;
		free(r);
	}
	n = 0;
	return ;
}

static int reflecteurDistanceRequise(POINT _a, POINT _b)
{
	if(utilitaireDistance2Points(_a, _b) < EPSIL_CREATION)
		return OK;
	else
		return NO;
}

int nbRefl(void) { return n; }

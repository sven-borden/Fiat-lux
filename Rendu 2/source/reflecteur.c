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
	struct REFLECTEUR *next;
};

typedef REFLECTEUR *LIST_R; /* type de liste de reflecteur*/

static int n = 0;
static LIST_R list = NULL;

int reflecteurSet(char[]);
int addReflecteur(POINT, POINT);
int delReflecteur(int);
void printListReflecteur(void);
void delListReflecteur(void);
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

	addPhoton(_a, _b);
	return OK;
}

int addReflecteur(POINT _ptA, POINT_ptB)
{
	/*Crée un nouveau reflecteur*/
	REFLECTEUR *r = (REFLECTEUR *) malloc(sizeof(REFLECTEUR));
	if(p != NULL)
	{
		/*Alloue la mémoire pour le Reflecteur*/
		r->a.x = malloc(sizeof(double));
		r->a.y = malloc(sizeof(double));
		r->b.x = malloc(sizeof(double));
		r->b.y = malloc(sizeof(double));
		r->next = *list;
		n++;
	}
	else
	{
		free(p);
		p = NULL;
	}
	return (p != NULL); //retourne 1 (vrai) si est different de NULL
}

int delReflecteur(int _id)
{
	/*TODO*/
	n--;
	return OK;
}

void printListReflecteur(void)
{
	REFLECTEUR *r = *list;
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
	while(*list)
	{
		REFLECTEUR *r = *list;
		*list = r->next;
		free(r->a.x);
		free(r->a.y);
		free(r->b.x);
		free(r->b.y);
		free(p);
	}
	return ;
}

static int reflecteurDistanceRequise(POINT _a, POINT _b)
{
	if(utilitaireDistance2Points(_a, _b) < EPSIL_CREATION)
		return OK;
	else
		return NO;
}

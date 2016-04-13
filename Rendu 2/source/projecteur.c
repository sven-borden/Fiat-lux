/*
    Fichier:    projecteur.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      16 mars 2016
    Version:    0.9
    Description:Module projecteur qui gere la structure
*/

#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "error.h"
#include "utilitaire.h"
#include "projecteur.h"

#define OK      0
#define NO      1
#define NB_ELEM 3

typedef struct Projecteur PROJECTEUR;

struct Projecteur
{
	POINT pos;
	double alpha;
	PROJECTEUR * next;
};

static int n = 0;
static PROJECTEUR * list;

int projecteurSet(char[]);
int addProjecteur(POINT, double);
int delProjecteur(int);
void printListProjecteur(void);
void delListProjecteur(void);

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
		p->next = list;
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

void delListProjecteur(void)
{
	while(list)
	{
		PROJECTEUR *p = list;
		list = p->next;
		free(p);
	}
	return ;
}

/*
    Fichier:    photon.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      16 mars 2016
    Version:    0.9
    Description:Module photon qui gere la structure photon
*/

#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "error.h"
#include "utilitaire.h"
#include "photon.h"

#define OK      0
#define NO      1
#define NB_ELEM 3

typedef struct Photon PHOTON;

struct Photon
{
	POINT pos;	/*position du photon*/
	double alpha;	/*angle du photon*/
	struct PHOTON *next;	/*Pointeur sur le suivant*/
};

typedef PHOTON *LIST_P; /* type de liste de photons*/

static int n = 0;
static LIST_P list = NULL;

int photonSet(char[]);
int addPhoton(POINT, double);
int delPhoton(int);
void printListPhoton(void);
void delListPhoton(void);

int photonSet(char line[MAX_LINE])
{
	POINT _pos; double _alpha;
	if(sscanf(line, "%lf %lf %lf", 
		&_pos.x, &_pos.y, &_alpha) != NB_ELEM)
	{
		error_lecture_elements(ERR_PHOTON, ERR_PAS_ASSEZ);
		return NO;
	}

	addPhoton(_pos, _alpha);
	return OK;
}

int addPhoton(POINT _pt, double _alpha)
{
	/*Crée un nouveau photon*/
	PHOTON *p = (PHOTON *) malloc(sizeof(PHOTON));
	if(p != NULL)
	{
		/*Alloue la mémoire pour le photon*/
		p->pos.x = malloc(sizeof(double));
		p->pos.y = malloc(sizeof(double));
		p->alpha = malloc(sizeof(double));

		if(p->pos.x && p->pos.y && p->alpha)
		{	
			/*copie dans le photon*/
			p->pos.x = _pt.x;
			p->pos.y = _pt.y;
			p->pos.alpha = _alpha;
			p->next = *list;
			n++;
		}
		else
		{
			free(p);
			p = NULL;
		}
	}
	return (p != NULL);//retourne 1 (vrai) si est différent de NULL
} 

int delPhoton(int _id);
{
	/*TODO*/
	n--;
	return OK;
}

void printListPhoton(void)
{
	PHOTON *p = *list;
	int i = 1;
	while(p)
	{
		printf("Photon %d\tX = %lf\t Y = %lf\tAlpha = %lf\n", 
			i, p->pos.x, p->pos.y, p->alpha);
		p = p->next;
		i++;
	}
	return ;
}

void delListPhoton(void)
{
	while(*list)
	{
		PHOTON *p = *list;
		*list = p->next;
		free(p->pos.x);
		free(p->pos.y);
		free(p->alpha);
		free(p);
	}
	return ;
}

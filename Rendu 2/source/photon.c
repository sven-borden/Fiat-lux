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
#include "graphic.h"
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
	PHOTON * next;	/*Pointeur sur le suivant*/
};

static int n = 0;
static PHOTON * list = NULL;

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

int delPhoton(int _id)
{
	/*TODO*/
	n--;
	return OK;
}

void writePhoton(FILE * file)
{
	PHOTON *p = list;
	fprintf(file, "#photon\n%d\n", n);
	while(p != NULL)
	{
		fprintf(file, "%lf %lf %lf\n", p->pos.x, p->pos.y, p->alpha);
		p = p->next;
	}
	fprintf(file, "FIN_LISTE\n\n");
}

void drawPhot(void)
{
	PHOTON *p = list;
	while(p != NULL)
	{
		graphicDrawPhoton(p->pos, p->alpha);
		p = p->next;
	}
}

void printListPhoton(void)
{
	PHOTON *p = list;
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
	while(list)
	{
		PHOTON *p = list;
		list = p->next;
		free(p);
	}
	return ;
}

int nbPhot(void) { return n; }

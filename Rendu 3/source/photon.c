/*
    Fichier:    photon.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      20 avril 2016
    Version:    1.1
    Description:Module photon qui gere la structure photon
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "absorbeur.h"
#include "constantes.h"
#include "error.h"
#include "graphic.h"
#include "reflecteur.h"
#include "utilitaire.h"
#include "photon.h"

#define OK      1
#define NO     	0
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
		if(list != NULL)
			p->next = list;
		else
			p->next = NULL;
		list = p;
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

void delOutside(double xmin, double xmax, double ymin, double ymax)
{
	PHOTON *p = list, *pOld = list, *pNext = list->next;
	while(p)
	{
		if(p->pos.x < xmin || p->pos.x > xmax
			||p->pos.y < ymin || p->pos.y > ymax)
			;//suppression(&p);
		p = p->next;
	}
}

void delListPhoton(void)
{
	n = 0;
	while(list)
	{
		PHOTON *p = list;
		list = p->next;
		free(p);
	}
	return ;
}

int nbPhot(void) { return n; }

void reflection(VECTOR v)
{
	
}

void suppression(PHOTON ** pOld, PHOTON ** p)
{
	return;
	if(!*p || !*pOld)
		return;
	/*si entete*/
	if(*p == list)
	{
		list = list->next;
		free(*p);
		*p = list;
		*pOld = *p;
		return;
	}

	/*reste*/
	(*pOld)->next = (*p)->next;
	free(*p);
	*p = *pOld;
	return;
}

void check(PHOTON * pOld, PHOTON *p, VECTOR v)
{
	POINT *prefl, *pabso;
	POINT refl, abso;
	prefl = reflProche(v);
	pabso = absoProche(v);
	if(prefl == NULL && pabso == NULL)//pas d'intersection
	{
		p->pos.x = v.ptFin.x;
		p->pos.y = v.ptFin.y;
		return;
	}
	if(prefl == NULL)//seulement un abso
	{
		//supprime
		suppression(&pOld, &p);
		return;
	}
	if(pabso == NULL)//seulement refl
	{
		printf("reflection\n");
		reflection(v);
		return;
	}
	//les deux
	refl.x = prefl->x;
	refl.y = prefl->y;
	abso.x = pabso->x;
	abso.y = pabso->y;
	
	double dRefl = fabs(utilitaireDistance2Points(refl, v.ptDeb));
	double dAbso = fabs(utilitaireDistance2Points(abso, v.ptDeb));

	dRefl < dAbso ? reflection(v) : suppression(&pOld, &p);
	
	return;
}

void updatePhoton()
{
	printf("%s\n", __func__);
	PHOTON *p = list, *pOld = list;
	double futureX = 0;
	double futureY = 0;/*les deux futures positions*/
	VECTOR v;
	while(p && pOld)
	{
		futureX = p->pos.x + cos(p->alpha)*DELTA_T*VPHOT;
		futureY = p->pos.y + sin(p->alpha)*DELTA_T*VPHOT;
		v.ptDeb.x = p->pos.x;
		v.ptDeb.y = p->pos.y;
		v.ptFin.x = futureX;
		v.ptFin.y = futureY;
		check(pOld, p, v);

		pOld = p;
		p = p->next;
	}
}

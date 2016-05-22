/*
    Fichier:    reflecteur.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      20 avril 2016
    Version:    1.1
    Description:Module reflecteur qui gere la structure 
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "absorbeur.h"
#include "constantes.h"
#include "error.h"
#include "graphic.h"
#include "projecteur.h"
#include "utilitaire.h"
#include "reflecteur.h"

#define OK      	1
#define NO      	0
#define NB_ELEM 	4
#define REFL_VAL	0
#define SELECT		1
#define UNSELECT	0
#define NONE		65353

typedef struct Reflecteur REFLECTEUR;

struct Reflecteur
{
	POINT a;
	POINT b;
	unsigned int id;
	REFLECTEUR * next;
};

static int n = 0;
static unsigned int lastReflectionId = NONE;
static unsigned int lastId = 0;
static unsigned int idSelected = NONE;
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
		r->id  = lastId;
		if(list != NULL)
			r->next = list;
		else
			r->next = NULL;
		list = r;
		lastId++;
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
	REFLECTEUR *r = list;

	if(r)
	{
		if(r->id == _id)
		{
			list = list->next;
			free(r);
		}	
		else
		{
			REFLECTEUR *prec = r;
			while(prec->next && prec->next->id != _id)
				prec = prec->next;
			if(prec->next)
			{
				REFLECTEUR * del = prec->next;
				prec->next = prec->next->next;
				free(del);
				del = NULL;
			}
		}
	}
	n--;
	return OK;
}

void delReflTete(void)
{
	delReflecteur(list->id);
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
		if(r->id == idSelected)
			graphicDrawReflecteur(r->a, r->b, SELECT);
		else
			graphicDrawReflecteur(r->a, r->b, UNSELECT);
		r = r->next;
	}
}	

void selectReflecteur(double x, double y)
{
	REFLECTEUR *r = list;
	POINT pt;	pt.x = x;	pt.y = y;
	unsigned int tmpId = 0;
	double norme, normeMin = NONE;
	while(r)
	{
		norme = utilitaireDistance2Points(r->a, pt);
		if(norme < normeMin)
		{
			normeMin = norme;
			tmpId = r->id;
		}
		norme = utilitaireDistance2Points(r->b, pt);
		if(norme < normeMin)
		{
			normeMin = norme;
			tmpId = r->id;
		}
		r = r->next;
	}	
	idSelected = tmpId;
}

void unselectRefl(void){	idSelected = NONE;	}

void reflDelSelect(void)
{
	delReflecteur(idSelected);
	idSelected = NONE;
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
		return NO;
	else
		return OK;
}

int interReflecteur(void)
{
	REFLECTEUR *r1 = list;
	REFLECTEUR *r2 = list;
	VECTOR v1, v2;
	POINT * pt = NULL;
	while(r1 != NULL)
	{
		v1.ptDeb.x = r1->a.x;
		v1.ptDeb.y = r1->a.y;
		v1.ptFin.x = r1->b.x;
		v1.ptFin.y = r1->b.y;
		r2 = r1->next;
		while(r2 != NULL)
		{
			v2.ptDeb.x = r2->a.x;
			v2.ptDeb.y = r2->a.y;
			v2.ptFin.x = r2->b.x;
			v2.ptFin.y = r2->b.y;
			pt = utilitaireIntersection(v1, v2);
			if(pt != NULL)
			{
				error_lecture_intersection(ERR_REFLECTEUR, r1->id,
					ERR_REFLECTEUR, r2->id);
				return NO;
			}
			r2 = r2->next;
		}
		r1 = r1->next;
	}
	return OK;
}

int reflInterAbs(void)
{
	REFLECTEUR * r = list;
	VECTOR a;
	while(r != NULL)
	{
		a.ptDeb.x = r->a.x;
		a.ptDeb.y = r->a.y;
		a.ptFin.x = r->b.x;
		a.ptFin.y = r->b.y;
		if(absorbeurExt(a, r->id, REFL_VAL) == NO)
			return NO;
		r = r->next;
	}
	return OK;
}

POINT * reflProche(VECTOR v)
{
	REFLECTEUR *r = list;
	VECTOR vR; POINT pt;
	double normeMin = 100; double normeTmp;
	normeTmp = normeMin;
	POINT * point = NULL;
	POINT * pointProche = NULL;
	while(r)
	{
		vR.ptDeb.x = r->a.x;
		vR.ptDeb.y = r->a.y;
		vR.ptFin.x = r->b.x;
		vR.ptFin.y = r->b.y;

		point = utilitaireIntersection(vR, v);
		if(point != NULL)
		{
			pt.x = point->x;
			pt.y = point->y;
			normeTmp = fabs(utilitaireDistance2Points(pt, v.ptDeb));
			if(normeTmp < normeMin)
			{
				normeMin = normeTmp;
				pointProche = point;
				lastReflectionId = r->id;	
			}
		}
		r = r->next;
	}
	return pointProche;
}
int getLastId(void) { return lastReflectionId; }
void resetLastReflect(void){ lastReflectionId = NONE; }
VECTOR getReflecteur(int _id)
{
	REFLECTEUR *r = list;
	while(r)
	{		
		if(r->id == _id)
		{
			VECTOR v;	
			v.ptDeb = r->a;
			v.ptFin = r->b;
			return v;
		}
		r = r->next;
	}
}

int reflInterProj(void)
{
	REFLECTEUR *r = list;
	VECTOR a;
	int id = n-1;
	while(r != NULL)
	{
		a.ptDeb.x = r->a.x;
		a.ptDeb.y = r->a.y;
		a.ptFin.x = r->b.x;
		a.ptFin.y = r->b.y;

		if(projecteurExt(a, id) == NO)
			return NO;
		r = r->next;
		id--;
	}
	return OK;
}

int nbRefl(void) { return n; }

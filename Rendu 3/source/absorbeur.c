/*
    Fichier:    absorbeur.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      22 mai 2016
    Version:    1.2
    Description:Module absorbeur qui gere cette structure 
*/

#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "error.h"
#include "graphic.h"
#include "graphic.h" 
#include "utilitaire.h"
#include "absorbeur.h"

#define OK      	1
#define NO      	0
#define MIN_PT  	2
#define PROJ		1
#define REFL		0
#define PHOT		2
#define SELECT		1
#define UNSELECT 	0
#define NONE		65535
typedef struct Absorbeur ABSORBEUR;

struct Absorbeur
{
	int nbPt;
	unsigned int id;
	POINT tabPt[MAX_PT];
	ABSORBEUR * next;
};


static int absorbeurDistanceRequise(POINT, POINT);
static unsigned int lastId = 0;
static int n = 0;
static unsigned int idSelected = NONE;
static ABSORBEUR * list;

int absorbeurSet(char line[MAX_LINE])
{
	int _nbPt, j = 0, i = 0;
	char* start = line; char * end = NULL;
	POINT _points[MAX_PT];

	//lecture
	_nbPt = (int)strtod(line, &end);
	if(_nbPt < MIN_PT || _nbPt > MAX_PT)
	{
		error_lect_nb_points_absorbeur();
		return NO;
	}
	start = end;
    
	for(j = 0; j < _nbPt; j++)
	{
		_points[j].x = strtod(start, &end);
		if(start == end)
		{
			error_lecture_elements(ERR_ABSORBEUR, ERR_PAS_ASSEZ);
			return NO;
		}
		start = end;
		_points[j].y = strtod(start, &end);
		if(start == end)
		{
			error_lecture_elements(ERR_ABSORBEUR, ERR_PAS_ASSEZ);
			return NO;
		}
		start = end;
	}
	//vérifies les points
	for(i = 1;i < _nbPt; i++)
	{
		if(!absorbeurDistanceRequise(
			_points[i], _points[i-1]))
		{
			error_lecture_point_trop_proche(ERR_ABSORBEUR, n);
			return NO;
		}
	}
	addAbsorbeur(_nbPt, _points);
	return OK;
}

int addAbsorbeur(int _nb, POINT tab[_nb])
{
	/*crée une nouveau absorbeur*/
	ABSORBEUR *a = (ABSORBEUR *) malloc(sizeof(ABSORBEUR));
	if(a != NULL)
	{
		int i = 0;
		a->nbPt = _nb;
		a->id = lastId;
		for(; i < _nb; i++)
		{
			a->tabPt[i].x = tab[i].x;
			a->tabPt[i].y = tab[i].y;
		}
		if(list != NULL)
			a->next = list;
		else
			a->next = NULL;
		list = a;
		lastId++;
		n++;
	}
	else
	{
		free(a);
		a = NULL;
	}
	return (a != NULL);
}

int delAbsorbeur(int _id)
{
	ABSORBEUR *a = list;
	
	if(a)
	{
		if(a->id == _id)
		{
			list = list->next;
			free(a);
		}
		else
		{
			ABSORBEUR *prec = a;
			while(prec->next && prec->next->id != _id)
				prec = prec->next;
			if(prec->next)
			{
				ABSORBEUR *del = prec->next;
				prec->next = prec->next->next;
				free(del);
				del = NULL;
			}
		}
	}	
	n--;
	return OK;
}

void delAbsoTete(void)
{
	delAbsorbeur(list->id);
}

void writeAbsorbeur(FILE *file)
{
	int i = 0;
	ABSORBEUR *a = list;
	fprintf(file, "#absorbeur\n%d\n", n);
	while(a != NULL)
	{
		fprintf(file, "%d ", a->nbPt);
		for(i = 0; i < a->nbPt; i++)
			fprintf(file, "%lf %lf",
				a->tabPt[i].x, a->tabPt[i].y);
		fprintf(file, "\n");
		a = a->next;
	}
	fprintf(file, "FIN_LISTE\n\n");
}

int absorbeurExt(VECTOR vE, int idE, int entity)
{
	ABSORBEUR *a = list;
	VECTOR vA;
	int i = 1;
	POINT* pt = NULL;

	while(a != NULL)
	{
		for(i = 0; i < a->nbPt-1; i++)
		{
			vA.ptDeb.x = a->tabPt[i].x;
			vA.ptDeb.y = a->tabPt[i].y;
			vA.ptFin.x = a->tabPt[i+1].x;
			vA.ptFin.y = a->tabPt[i+1].y;

			pt = utilitaireIntersection(vA, vE);
			if(pt != NULL)
			{
				if(entity == PROJ)
				{
					error_lecture_intersection(ERR_PROJECTEUR, idE,
						ERR_ABSORBEUR, a->id);
					return NO;
				}
				if(entity == REFL)
				{
					error_lecture_intersection(ERR_REFLECTEUR, idE,
						ERR_ABSORBEUR, a->id);
					return NO;
					
				}
			}
		}
		a = a->next;
	}
	return OK;
}

POINT * absoProche(VECTOR vE)
{
	ABSORBEUR *a = list;
	VECTOR vA;
	POINT *pt = NULL;
	int i = 0;
	while(a)
	{
		for(i = 0; i < a->nbPt-1; i++)
		{
			vA.ptDeb.x = a->tabPt[i].x;
			vA.ptDeb.y = a->tabPt[i].y;
			vA.ptFin.x = a->tabPt[i+1].x;
			vA.ptFin.y = a->tabPt[i+1].y;

			pt = utilitaireIntersection(vA, vE);

			if(pt != NULL)
				break;
		}
		if(pt != NULL)
			break;
		else
			a = a->next;
	}
	return pt;
}

void drawAbso(void)
{
	ABSORBEUR *a = list;
	while(a != NULL)
	{
		if(a->id == idSelected)
			graphicDrawAbsorbeur(a->nbPt, a->tabPt, SELECT);
		else
			graphicDrawAbsorbeur(a->nbPt, a->tabPt, UNSELECT);
		a = a->next;
	}
}

void selectAbsorbeur(double x, double y)
{
	ABSORBEUR *a = list;
	POINT pt;	pt.x = x;	pt.y = y;
	unsigned int tmpId = 0;
	int i = 0;
	double norme, normeMin = NONE;
	while(a)
	{
		for(i = 0; i < a->nbPt; i++)
		{
			norme = utilitaireDistance2Points(a->tabPt[i], pt);
			if(norme < normeMin)
			{
				normeMin = norme;
				tmpId = a->id;
			}
		}
		a = a->next;
	}
	idSelected = tmpId;
}

void unselectAbso(void){	idSelected = NONE;	}

void absoDelSelect(void)
{
	delAbsorbeur(idSelected);
	idSelected = NONE;
}

void printListAbsorbeur(void)
{
	ABSORBEUR *a = list;
	int i = 0, j = 0;
	while(a != NULL)
	{
		printf("ABSORBEUR %d\n", i);
		for(j = 0; j < a->nbPt; j++)
		{
			printf("\tPT : %d\tx = %lf\ty = %lf\n", 
				j, a->tabPt[j].x, a->tabPt[j].y);
		}
		a = a->next;
		i++;
	}
	return ;
}

void delListAbsorbeur(void)
{
	while(list)
	{
		ABSORBEUR *a = list;
		list = a->next;
		free(a);
	}
	n = 0;
	return ;
}

static int absorbeurDistanceRequise(POINT _a, POINT _b)
{
	if(utilitaireDistance2Points(_a, _b) < EPSIL_CREATION)
		return NO;
	else
		return OK;}

int nbAbso(void) { return n; }

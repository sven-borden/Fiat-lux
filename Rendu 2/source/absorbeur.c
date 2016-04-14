/*
    Fichier:    absorbeur.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      16 mars 2016
    Version:    0.9
    Description:Module absorbeur qui gere cette structure 
*/

#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "error.h"
#include "utilitaire.h"
#include "absorbeur.h"

#define OK      0
#define NO      1
#define MIN_PT  2

typedef struct Absorbeur ABSORBEUR;

struct Absorbeur
{
	int nbPt;
	POINT tabPt[MAX_PT];
	ABSORBEUR * next;
};

int absorbeurSet(char[]);
int addAbsorbeur(int, POINT[]);
int delAbsorbeur(int);
void printListAbsorbeur(void);
void delListAbsorbeur(void);

static int absorbeurDistanceRequise(POINT, POINT);

static int n = 0;
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
		for(; i < _nb; i++)
		{
			a->tabPt[i].x = tab[i].x;
			a->tabPt[i].y = tab[i].y;
		}
		a->next = list;
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
	/*TODO*/
	n--;
	return OK;
}

void writeAbsorbeur(FILE *file)
{
	int i = 0;
	ABSORBEUR *a = list;
	fprintf(file, "#absorbeur\n%d\n", n);
	while(a != NULL)
	{
		fprintf(file, "%d", a->nbPt);
		for(i = 0; i < a->nbPt; i++)
			fprintf(file, "%lf %lf",
				a->tabPt[i].x, a->tabPt[i].y);
		fprintf(file, "\n");
		a = a->next;
	}
	fprintf(file, "FIN_LISTE\n\n");
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
	return ;
}

static int absorbeurDistanceRequise(POINT _a, POINT _b)
{
	if(utilitaireDistance2Points(_a, _b) < EPSIL_CREATION)
		return OK;
	else
		return NO;
}

int nbAbso(void) { return n; }

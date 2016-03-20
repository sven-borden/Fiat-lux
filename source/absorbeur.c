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
};

static int absorbeurDistanceRequise(POINT, POINT);

static ABSORBEUR tabAbsorbeur[MAX_RENDU1];
static int n = 0;

int absorbeurSet(char line[MAX_LINE])
{
    int _nbPt, j = 0, i = 0;
    char* start = line, end = NULL;
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
    tabAbsorbeur[n].nbPt = _nbPt;
    tabAbsorbeur[n].tabPt[i] = _points[i];
    i++;
    for(; i < _nbPt; i++)
    {
        tabAbsorbeur[n].tabPt[i] = _points[i];
        if(!distanceRequise(tabAbsorbeur[n].tabPt[i], tabAbsorbeur[n].tabPt[i-1]))
        {
            error_lecture_point_trop_proche(ERR_ABSORBEUR, n);
            return NO;
        }
    }       
    n++;    return OK;
}

static int absorbeurDistanceRequise(POINT _a, POINT _b)
{
    if(distance2Points(_a, _b) < EPSIL_CREATION)
        return OK;
    else
        return NO;
}

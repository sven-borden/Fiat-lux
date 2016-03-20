#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "absorbeur.h"
#include "constantes.h"
#include "utilitaire.h"

#define OK 0
#define NO 1

typedef struct Absorbeur ABSORBEUR;

struct Absorbeur
{
	int nbPt;
	POINT tabPt[MAX_PT];
};

static ABSORBEUR tabAbsorbeur[MAX_RENDU1];
static int n = 0;

static int distanceRequise(POINT, POINT);

int setAbsorbeur(char line[MAX_LINE])
{
    int _nbPt, j = 0;
    char* start = line;
    char* end = NULL;
    POINT _points[MAX_PT];
    //lecture
    
    _nbPt = (int)strtod(line, &end);
    if(_nbPt < 2 || _nbPt > MAX_PT)
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
    int i = 0;
    tabAbsorbeur[n].tabPt[i] = _points[i];
    
    for(i = 1; i < _nbPt; i++)
    {
        tabAbsorbeur[n].tabPt[i] = _points[i];
        if(!distanceRequise(tabAbsorbeur[n].tabPt[i], tabAbsorbeur[n].tabPt[i-1]))
        {
            error_lecture_point_trop_proche(ERR_ABSORBEUR, n);
            return NO;
        }
    }       
    n++;
    return OK;
}

int distanceRequise(POINT _a, POINT _b)
{
    if(distance2Points(_a, _b) < EPSIL_CREATION)
        return OK;
    else
        return NO;
}

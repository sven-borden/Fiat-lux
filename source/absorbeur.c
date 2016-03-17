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

int setAbsorbeur(int _nbPt, POINT _tabPt[MAX_PT])
{
    tabAbsorbeur[n].nbPt = _nbPt;
    int i = 0;
    tabAbsorbeur[n].tabPt[i] = _tabPt[i];
    
    for(i = 1; i < _nbPt; i++)
    {
        tabAbsorbeur[n].tabPt[i] = _tabPt[i];
        if(!distanceRequise(tabAbsorbeur[n].tabPt[i], tabAbsorbeur[n].tabPt[i-1]))
        {
            error_lecture_point_trop_proche(ERR_ABSORBEUR, i);
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
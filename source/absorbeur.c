#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "absorbeur.h"
#include "constantes.h"
#include "utilitaire.h"

typedef struct Absorbeur ABSORBEUR;

struct Absorbeur
{
	int nbPt;
	POINT tabPt[MAX_PT];
};

static ABSORBEUR tabAbsorbeur[MAX_RENDU1];
static int n = 0;

void setAbsorbeur(int _nbPt, POINT _tabPt[MAX_PT])
{
    tabAbsorbeur[n].nbPt = _nbPt;
    int i = 0;
    for(i = 0; i < _nbPt; i++)
        tabAbsorbeur[n].tabPt[i] = _tabPt[i];
        
    n++;
}
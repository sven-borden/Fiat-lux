#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "absorbeur.h"
#include "constantes.h"
#include "utilitaire.h"


typedef struct Projecteur PROJECTEUR;

struct Projecteur
{
	POINT pos;
	double alpha;
};

static PROJECTEUR tabProjecteur[MAX_RENDU1];
static int n = 0;

void setProjecteur(POINT _pos, double _alpha)
{
    tabProjecteur[n].pos.x = _pos.x;
    tabProjecteur[n].pos.y = _pos.y;
    tabProjecteur[n].alpha = _alpha;
    n++;
}
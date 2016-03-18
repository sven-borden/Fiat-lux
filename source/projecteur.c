#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "absorbeur.h"
#include "constantes.h"
#include "utilitaire.h"

#define OK 0
#define NO 1

typedef struct Projecteur PROJECTEUR;

struct Projecteur
{
	POINT pos;
	double alpha;
};

static PROJECTEUR tabProjecteur[MAX_RENDU1];
static int n = 0;

int setProjecteur(char line[MAX_LINE])
{
    double x = 0, y = 0, alpha = 0;
    if(sscanf(line, "%lf %lf %lf", &a, &b, &alpha) != 3)
    {
        error_lecture_elements(ERR_PROJECTEUR, ERR_PAS_ASSEZ);
        return NO;
    }
    tabProjecteur[n].pos.x = x;
    tabProjecteur[n].pos.y = y;
    tabProjecteur[n].alpha = alpha;
    n++;
    return OK;
}
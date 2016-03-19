#include <stdio.h>
#include <stdlib.h>
#include "utilitaire.h"
#include "constantes.h"
#include "reflecteur.h"
#include "error.h"

#define OK 0
#define NO 1

typedef struct Reflecteur REFLECTEUR;

struct Reflecteur
{
	POINT a;
	POINT b;
};

static REFLECTEUR tabReflecteur[MAX_RENDU1];
static int n = 0;

static int distanceRequise(POINT, POINT);

int setReflecteur(char line[MAX_LINE])
{
    printf("IN %s, LINE %d\n", __func__, __LINE__);
    POINT _a, _b;
    if(sscanf(line, "%lf %lf %lf %lf", &_a.x, &_a.y, &_b.x, &_b.y) != 4)
    {
        error_lecture_elements(ERR_REFLECTEUR, ERR_PAS_ASSEZ);
        return NO;
    }
    
    if(!distanceRequise(_a, _b))
    {
        error_lecture_point_trop_proche(ERR_REFLECTEUR, n);
        return NO;
    }
    tabReflecteur[n].a.x = _a.x;
    tabReflecteur[n].a.y = _a.y;
    tabReflecteur[n].b.x = _b.x;
    tabReflecteur[n].b.y = _b.y;
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

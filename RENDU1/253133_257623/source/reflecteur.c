/*
    Fichier:    reflecteur.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      16 mars 2016
    Version:    0.9
    Description:Module reflecteur qui gere la structure 
*/

#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "error.h"
#include "utilitaire.h"
#include "reflecteur.h"

#define OK      0
#define NO      1
#define NB_ELEM 4

typedef struct Reflecteur REFLECTEUR;

struct Reflecteur
{
	POINT a;
	POINT b;
};

static int reflecteurDistanceRequise(POINT, POINT);

static REFLECTEUR tabReflecteur[MAX_RENDU1];
static int n = 0;

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
    tabReflecteur[n].a.x = _a.x;
    tabReflecteur[n].a.y = _a.y;
    tabReflecteur[n].b.x = _b.x;
    tabReflecteur[n].b.y = _b.y;
    n++;
    return OK;
}

static int reflecteurDistanceRequise(POINT _a, POINT _b)
{
    if(utilitaireDistance2Points(_a, _b) < EPSIL_CREATION)
        return OK;
    else
        return NO;
}

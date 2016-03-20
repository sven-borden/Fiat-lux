/*
    Fichier:    projecteur.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      16 mars 2016
    Version:    0.9
    Description:Module projecteur qui gere la structure
*/

#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "error.h"
#include "utilitaire.h"
#include "projecteur.h"

#define OK      0
#define NO      1
#define NB_ELEM 3

typedef struct Projecteur PROJECTEUR;

struct Projecteur
{
	POINT pos;
	double alpha;
};

static PROJECTEUR tabProjecteur[MAX_RENDU1];
static int n = 0;

int projecteurSet(char line[MAX_LINE])
{
    double x = 0, y = 0, alpha = 0;
    if(sscanf(line, "%lf %lf %lf", &x, &y, &alpha) != NB_ELEM)
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

/*
    Fichier:    photon.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      16 mars 2016
    Version:    0.9
    Description:Module photon qui gere la structure photon
*/

#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "error.h"
#include "utilitaire.h"
#include "photon.h"

#define OK      0
#define NO      1
#define NB_ELEM 3

typedef struct Photon PHOTON;

struct Photon
{
	POINT pos;
	double alpha;
};

static PHOTON tabPhoton[MAX_RENDU1];
static int n = 0;

int photonSet(char line[MAX_LINE])
{
    POINT _pos; double _alpha;
    if(sscanf(line, "%lf %lf %lf", 
	&_pos.x, &_pos.y, &_alpha) != NB_ELEM)
    {
        error_lecture_elements(ERR_PHOTON, ERR_PAS_ASSEZ);
        return NO;
    }

	tabPhoton[n].pos.x = _pos.x;
	tabPhoton[n].pos.y = _pos.y;
	tabPhoton[n].alpha = _alpha;
	n++;
	return OK;
}

#include <stdio.h>
#include <stdlib.h>
#include "utilitaire.h"
#include "constantes.h"
#include "photon.h"

#define OK 0
#define NO 1

typedef struct Photon PHOTON;

struct Photon
{
	POINT pos;
	double alpha;
};

static PHOTON tabPhoton[MAX_RENDU1];
static int n = 0;

int setPhoton(char line[MAX_LINE])
{
    POINT _pos; int _alpha;
    if(sscanf(line, "%lf %lf %lf", &_pos.x, &_pos.y, &_alpha) != 3)
    {
        error_lecture_elements(ERR_PHOTON, ERR_PAS_ASSEZ);
        return NO;
    }

	tabPhoton[n].pos.x = _pos.x;
	tabPhoton[n].pos.y = _pos.y;
	tabPhoton[n].alpha = _alpha;
	n++;
}

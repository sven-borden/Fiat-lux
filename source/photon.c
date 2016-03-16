#include <stdio.h>
#include <stdlib.h>
#include "utilitaire.h"
#include "constantes.h"
#include "photon.h"


typedef struct Photon PHOTON;

struct Photon
{
	POINT pos;
	double alpha;
};

static PHOTON tabPhoton[MAX_RENDU1];
static n = 0;

void setPhoton(POINT _pos, double _alpha)
{
	tab[n].pos.x = _pos.x;
	tab[n].pos.y = _pos.y;
	tab[n].alpha = _alpha;
	n++;
}

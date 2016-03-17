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
static int n = 0;

void setPhoton(POINT _pos, double _alpha)
{
	tabPhoton[n].pos.x = _pos.x;
	tabPhoton[n].pos.y = _pos.y;
	tabPhoton[n].alpha = _alpha;
	n++;
}

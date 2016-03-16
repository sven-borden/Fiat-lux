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


#ifndef photon_h
#define photon_h

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "constantes.h"
#include "tolerance.h"

typedef struct
{
    double x;
    double y;
    double alpha;
}COORD_PHOTON;

static COORD_PHOTON tab_f[MAX_RENDU1];

void photon (char* ligne, int numero);

#endif

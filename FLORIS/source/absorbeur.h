#ifndef absorbeur_h
#define absorbeur_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "constantes.h"
#include "error.h"
#include "tolerance.h"


typedef struct
{
    double x;
    double y;
}COORD_ABSORBEUR;

static COORD_ABSORBEUR tab_a[MAX_RENDU1][MAX_LINE];

void absorbeur (char* ligne, int numero);

#endif

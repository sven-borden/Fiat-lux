#ifndef reflecteur_h
#define reflecteur_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "error.h"
#include "constantes.h"
#include "tolerance.h"

typedef struct
{
    double x1;
    double y1;
    double x2;
    double y2;
}COORD_REFLECTEUR;

static COORD_REFLECTEUR tab_r[MAX_RENDU1];

void reflecteur (char* ligne, int numero);

#endif

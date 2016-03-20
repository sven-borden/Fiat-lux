#ifndef projecteur_h
#define projecteur_h

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
}COORD_PROJECTEUR;

static COORD_PROJECTEUR tab_p[MAX_RENDU1];

void projecteur (char* ligne, int numero);

#endif

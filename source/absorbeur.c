#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "absorbeur.h"
#include "constantes.h"
#include "utilitaire.h"
typedef struct Absorbeur ABSORBEUR;

struct Absorbeur
{
	int nbPt;
	POINT tabPt[MAX_PT];
};

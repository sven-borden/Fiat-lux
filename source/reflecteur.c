#include <stdio.h>
#include <stdlib.h>
#include "utilitaire.h"
#include "constantes.h"
#include "reflecteur.h"

typedef struct Reflecteur REFLECTEUR

struct Reflecteur
{
	POINT pos;
	double alpha;
};

static REFLECTEUR tabReflecteur[MAX_RENDU1];

#include <stdio.h>
#include <stdlib.h>
#include "utilitaire.h"
#include "constantes.h"
#include "projecteur.h"


typedef struct Projecteur PROJECTEUR;

struct Projecteur
{
	POINT pos;
	double alpha;
};

static PROJECTEUR tabProjecteur[MAX_RENDU1];

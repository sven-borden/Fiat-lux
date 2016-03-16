#include <stdio.h>
#include <stdlib.h>
#include "utilitaire.h"
#include "constantes.h"
#include "reflecteur.h"

typedef struct Reflecteur REFLECTEUR

struct Reflecteur
{
	POINT a;
    POINT b;
};

static REFLECTEUR tabReflecteur[MAX_RENDU1];
static int n = 0;

void setReflecteur(POINT _a, POINT _b)
{
    tabReflecteur[n].a.x = _a.x;
    tabReflecteur[n].a.y = _a.y;
    tabReflecteur[n].b.x = _b.x;
    tabReflecteur[n].b.y = _b.y;
    n++;
}
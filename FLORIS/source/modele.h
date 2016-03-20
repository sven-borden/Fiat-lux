#ifndef modele_h
#define modele_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "error.h"
#include "projecteur.h"
#include "reflecteur.h"
#include "absorbeur.h"
#include "photon.h"

#define MAX 100

enum Etat_lecture {NB0,PROJECTEUR,NB1,REFLECTEUR,NB2,ABSORBEUR,NB3,PHOTON,NB4};

void modele_lecture();

#endif

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "utilitaire.h"

void graphicDrawPhoton(POINT, double);
void graphicDrawAbsorbeur(int, POINT[]);
void graphicDrawReflecteur(POINT, POINT);
void graphicDrawProjecteur(POINT, double);
void graphicDrawZoom(double, double, double, double);
#endif

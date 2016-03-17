#include <stdio.h>
#include <stdlib.h>
#include "utilitaire.h"
#include <math.h>

double normeVector(VECTOR v)
{
    double xLen = v.ptFin.x - v.ptDeb.x;
    double yLen = v.ptFin.y - v.ptDeb.y;
    return sqrt(xLen*xLen + yLen*yLen); 
}

double distance2Points(POINT a, POINT b)
{
    double xLen = b.x - a.y;
    double yLen = b.y - a.y;
    return sqrt(xLen*xlen + yLen* yLen);
}
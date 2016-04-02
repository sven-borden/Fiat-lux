#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utilitaire.h"

double points_trop_proche(double x1, double y1, double x2, double y2)
{
	double d = 0;
	d = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	return d;
}


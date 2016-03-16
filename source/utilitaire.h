#ifndef UTILITAIRE_H
#define UTILITAIRE_H

typedef struct Point POINT;
typedef struct Vector VECTOR;

struct Point
{
	double x;
	double y;
};

struct Vector
{
	POINT ptDeb;
	POINT ptFin;
};

#endif

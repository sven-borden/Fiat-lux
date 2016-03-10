#ifndef TOOLS_H
#define TOOLS_H

//prototypes
typedef struct Point POINT;
typedef struct Vector VECTOR;

struct Point
{
    double x;
    double y;   
};

struct Vector
{
    Point ptDeb;
    Point ptFin;
};

double distanceTwoPoint(POINT, POINT);
double longueurVecteur(VECTOR)
#endif
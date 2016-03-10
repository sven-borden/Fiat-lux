#ifndef TOOLS_H
#define TOOLS_H

//prototypes
typedef struct Point point;
typedef struct Vector vector;

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

double distanceTwoPoint(Point, Point);
double longueurVecteur(Vector)
#endif
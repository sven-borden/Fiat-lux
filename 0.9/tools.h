#ifndef TOOLS_H
#define TOOLS_H

//prototypes
typedef struct point point;
typedef struct vector vector;

struct point
{
    double x;
    double y;   
};

struct vector
{
    double x1;
    double y1;
    double x2;
    double y2;
};

double distanceTwoPoint(point, point);

#endif
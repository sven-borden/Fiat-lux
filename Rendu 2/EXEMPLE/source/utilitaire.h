/*!
 \file utilitaire.h
 \brief Module which provides general tools (for ex. vector-operations)
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.2
 \date 19 april 2016
 */

#ifndef UTILITAIRE_H
#define UTILITAIRE_H

typedef struct Vecteur VECTEUR;  //vector (for direction or position)
struct Vecteur
{
	double x; //contains the x coordinate
	double y; //contains the y coordinate
};

//DISTANCE BETWEEN 2 POINTS DEFINED BY VECTORS (with same origin)
double 	utilitaire_distance(VECTEUR p1, VECTEUR p2);

//FINDS SUPERPOSITIONS AND INTERSECTIONS
_Bool 	utilitaire_common_point	(VECTEUR a1, VECTEUR a2, VECTEUR b1, VECTEUR b2);

//FINDS THE NEXT POINT based on an angle, a length and the start-point
VECTEUR utilitaire_next_point(VECTEUR o, double alpha, double d);

#endif

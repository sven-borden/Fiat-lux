/*!
 \file utilitaire.c
 \brief Module which provides general tools (for ex. vector-operations)
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.2
 \date 19 april 2016
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "utilitaire.h"

static double 	utilitaire_vectorproduct(VECTEUR v1, VECTEUR v2);
static double 	utilitaire_scalarproduct(VECTEUR v1, VECTEUR v2);
static VECTEUR  utilitaire_unitaire(VECTEUR v, double norm);
static double 	utilitaire_norm(VECTEUR v);
static VECTEUR  utilitaire_vector_p_to_p(VECTEUR start, VECTEUR end);
static VECTEUR  utilitaire_normal(VECTEUR u);
static _Bool 	utilitaire_intersection(VECTEUR a1b2, VECTEUR b1a2, VECTEUR a1b1,
										VECTEUR u1, VECTEUR u2);

//distance between two points defined by vectors (with same origin)
double utilitaire_distance(VECTEUR p1, VECTEUR p2)
{
	return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

_Bool utilitaire_common_point(VECTEUR a1, VECTEUR a2, VECTEUR b1, VECTEUR b2)
{
	VECTEUR v1   = utilitaire_vector_p_to_p(a1, a2);
	VECTEUR v2   = utilitaire_vector_p_to_p(b1, b2);
	double norm1 = utilitaire_norm(v1);
	double norm2 = utilitaire_norm(v2);
	VECTEUR u1   = utilitaire_unitaire(v1, norm1);
	VECTEUR u2   = utilitaire_unitaire(v2, norm2);
	VECTEUR a1b1 = utilitaire_vector_p_to_p(a1, b1);
	VECTEUR a1b2 = utilitaire_vector_p_to_p(a1, b2);
	VECTEUR b1a2 = utilitaire_vector_p_to_p(b1, a2);

	if(fabs(utilitaire_vectorproduct(u1, u2)) <= EPSIL_PARAL)
	{
		double vpbegin = utilitaire_vectorproduct(u1, utilitaire_unitaire(a1b1,
													  utilitaire_norm(a1b1)));
		if(fabs(vpbegin) <= EPSIL_PARAL)
		{
			double spu1v2  = utilitaire_scalarproduct(u1, v2);
			double spbegin = utilitaire_scalarproduct(u1, a1b1);
			if(fabs(spu1v2) < EPSIL_PARAL)
			{
				if(spbegin > 0)
				{
					if(spbegin + spu1v2 > norm1 + EPSIL_CONTACT)
						return 0;
				}
				else if(spbegin < -EPSIL_CONTACT)
					return 0;
			}
			else
			{
				if(spbegin > 0)
				{
					if(spbegin > norm1 + EPSIL_CONTACT)
						return 0;
				}
				else if(spbegin + spu1v2 < -EPSIL_CONTACT)
					return 0;
			}
			return 1;
		}
		else
			return 0;
	}
	else
		return utilitaire_intersection(a1b2, b1a2, a1b1, u1, u2);
}

VECTEUR utilitaire_next_point(VECTEUR o, double alpha, double d)
{
	return (VECTEUR){o.x + d * cos(alpha), o.y + d * sin(alpha)};
}

static double utilitaire_vectorproduct(VECTEUR v1, VECTEUR v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

static double utilitaire_scalarproduct(VECTEUR v1, VECTEUR v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

static VECTEUR utilitaire_unitaire(VECTEUR v, double norm)
{
	VECTEUR u = {v.x / norm, v.y / norm};
	return u;
}

static double utilitaire_norm(VECTEUR v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

static VECTEUR utilitaire_vector_p_to_p(VECTEUR start, VECTEUR end)
{
	VECTEUR v = {end.x - start.x, end.y - start.y};
	return v;
}

static VECTEUR utilitaire_normal(VECTEUR u)
{
	VECTEUR n = {-u.y, u.x};
	return n;
}

static _Bool utilitaire_intersection(VECTEUR a1b2, VECTEUR b1a2, VECTEUR a1b1,
                                     VECTEUR u1, VECTEUR u2)
{
	VECTEUR n1 	 = utilitaire_normal(u1);
	VECTEUR n2 	 = utilitaire_normal(u2);
	double spn1a1b1 = utilitaire_scalarproduct(n1, a1b1);
	double spn1a1b2 = utilitaire_scalarproduct(n1, a1b2);
	double spn2b1a1 = utilitaire_scalarproduct((VECTEUR){-(n2.x), -(n2.y)}, a1b1);
	double spn2b1a2 = utilitaire_scalarproduct(n2, b1a2);
	if(fabs(spn1a1b1) < EPSIL_CONTACT || fabs(spn1a1b2) < EPSIL_CONTACT
		|| spn1a1b1 * spn1a1b2 < 0)
	{  //### space
		if(fabs(spn2b1a1) < EPSIL_CONTACT || fabs(spn2b1a2) < EPSIL_CONTACT
		   || spn2b1a1 * spn2b1a2 < 0)
			return 1;
	}
	return 0;
}

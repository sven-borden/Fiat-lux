#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "tolerance.h"
#include <math.h>
#define NON 0
#define OUI 1
typedef struct Vector VECTOR;
typedef struct Point POINT;

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

int utilitaire(VECTOR, VECTOR);
int intersection(VECTOR, VECTOR);
void print(VECTOR, char*);
double utilitaireNormeVector(VECTOR);
double utilitaireProduitScalaire(VECTOR, VECTOR);
double utilitaireProduitVectoriel(VECTOR, VECTOR);

void print(VECTOR v, char* b)
{
	printf("VECTEUR \t%s\n", b);
	printf("DEPART :\t%lf\t%lf\n", v.ptDeb.x, v.ptDeb.y);
	printf("FIN:\t\t%lf\t%lf\n\n\n", v.ptFin.x, v.ptFin.y);
}

int main(int argc, char* argv[])
{
	if(argc!=9)
		return EXIT_FAILURE;
	VECTOR a;
	a.ptDeb.x = strtod(argv[1], NULL);
	a.ptDeb.y = strtod(argv[2], NULL);
	a.ptFin.x = strtod(argv[3], NULL);
	a.ptFin.y = strtod(argv[4], NULL);
	VECTOR b;
	b.ptDeb.x = strtod(argv[5], NULL);
	b.ptDeb.y = strtod(argv[6], NULL);
	b.ptFin.x = strtod(argv[7], NULL);
	b.ptFin.y = strtod(argv[8], NULL);
	
	if(utilitaire(a, b) == 1)
		printf("SUPPERPOSER\n");
	if(intersection(a, b) == 1)
		printf("INTERSECTION\n");
	return EXIT_SUCCESS;
}

int utilitaire(VECTOR v1, VECTOR v2)
{
        VECTOR ud1d2;
        ud1d2.ptDeb.x = v1.ptDeb.x;		ud1d2.ptDeb.y = v1.ptDeb.y;
        ud1d2.ptFin.x = v2.ptDeb.x;		ud1d2.ptFin.y = v2.ptDeb.y;

#ifdef DEBUG
	print(v1, "v1");
	print(v2, "v2");
	print(ud1d2, "ud1d2");
#endif
        double pv = fabs(utilitaireProduitVectoriel(v1, v2));
        if(pv <= EPSIL_PARAL)/*2 vecteurs parallèles*/
        {
                double pvDeb = fabs(utilitaireProduitVectoriel(v1, ud1d2));

			if(pvDeb <= EPSIL_PARAL)/*2 vecteur colinéaires*/
			{
				VECTOR vd1d2;
				vd1d2.ptDeb.x = v1.ptDeb.x;		vd1d2.ptDeb.y = v1.ptDeb.y;
				vd1d2.ptFin.x = v2.ptDeb.x;		vd1d2.ptFin.y = v2.ptDeb.y;
                        
				double psu1v2 = utilitaireProduitScalaire(v1, v2);
                double psDeb = utilitaireProduitScalaire(v1, vd1d2);

                if(psDeb > 0 || psDeb < -EPSIL_CONTACT || 
					psDeb + psu1v2 < -EPSIL_CONTACT)
                {
					double norme = utilitaireNormeVector(v1);
					if(psDeb + psu1v2 > norme + EPSIL_CONTACT)
                    	return NON;
                    if(psDeb > norme + EPSIL_CONTACT)
                       	return NON;
					return OUI;
                }
				else
					return OUI;
            }
			return NON;
        }
        return NON;
}

int intersection(VECTOR v1, VECTOR v2)
{
	VECTOR vd1d2;
	vd1d2.ptDeb.x = v1.ptDeb.x;		vd1d2.ptDeb.y = v1.ptDeb.y;
	vd1d2.ptFin.x = v2.ptDeb.x;		vd1d2.ptFin.y = v2.ptDeb.y;

	VECTOR vd1f2;
	vd1f2.ptDeb.x = v1.ptDeb.x;		vd1f2.ptDeb.x = v1.ptDeb.y;
	vd1f2.ptFin.x = v2.ptFin.x;		vd1f2.ptFin.y = v2.ptFin.y;

	VECTOR vd2f1;
	vd2f1.ptDeb.x = v2.ptDeb.x;		vd2f1.ptDeb.y = v2.ptDeb.y;
	vd2f1.ptFin.x = v1.ptFin.x;		vd2f1.ptFin.y = v1.ptFin.y;

	VECTOR n1;
	n1.ptDeb.x = v1.ptDeb.x;		n1.ptDeb.y = v1.ptDeb.y;
	n1.ptFin.x = -v1.ptFin.x;		n1.ptFin.y = v1.ptFin.y;

	VECTOR n2;
	n2.ptDeb.x = v2.ptDeb.x;		n2.ptDeb.y = v2.ptDeb.y;
	n2.ptFin.x = -v2.ptFin.x;		n2.ptDeb.y = v2.ptFin.y;

	VECTOR n2neg;
	n2neg.ptDeb.x = n2.ptDeb.y;		n2neg.ptDeb.y = n2.ptDeb.x;
	n2neg.ptFin.x = n2.ptFin.y;		n2neg.ptFin.y = -n2.ptFin.x;

	double ps1d1d2 = fabs(utilitaireProduitScalaire(n1, vd1d2));
	double ps1d1f2 = fabs(utilitaireProduitScalaire(n1, vd1f2));
	double ps2d2d1 = fabs(utilitaireProduitScalaire(n2neg, vd1d2));
	double ps2d2f1 = fabs(utilitaireProduitScalaire(n2, vd2f1));
#ifdef DEBUG
	print(vd1d2, "vd1d2");
	print(vd1f2, "vd1f2");
	print(vd2f1, "vd2f1");
	print(n1, "n1");
	print(n2, "n2");
	print(n2neg, "n2neg");
#endif
	if(ps1d1d2 < EPSIL_CONTACT ||
		ps1d1f2 < EPSIL_CONTACT ||
		(ps1d1d2*ps1d1f2) < 0)
	{
		if(ps2d2d1 < EPSIL_CONTACT ||
			ps2d2f1 < EPSIL_CONTACT ||
			(ps2d2d1*ps2d2f1) < 0)
		{
			//alors c'est une interesection
			return OUI;
		}
	}
	return NON;
}

double utilitaireNormeVector(VECTOR v)
{
	double xLen = v.ptFin.x - v.ptDeb.x;
	double yLen = v.ptFin.y - v.ptDeb.y;
	return sqrt(xLen*xLen + yLen*yLen);
}

double utilitaireProduitScalaire(VECTOR v, VECTOR w)
{
	double normeX = v.ptFin.x - v.ptDeb.x;
	double normeY = v.ptFin.y - v.ptDeb.y;
	return normeX * normeY + normeY * normeY;
}

double utilitaireProduitVectoriel(VECTOR v, VECTOR w)
{
	double normeX = v.ptFin.x - v.ptDeb.x;
	double normeY = v.ptFin.y - v.ptDeb.y;
	return normeX * normeY - normeY * normeX;
}

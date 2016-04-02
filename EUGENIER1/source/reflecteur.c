#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "error.h"
#include "reflecteur.h"
#include "utilitaire.h"
#define NB_ELEM	4
#define NB_REFL 1

typedef struct refl{
	double debx;
	double deby;
	double finx;
	double finy;
}REFL;


static REFL tab_r[MAX_RENDU1]; 


int decodage_nb_r(char *tab, int *ptr_nb_r)
{
	if(sscanf(tab,"%d", ptr_nb_r) != NB_REFL) 
	{
		error_lect_nb_elements(ERR_REFLECTEUR); 			
		return 1;
	}
	return 0;
}
int reflecteur(char *tab, int i) 
{	
	if(sscanf(tab, "%lf %lf %lf %lf", &tab_r[i].debx, &tab_r[i].deby, 
	   &tab_r[i].finx, &tab_r[i].finy) != NB_ELEM) 
	{
		error_lecture_elements(ERR_REFLECTEUR, ERR_PAS_ASSEZ);
		return 1;
	}
	else 
	{
		if (points_trop_proche(tab_r[i].debx, tab_r[i].deby, tab_r[i].finx, 
		    tab_r[i].finy) <= EPSIL_CREATION)
		{
			error_lecture_point_trop_proche(ERR_REFLECTEUR, i); 
			return 1;
		}
		return 0;		
	}
}

#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "error.h"
#include "photon.h"
#include "utilitaire.h" 
#define NB_ELEM 3
#define NB_PHOT 1


typedef struct phot{
	double x;
	double y;
	double alpha;
}PHOT;


static PHOT tab_ph[MAX_RENDU1]; 


int decodage_nb_ph(char *tab, int *ptr_nb_ph)
{
	if(sscanf(tab,"%d", ptr_nb_ph) != NB_PHOT) 
	{
		error_lect_nb_elements(ERR_PHOTON); 
		return 1;
	}
	return 0;
}

int photon(char *tab, int i)
{
	if(sscanf(tab, "%lf %lf %lf", &tab_ph[i].x, &tab_ph[i].y, 
	   &tab_ph[i].alpha) != NB_ELEM) 
	{
		error_lecture_elements(ERR_PHOTON, ERR_PAS_ASSEZ);
		return 1;
	}
	else return 0;
}

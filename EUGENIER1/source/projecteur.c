#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "error.h"
#include "projecteur.h"
#include "utilitaire.h" 
#define NB_ELEM 3
#define NB_PROJ 1


typedef struct proj{
	double x;
	double y;
	double alpha;
}PROJ;


static PROJ tab_pr[MAX_RENDU1]; 


int decodage_nb_pr(char *tab, int *ptr_nb_pr)
{
	if(sscanf(tab,"%d", ptr_nb_pr) != NB_PROJ) 
	{
		error_lect_nb_elements(ERR_PROJECTEUR);  
		return 1;
	}
	return 0;
}

int projecteur(char *tab, int i)
{
	if(sscanf(tab, "%lf %lf %lf", &tab_pr[i].x, &tab_pr[i].y, 
	   &tab_pr[i].alpha) != NB_ELEM) 
	{
		error_lecture_elements(ERR_PROJECTEUR, ERR_PAS_ASSEZ);
		return 1;
	}
	return 0;
}


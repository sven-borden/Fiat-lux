#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "error.h"
#include "absorbeur.h"
#include "utilitaire.h" 
#define NB_ABSO 1
#define MIN_PT  2


typedef struct abso{
	int nb_points; 
	double x;
	double y;
}ABSO;


static ABSO tab_a[MAX_RENDU1*MAX_RENDU1]; 


int decodage_nb_a(char *tab, int *ptr_nb_a)
{
	if(sscanf(tab,"%d", ptr_nb_a) != NB_ABSO) 
	{
		error_lect_nb_elements(ERR_ABSORBEUR); 
		return 1;
	}
	return 0;
}


int absorbeur(char *tab, int i)
{
	int k = 0;
	static int l = 0;
	double a = 0, b = 0;
	char *p_start_a = NULL, *p_end_a = NULL;
	
	sscanf(tab,"%d", &tab_a[i].nb_points);
	
	if((tab_a[i].nb_points < MIN_PT)||(tab_a[i].nb_points > MAX_PT)) 
	{
		error_lect_nb_points_absorbeur();
		return 1;
	}
	else 
	{
		p_start_a = tab+1;
		
		for(k = 0; k < tab_a[i].nb_points; k++)
		{
			a = strtod(p_start_a, &p_end_a); 
			
			if(p_start_a == p_end_a) 
			{
				error_lecture_elements(ERR_ABSORBEUR, ERR_PAS_ASSEZ);
				return 1;
			}
			else tab_a[l].x = a;

			p_start_a = p_end_a;

			b = strtod(p_start_a, &p_end_a);
			
			if(p_start_a == p_end_a) 
			{
				error_lecture_elements(ERR_ABSORBEUR, ERR_PAS_ASSEZ);
				return 1;
			}
			else tab_a[l].y = b;
			
			p_start_a = p_end_a;
			
			if(l != i*tab_a[i].nb_points)
			{
				if (points_trop_proche(tab_a[l-1].x, tab_a[l-1].y, tab_a[l].x, 
				    tab_a[l].y) <= EPSIL_CREATION) 
				{
					error_lecture_point_trop_proche(ERR_ABSORBEUR, i); 
					return 1;
				}
			}
			l++;
		}
		return 0;
	} 
}

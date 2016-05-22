/*!
 \file absorbeur.c
 \brief Module which manages the absorbers
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.1
 \date 19 april 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "utilitaire.h"
#include "error.h"
#include "graphic.h"
#include "absorbeur.h"

#define ABSORBEUR_LINE_WIDTH 3

typedef struct Absorbeur ABSORBEUR;
struct Absorbeur
{
	VECTEUR p[MAX_PT]; //contains the positions x and y of its points
	int nbp; //contains its number of points
};

//shifts the position from where the next sscanf should read
static void absorbeur_shift(char ** beg, char ** end, int * counter);

static ABSORBEUR* tab_a = NULL; //table for absorbers
static int nb_absorbeur = 0;

_Bool absorbeur_lecture(char * table, int i)
{
	int counter = 0;
	int j = 0;

	if(sscanf(table, "%d", &tab_a[i].nbp) == 1)
	{
		char *beg = table, *end = NULL;

		absorbeur_shift(&beg, &end, &counter);
		while(j < tab_a[i].nbp) //reads and counts the values
		{
			if(sscanf(beg, "%lg", &tab_a[i].p[j].x) == 1)
				absorbeur_shift(&beg, &end, &counter);
			if(sscanf(beg, "%lg", &tab_a[i].p[j].y) == 1)
				absorbeur_shift(&beg, &end, &counter);
			j++;
		}
	}
	else //if unexpected FIN_LISTE or something else unexpected (=no int)
		error_lecture_elements(ERR_ABSORBEUR, ERR_PAS_ASSEZ);

	if(tab_a[i].nbp > 1 && tab_a[i].nbp <= MAX_PT)
	{
		if((--counter) == 2 * tab_a[i].nbp)//controls num of values
		{
			for(j = 1; j < tab_a[i].nbp; j++)
				if(utilitaire_distance(tab_a[i].p[j], tab_a[i].p[j-1])
					<= EPSIL_CREATION)
				{
					error_lecture_point_trop_proche(ERR_ABSORBEUR, i);
					return 0;
				}
			return 1;
		}
		else
			error_lecture_elements(ERR_ABSORBEUR, ERR_PAS_ASSEZ);
	}
	else  //too many or not enough points indicated
		error_lect_nb_points_absorbeur();
	return 0;
}

int absorbeur_get_tsize(void)
{
	return nb_absorbeur;
}

void absorbeur_get_lineseg(int *i, VECTEUR *a, VECTEUR *b, _Bool *countadd, 
						   _Bool set_back)
{
	static j = 1; //saves the segment number for the next call of the function
	if(set_back)//when a new file is loaded
		j = 1;
	else
	{
		*a = tab_a[*i].p[j];
		*b = tab_a[*i].p[j-1];
		j++;		//next segment
		if(j >= tab_a[*i].nbp)  //if last segment, changes to new absorber
		{
			j = 1;
			(*i)++;
			*countadd = 1;	//correction of i for eventual error-messages
		}
		else
			*countadd = 0;
	}
}

_Bool absorbeur_create_table(int nb_elements)
{
	if(tab_a == NULL)
	{
		tab_a = calloc(nb_elements, sizeof(ABSORBEUR));
		nb_absorbeur = nb_elements;  //saves the variable in the module
		if(tab_a)
		   return 1;
	}
	error_msg("\nError Memory Allocation for absorbeurs");
	return 0;
}

void absorbeur_delete_table(void)
{
	if(tab_a)
	{
		free(tab_a);
		tab_a = NULL;
	}
	nb_absorbeur = 0;
}

int absorbeur_save(FILE* file_write)
{
    int i = 0, j = 0;

    fprintf(file_write, "%s", "#Absorbers\n");
    fprintf(file_write, "%s", "#Absorber structure : p[nbp].x p[nbp].y nbp\n");
    fprintf(file_write, "%d", nb_absorbeur);
    for(i = 0; i < nb_absorbeur; i++)
    {
        if(fprintf(file_write,"\n%d ", tab_a[i].nbp)<=0)
			return 0;
        for( j = 0; j < tab_a[i].nbp; j++)
            if(fprintf(file_write, "%lg %lg ", tab_a[i].p[j].x, tab_a[i].p[j].y)
               <= 0)
				return 0;
    }
    fprintf(file_write, "%s", "\nFIN_LISTE\n\n");

    return 1;
}

void absorbeur_draw(void)
{
	int i = 0, j = 0;
	const float blue[3] = {0,0,1};

	graphic_set_color3fv(blue); // in blue
	graphic_set_line_width(ABSORBEUR_LINE_WIDTH);


    for( i = 0 ; i < nb_absorbeur; i++)
        for ( j = 0; j < tab_a[i].nbp-1 ; j++)
            graphic_draw_segments(tab_a[i].p[j].x,   tab_a[i].p[j].y,
                                  tab_a[i].p[j+1].x, tab_a[i].p[j+1].y);

}

static void absorbeur_shift(char ** beg, char ** end, int * counter)
{
 	strtod(*beg, end);
	*beg = *end;
	(*counter)++;
}

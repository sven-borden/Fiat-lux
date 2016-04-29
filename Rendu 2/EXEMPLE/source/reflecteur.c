/*!
 \file reflecteur.c
 \brief Module which manages the reflectors
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.1
 \date 20 april 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include "utilitaire.h"
#include "error.h"
#include "constantes.h"
#include "graphic.h"
#include "reflecteur.h"

#define REFLECTEUR_NUM_ARGU 4
#define REFLECTEUR_LINE_WIDTH 2

typedef struct Reflecteur REFLECTEUR;
struct Reflecteur
{
	VECTEUR p1; //contains the position of its first point
	VECTEUR p2; //contains the position of its second point
};

static REFLECTEUR *tab_r =  NULL;  //table for reflectors
static int nb_reflecteur = 0;

_Bool reflecteur_lecture(char * table, int i)
{
	int counter;
	counter = sscanf(table, "%lg %lg %lg %lg", &tab_r[i].p1.x,
					 &tab_r[i].p1.y, &tab_r[i].p2.x, &tab_r[i].p2.y);
	if(counter == REFLECTEUR_NUM_ARGU)
	{
		if(utilitaire_distance(tab_r[i].p1, tab_r[i].p2) > EPSIL_CREATION)
			return 1;
		error_lecture_point_trop_proche(ERR_REFLECTEUR, i);
	}
	else
		error_lecture_elements(ERR_REFLECTEUR, ERR_PAS_ASSEZ);

	return 0;
}

_Bool reflecteur_verification(void)
{
	int i, j;

	for(i = 1; i < nb_reflecteur; i++)
		for(j = 0; j < i; j++)
			if(utilitaire_common_point(tab_r[i].p1, tab_r[i].p2,
									   tab_r[j].p1, tab_r[j].p2))
			{
				error_lecture_intersection(ERR_REFLECTEUR, i,
										   ERR_REFLECTEUR, j);
				return 0;
			}
	return 1;
}

int reflecteur_get_tsize(void)
{
	return nb_reflecteur;
}

void reflecteur_get_lineseg(int *i, VECTEUR *a, VECTEUR *b)
{
	*a = tab_r[*i].p1;
	*b = tab_r[*i].p2;
	(*i)++;
}

_Bool reflecteur_create_table(int nb_elements)
{
	if(tab_r == NULL)
	{
		tab_r = calloc(nb_elements, sizeof(REFLECTEUR));
		nb_reflecteur = nb_elements;  //saves the variable in the module
		if(tab_r)
		   return 1;
	}
	error_msg("\nError Memory Allocation for reflector");
	return 0;
}

void reflecteur_delete_table(void)
{
	if(tab_r)
	{
		free(tab_r);
		tab_r = NULL;
	}
	nb_reflecteur = 0;
}

int reflecteur_save(FILE* file_write)
{
    int i = 0;

    fprintf(file_write, "%s", "#Reflector\n");
    fprintf(file_write, "%s", "#Reflector structure : p1.x p1.y p2.x p2.y\n");
    fprintf(file_write, "%d", nb_reflecteur);
    for(i = 0; i < nb_reflecteur; i++)
        if(fprintf(file_write, "\n%lg %lg %lg %lg", tab_r[i].p1.x, tab_r[i].p1.y,
									 tab_r[i].p2.x, tab_r[i].p2.y) <= 0)
			return 0;
    fprintf(file_write, "%s", "\nFIN_LISTE\n\n");

    return 1;
}

void reflecteur_draw(void)
{
	int i = 0;
	const float red[3] = {1,0,0};

	graphic_set_color3fv(red); // in red
	graphic_set_line_width(REFLECTEUR_LINE_WIDTH);

	for ( i = 0; i < nb_reflecteur; i++)
		graphic_draw_segments(tab_r[i].p1.x, tab_r[i].p1.y,
							  tab_r[i].p2.x, tab_r[i].p2.y);
}


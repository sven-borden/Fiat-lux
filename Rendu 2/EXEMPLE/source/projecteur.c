/*!
 \file projecteur.c
 \brief Module which manages the projectors
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.1
 \date 21 april 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utilitaire.h"
#include "error.h"
#include "constantes.h"
#include "graphic.h"
#include "projecteur.h"

#define _USE_MATH_DEFINES
#define PROJECTEUR_NUM_ARGU 3
#define PROJECTEUR_LINE_WIDTH 4

typedef struct Projecteur PROJECTEUR;
struct Projecteur
{
	VECTEUR p; //contains its position x and y
	double alpha; //contains the direction where the photons are sent
};

static PROJECTEUR *tab_p =  NULL;  //table for Projectors
static int nb_projecteur = 0;

_Bool projecteur_lecture(char * table, int i)
{
	int counter;
	counter = sscanf(table, "%lg %lg %lg", &tab_p[i].p.x, &tab_p[i].p.y,
					 &tab_p[i].alpha);
	if(counter == PROJECTEUR_NUM_ARGU)
		return 1;
	else  //if there are not enough values or (unexpected) FIN_LISTE
		error_lecture_elements(ERR_PROJECTEUR, ERR_PAS_ASSEZ);

	return 0;
}

int projecteur_get_tsize(void)
{
	return nb_projecteur;
}

void projecteur_get_lineseg(int *i, VECTEUR *a, VECTEUR *b)
{
	*a = tab_p[*i].p;
	*b = utilitaire_next_point(tab_p[*i].p, tab_p[*i].alpha + M_PI/2,
                               (NBPH-1) * EPSIL_PROJ);
	(*i)++;
}

_Bool projecteur_create_table(int nb_elements)
{
	if(tab_p == NULL)
	{
		tab_p = calloc(nb_elements, sizeof(PROJECTEUR));
		nb_projecteur = nb_elements;  //saves the variable in the module
		if(tab_p)
		   return 1;
	}
	error_msg("\nError Memory Allocation for projectors");
	return 0;
}

void projecteur_delete_table(void)
{
    if(tab_p)
	{
		free(tab_p);
		tab_p = NULL;
	}
	nb_projecteur = 0;
}

_Bool projecteur_save(FILE* file_write)
{
    int i = 0;

    fprintf(file_write, "%s", "#Projectors\n");
    fprintf(file_write, "%s", "#Projector structure : pos.x pos.y alpha\n");
    fprintf(file_write, "%d", nb_projecteur);
    for(i = 0; i < nb_projecteur; i++)
        if(fprintf(file_write, "\n%lg %lg %lg", tab_p[i].p.x, tab_p[i].p.y,
												tab_p[i].alpha) <= 0)
			return 0;
    fprintf(file_write, "%s", "\nFIN_LISTE\n\n");

    return 1;
}

void projecteur_draw(void)
{
	int i = 0;
	const float green[3] = {0,1,0};

	graphic_set_color3fv(green); // in green
	graphic_set_line_width(PROJECTEUR_LINE_WIDTH);

    VECTEUR pos2;
	double angle;
	double d = (NBPH-1)*EPSIL_PROJ;

	for ( i = 0; i < nb_projecteur; i++)
	{
        angle = tab_p[i].alpha + (M_PI / 2);
	    pos2 = utilitaire_next_point(tab_p[i].p, angle, d);

        graphic_draw_segments(tab_p[i].p.x, tab_p[i].p.y, pos2.x, pos2.y);
	}
}

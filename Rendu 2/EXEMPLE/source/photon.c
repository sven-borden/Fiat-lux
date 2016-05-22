/*!
 \file photon.c
 \brief Module which manages the photons
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.1
 \date 19 april 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "utilitaire.h"
#include "constantes.h"
#include "graphic.h"
#include "photon.h"

#define PHOTON_NUM_ARGU 3
#define PHOTON_CIRCLE_NB_SIDES 12
#define PHOTON_LINE_WIDTH 2

typedef struct Photon PHOTON;
struct Photon
{
	VECTEUR p; //contains its position x and y
	double angle; //contains the direction where he goes
	PHOTON *next; //contains the adress of the next photon
};

static void photon_initialization(PHOTON *target, const PHOTON modele);
static int  photon_add( PHOTON values);
static void photon_delete( PHOTON *target);

static PHOTON *head_ph = NULL; //head for photons
static int nb_photon = 0;

_Bool photon_lecture(char * table)
{
	PHOTON values;
    int counter;
    counter = sscanf(table,"%lg %lg %lg", &values.p.x, &values.p.y,
										  &values.angle);

    if(photon_add(values))
		if(counter == PHOTON_NUM_ARGU)
			return 1;
		else //if there are not enough numbers or (unexpected) FIN_LISTE
			error_lecture_elements(ERR_PHOTON, ERR_PAS_ASSEZ);

	return 0;
}

int photon_get_tsize(void)
{
	return nb_photon;
}

_Bool photon_create_chain(int nb_elements)
{
	if(head_ph == NULL)
	{
		nb_photon = nb_elements;
		return 1;
	}
	error_msg("Error Memory Allocation for photons");
	return 0;
}

void photon_delete_chain(void) //temporary
{
	while(head_ph) //while head_ph != NULL
		photon_delete(head_ph);
}

_Bool photon_save(FILE* file_write)
{
    int i = 0;
    PHOTON* current = head_ph;

    fprintf(file_write, "%s", "#Photons\n");
    fprintf(file_write, "%s", "#Photon structure : position.x position.y angle\n");
    fprintf(file_write, "%d", nb_photon);
    for(i = 0; i < nb_photon && current != NULL; i++)
    {
        fprintf(file_write, "\n%lg %lg %lg", current->p.x, current->p.y,
											 current->angle);
        current = current->next;
	}
	if(i != nb_photon)
		printf("Info: Intern structure for photons invalid!\n"
				"We tried to save as much as possible.\n"
				"WE RECOMMEND TO RESTART THE PROGRAM\n");
    fprintf(file_write, "%s", "\nFIN_LISTE\n\n");

    return 1;
}

void photon_draw(void)
{
	int i = 0;
	const float black[3] = {0,0,0};
	PHOTON* current = head_ph;

	graphic_set_color3fv(black); // in black
	graphic_set_line_width(PHOTON_LINE_WIDTH);

	for (i = 0; i < nb_photon ; i++)
	{
		graphic_draw_circle(current->p.x, current->p.y,
                            EPSIL_PROJ/2, PHOTON_CIRCLE_NB_SIDES);
		current = current->next;
	}
}

static int photon_add( PHOTON values)
{
	PHOTON* new = NULL;

	if( !(new = (PHOTON*) malloc( sizeof(PHOTON))) )
	{
		error_msg(strcat("Error Allocation in %s", __func__));
		return 0; //submitting an error
	}

	//initialization of the PHOTON
	photon_initialization(new, values);

	//insertion of the new PHOTON in front of the chain
	new->next = head_ph;
	head_ph = new;

	return 1;
}

static void photon_delete(PHOTON *target)
{
	PHOTON *head = head_ph;
	if(head)
	{
		if( head->next == target->next )
		{
			head_ph = head->next;
			free(head);
		}
		else
		{
			PHOTON *previous = head;
			while( (previous->next != NULL) &&
			       (previous->next->next != target->next) )
				previous = previous->next;
			/* The loop will stop if we're at the end of the chain OR if
			   we have found the right photon */
			if(previous->next != NULL) // So we check that the loop stops
			{						   // for the reason desired
				PHOTON *to_delete = previous->next;
				previous->next = previous->next->next ;
				free (to_delete);
			}
		}
        nb_photon--;
	}
}

static void photon_initialization(PHOTON *target, const PHOTON modele)
{ /*initializes target with the values of modele
    but doesn't affect the pointer*/
	target->p.x   = modele.p.x;
	target->p.y   = modele.p.y;
	target->angle = modele.angle;
}

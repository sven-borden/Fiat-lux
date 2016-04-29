/*!
 \file modele.c
 \brief Module for lecture, simulation and other central operations
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.2
 \date 20 april 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilitaire.h"
#include "absorbeur.h"
#include "reflecteur.h"
#include "projecteur.h"
#include "photon.h"
#include "error.h"
#include "graphic.h"
#include "modele.h"

#define MAX_PT_REFELCTOR 2
#define MAX_PT_PROJECTOR 2
#define ZOOM_RECTANGLE_LINE_WIDTH 3

//counts the number of scanned elements, depending on number of elements
static void modele_next_step(int nb_elements, COUNTER counter, STEP * current_step);
//Finds out the next step to do
static void modele_back_to_num(STEP * old, int * i, int nb_elements);

const static char mode_tab[][12] = {"projector", "reflector", "absorber"};

int modele_lecture(const char * file_name)
{
	FILE* file_read = NULL;
	char table[MAX_LINE];
	STEP current_step = NUM;  //memorizes the next step to read the input
	COUNTER counter = PJ;  //counts which of the 4 objects we read in
	int i = 0;
	int nb_elements = 0;

	if(!(file_read = fopen(file_name, "r"))) //(try to) open the file
	{
		error_fichier_inexistant();
		return 0;
	}
	//main loop:
	while(fgets(table, MAX_LINE, file_read))  //reads lines until EOF
	{
		if(table[0] == '\n' || table[0] == '\r' || table[0] == '#')
            continue;		//ignores useless lines

		switch(current_step)  //examinates point of reading
		{
			case NUM :				//reads the number of elements
				if(sscanf(table,"%d", &nb_elements) !=1)
				{
					error_lect_nb_elements((ERREUR_ORIG)counter);
					return 0;
				}
				modele_next_step(nb_elements, counter, &current_step);
				i = 0;
				break;
			case PROJ :
			    if(!i) //first time --> new table
                    if(!projecteur_create_table(nb_elements))
						return 0;
				if(!projecteur_lecture(table, i))
                    return 0;
				modele_back_to_num(&current_step, &i, nb_elements);
				break;
			case REFL:
			    if(!i)
					if(!reflecteur_create_table(nb_elements))
						return 0;
				if(!reflecteur_lecture(table, i))
				    return 0;
				modele_back_to_num(&current_step, &i, nb_elements);
				break;
			case ABS:
			    if(!i)
                    if(!absorbeur_create_table(nb_elements))
						return 0;
				if(!absorbeur_lecture(table, i))
                    return 0;
				modele_back_to_num(&current_step, &i, nb_elements);
				break;
			case PHO:
				 if(!i)
                    if(!photon_create_chain(nb_elements))
						return 0;
				if(!photon_lecture(table))
                    return 0;
				modele_back_to_num(&current_step, &i, nb_elements);
				break;
			case END: //tests if really end of a bloc (FIN_LISTE?)
				if(strncmp("FIN_LISTE", table, 9))
				{ //if equal: 0 -> no error, else...
					error_lecture_elements(counter, ERR_TROP);
					return 0;
				}
				current_step = NUM;
				counter++;
				break;
			default:  //(=) case ENDF , that means, when there are still
					  //numbers after the FIN_LISTE of the photon-part
				error_msg("file is longer than expected");
				break;
		}
	}
	if(counter != OUT) //if EOF-line appears before the complete reading
		error_fichier_incomplet();
	fclose(file_read);  //closes the file
	return 1;
}

int modele_verification_rendu2(void)
{
	VECTEUR a1, a2, b1, b2, c1, c2;
	int i, j, k;
	int at_size = absorbeur_get_tsize();
	int rt_size = reflecteur_get_tsize();
	int pt_size = projecteur_get_tsize();
	_Bool countadd;
	
	absorbeur_get_lineseg(NULL, NULL, NULL, NULL, 1);
	for(i = 0; i < at_size;)
	{

		absorbeur_get_lineseg(&i, &a1, &a2, &countadd, 0);
		for(j = 0; j < rt_size;)
		{
			reflecteur_get_lineseg(&j, &b1, &b2);
			if(utilitaire_common_point(a1, a2, b1, b2))
			{
				error_lecture_intersection(ERR_ABSORBEUR,  i-countadd,
										   ERR_REFLECTEUR, j-1);
				return 0;
			}
			for(k = 0; k < pt_size;)
			{
				projecteur_get_lineseg(&k, &c1, &c2);
				if(utilitaire_common_point(c1, c2, b1, b2))
				{
					error_lecture_intersection(ERR_PROJECTEUR, k-1,
											   ERR_REFLECTEUR, j-1);
					return 0;
				}
				if(j == 1)
					if(utilitaire_common_point(c1, c2, a1, a2))
					{
						error_lecture_intersection(ERR_ABSORBEUR,  i-countadd,
												   ERR_PROJECTEUR, k-1);
						return 0;
					}
			}
		}
	}
	if(!reflecteur_verification())
		return 0;
	return 1;
}

void modele_update(void)  //demo-mode
{
	printf("modele_update is called.\n");
	printf("demo-function\n");
}

void modele_delete(void)
{
	absorbeur_delete_table();
	projecteur_delete_table();
	photon_delete_chain();
	reflecteur_delete_table();
}

void modele_save(const char* file_name)
{
    FILE* file_write = NULL;

	if(file_name == NULL || file_name[0] == '\0')
		error_msg("Erreur : impossible de créer un fichier de sauvegarde\n");

    if(!(file_write = fopen(file_name, "w"))) //(tries to) open the file
	{
		error_msg("Error to open the file to save");
		return;
	}

	if(!projecteur_save(file_write))
        error_msg("Error to save the projetors");
    if(!reflecteur_save(file_write))
        error_msg("Error to save the reflectors");
    if(!absorbeur_save(file_write))
        error_msg("Error to save the absorbers");
	if(!photon_save(file_write))
        error_msg("Error to save the photons");
	fclose(file_write);  //close File
}

int modele_find_nearest(int mode, int *element, double x_pos, double y_pos)
{ 						//demo-mode
	printf("modele_find_nearest in mode %s is called.\n", mode_tab[mode]);
	printf("demo-function\n");
	return 1;
}

void modele_delete_outside(double x_max, double x_min, //demo-mode
						   double y_max, double y_min)
{
	printf("modele_delete_outside is called.\n");
	printf("delete photons with x smaller %lf or bigger %lf\n", x_min, x_max);
	printf("delete photons with y smaller %lf or bigger %lf\n", y_min, y_max);
	printf("demo-function\n");
}

void modele_delete_selected(int mode, int element)   //demo-mode
{
	printf("modele_delete_selected is called.\n");
	printf("demo-function\n");
}

void modele_draw_element(int mode, double x_pos, double y_pos, int *beginnew)
{								//demo-mode
	static counter = 0;
	static VECTEUR p1 = {0, 0}; //remembers first element of a new element
	printf("modele_draw_element is called.\n");
	if(*beginnew)
	{
		*beginnew = 0;
		counter = 0;
		p1.x = x_pos;
		p1.y = y_pos;
	}
	counter++;
	printf("mode: %s, element: %d \n", mode_tab[mode], counter);
	switch(mode)
	{
		case PJ:
			if(counter == MAX_PT_PROJECTOR)
				*beginnew = 1;
			break;
		case RF:
			if(counter == MAX_PT_REFELCTOR)
				*beginnew = 1;
			break;
		case AS:
			if(counter == MAX_PT)
				*beginnew = 1;
			break;
	}
	printf("demo-function\n");
}

void modele_statistic(int statistic[4])
{
	statistic[PJ] = projecteur_get_tsize();
	statistic[RF] = reflecteur_get_tsize();
	statistic[AS] = absorbeur_get_tsize();
	statistic[PH] = photon_get_tsize();
}

void modele_draw(int click, double s_x, double s_y, double e_x, double e_y)
{
    const float black[3] = {0,0,0};
	projecteur_draw();
	reflecteur_draw();
	absorbeur_draw();
	photon_draw();
	if(click)
	{
		graphic_set_line_width(ZOOM_RECTANGLE_LINE_WIDTH);
		graphic_set_color3fv(black);
		graphic_draw_rectangle (s_x, s_y, e_x, e_y);
	}
}

void modele_error_cl(void)
{
	error_msg("Commande-Line arguments are invalid");
}

//controls the number of elements and finds out the next step
static void modele_next_step(int nb_elements, COUNTER counter,
	STEP * current_step)
{
	if(nb_elements < 0)
	{
		error_msg("negative number of elements");
		return;
	}
	else if(nb_elements > 0)
	{
		switch(counter)	//chooses next step (counter = next element to read)
		{
			case PJ:
				*current_step = PROJ;
				break;
			case RF:
				*current_step = REFL;
				break;
			case AS:
				*current_step = ABS;
				break;
			case PH:
				*current_step = PHO;
				break;
			default: //(=)case OUT:
				*current_step = ENDF;
				break;
		}
	}
	else //if 0, jumps directly to END-state
		*current_step = END;
}

//counts the number of scanned elements
//and changes the mode when enough elem. are read
static void modele_back_to_num(STEP * old, int * i, int nb_elements)
{
	++(*i);
	if(nb_elements == *i)
		*old = END;
}

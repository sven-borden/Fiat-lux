/*!
 \file reflecteur.h
 \brief Module which manages the reflectors
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.1
 \date 20 april 2016
 */

#ifndef REFLECTEUR_H
#define REFLECTEUR_H

//LECTURE OF THE REFLECTORS
//*table (string) equal to a line in the given file
_Bool reflecteur_lecture(char * table, int i);

//VERIFICATES THAT THERE ARE NO INTERSECTION BETWEEN REFLECTORS
_Bool reflecteur_verification(void);

//RETURNS THE NUMBER OF REFLECTORS(resp. the size of the table)
int   reflecteur_get_tsize(void);

//RETURNS THE 2 POINTS a & b OF A SEGMENT
void  reflecteur_get_lineseg(int *i, VECTEUR *a, VECTEUR *b);

//CREATES A TABLE FOR REFLECTORS (if necessary)
_Bool reflecteur_create_table(int nb_elements);

//DELETES THE TABLE (if the table exists)
void  reflecteur_delete_table(void);

//PRINTS THE TABLE IN A GIVEN FILE
int   reflecteur_save(FILE* file_write);

//(RE)DRAWS THE REFLECTORS (ALL!)
void  reflecteur_draw(void);

#endif

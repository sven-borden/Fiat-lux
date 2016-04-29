/*!
 \file projecteur.h
 \brief Module which manages the projectors
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.1
 \date 21 april 2016
 */

#ifndef PROJECTEUR_H
#define PROJECTEUR_H

//LECTURE OF THE PROJECTOR
//*table (string) equal to a line in the given file
_Bool projecteur_lecture(char * table, int i);

//RETURNS THE NUMBER OF PROJECTORS (resp. the size of the table)
int   projecteur_get_tsize(void);

//RETURNS THE 2 POINTS a & b OF A SEGMENT
void  projecteur_get_lineseg(int *i, VECTEUR *a, VECTEUR *b);

//CREATES A TABLE FOR PROJECTOR (if necessary)
_Bool projecteur_create_table(int nb_elements);

//DELETES THE TABLE (if the table exists)
void  projecteur_delete_table(void);

//PRINTS THE TABLE IN A GIVEN FILE
_Bool projecteur_save(FILE* file_write);

//(RE)DRAWS THE PROJECTORS (ALL!)
void  projecteur_draw(void);

#endif

/*!
 \file absorbeur.h
 \brief Module which manages the absorbers
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.1
 \date 19 april 2016
 */

#ifndef ABSORBEUR_H
#define ABSORBEUR_H

//LECTURE OF THE ABSORBER
//*table (string) equal to a line in the given file
_Bool absorbeur_lecture(char * table, int i);

//RETURNS THE NUMBER OF ABSORBERS (resp. the size of the table)
int   absorbeur_get_tsize(void);

//RETURNS THE 2 POINTS a & b OF A SEGMENT
//*i changes +1  when all segments are read --> next absorber
//*countadd helps to show the correct number in a case of an error:
//    i++, but a and b still from old "i": 1
//    else: 0
//set_back is there to set back the function when we load a new file
void  absorbeur_get_lineseg(int *i, VECTEUR *a, VECTEUR *b, _Bool *countadd,
							_Bool set_back);

//CREATES A TABLE FOR ABSORBERS (if necessary)
_Bool absorbeur_create_table(int nb_elements);

//DELETES THE TABLE (if the table exists)
void  absorbeur_delete_table(void);

//PRINTS THE TABLE IN A GIVEN FILE
int   absorbeur_save(FILE* file_write);

//(RE)DRAWS THE ABSORBERS (ALL!)
void  absorbeur_draw(void);

#endif

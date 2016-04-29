/*!
 \file photon.h
 \brief Module which manages the photons
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.1
 \date 19 april 2016
 */
#ifndef PHOTON_H
#define PHOTON_H

//LECTURE OF THE PHOTONS
//*table (string) equal a line in the given file
_Bool photon_lecture(char * table);

//RETURNS THE NUMBER OF PHOTONS
int   photon_get_tsize(void);

//just ALLOCATES THE MEMORY FOR THE CHAIN (if necessary)
_Bool photon_create_chain(int nb_elements);

//DELETES THE CHAIN
void  photon_delete_chain(void);

//PRINTS THE CHAIN IN A GIVEN FILE
_Bool photon_save(FILE* file_write);

//(RE)DRAWS THE PHOTONS (ALL!)
void  photon_draw(void);

#endif

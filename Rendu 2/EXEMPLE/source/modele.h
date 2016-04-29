/*!
 \file modele.h
 \brief Module for lecture, simulation and other central operations
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.2
 \date 20 april 2016
 */

#ifndef MODELE_H
#define MODELE_H

#include "constantes.h"

#define MODELE_NUM_ARGU 3 //Number of arguments

typedef enum Step {NUM, PROJ, REFL, ABS, PHO, END, ENDF} STEP;
typedef enum Counter {PJ, RF, AS, PH, OUT} COUNTER;
//Counter represents a higher level of abstraction than Step
//for example: (PJ: NUM -> PROJ -> END) -> (RF: NUM -> ...

//ORGANIZES THE READING of a given file
int modele_lecture(const char * file_name);

//ORGANIZES THE VERIFICATION in the table
int modele_verification_rendu2(void);

//UPDATES THE POSITION OF THE PHOTONS (RENDU FINAL)
void modele_update(void);

//ORGANIZES THE "PRINTING" of the actually state in a file
void modele_save(const char* file_name);

//ORGANIZES THE SUPRRESSION OF ALL TABLES
void modele_delete(void);

//FINDS THE NEAREST ELEMENT (RENDU FINAL)
int modele_find_nearest(int mode, int *element, double x_pos, double y_pos);

//DELETES THE ELEMENTS OUTSIDE OF THE FRAME
void modele_delete_outside(double x_max, double x_min, 
						   double y_max, double y_min);
						   
//DELETES THE LAST SELECTED ELEMENT
void modele_delete_selected(int mode, int element);

//DRAWS AN ELEMENT
//beginnew indicates if a new element should be begun
void modele_draw_element(int mode, double x_pos, double y_pos, int *beginnew);

//ASKS FOR NB_ELEMENTS in the different modules 
void modele_statistic(int statistic[4]);

//ORGANIZES THE DRAWING of all available objects
void modele_draw(int click, double s_x, double s_y, double e_x, double e_y);

//just CALLS ERROR-MESSAGE FOR COMMANDE-LINE ERRORS
//error itself appears in main.cpp, but main doesn't include error.h
void modele_error_cl(void);

#endif

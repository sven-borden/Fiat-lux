//-------------------------------------------------------------------------------
// sciper1: 261984
// nom1: Demeure
// prenom1: Eugénie
// sciper2: 261821
// nom2: Jullien
// prenom2: Sorya
// fichier: main.c
// date: 20.03.2016
// description du programme: projet PROG II Printempts 2015-16 EPFL MT-EL
//-------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modele.h"


// lit le fichier dont le nom est transmis sur la ligne de commande
int main(int argc, char * argv[])
{
	if(argc > 2) 
	{
		if(strcmp(argv[1], "Error") == 0) 
		{
			lecture_modele(argv[2]);
		}
	}
	return EXIT_SUCCESS;
}

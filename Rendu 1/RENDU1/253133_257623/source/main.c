/*
    Fichier:    main.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      16 mars 2016
    Version:    0.9
    Description:Point d'entree du projet 
*/

#include <stdio.h>
#include <stdlib.h>
#include "modele.h"

#define NB_ARG  3
#define ERROR   1

int main(int argc, char *argv[])
{
	if(argc == NB_ARG)
	{
		if(modeleLecture(argv[2]) == ERROR)
			EXIT_FAILURE;
		else
			EXIT_SUCCESS;
	}
	
	return 0;
}

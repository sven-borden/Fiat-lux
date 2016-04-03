/*
    Fichier:    modele.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      20 mars 2016
    Version:    0.9
    Description:Module de simulation du projet de Programation II MT 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "absorbeur.h"
#include "constantes.h"
#include "error.h"
#include "lecture.h"
#include "reflecteur.h"
#include "photon.h"
#include "projecteur.h"
#include "modele.h"


#define SUCCESS		0
#define ERROR		1

int modeleLecture(char fileName[MAX_FILE])
{
	if(lecture(fileName) == SUCCESS)
	{
		/* TODO TRUCS*/
	}
	else
		return ERROR;
}

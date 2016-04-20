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
		return SUCCESS;
	else
		return ERROR;
	return ERROR;
}

int modele_verification_rendu2(void)
{
	
	return SUCCESS;;	
}	

void modeleDestroy(void)
{

}

void modeleDraw()
{
	printf("modeleDraw\n");
	drawPhot();
	drawRefl();
	drawAbso();
	drawProj();
}

void modeleUpdate()
{
	drawPhot();
	drawRefl();
	drawAbso();
	drawProj();	
}

int modeleNbPhot(void) { return nbPhot(); }
int modeleNbRefl(void) { return nbRefl(); }
int modeleNbAbso(void) { return nbAbso(); }
int modeleNbProj(void) { return nbProj(); }

void modeleWrite(char * nom)
{
	FILE * file;

	if(!(file = fopen(nom, "w")))
		return ;
	
	/*ecriture photons*/
	fprintf(file, "#Fiat Lux Alix Nepveux & Sven Borden\n");
	fprintf(file, "#\n#fichier:\t%s\n#\n", nom);

	writeProjecteur(file);
	writeReflecteur(file);
	writeAbsorbeur(file);
	writePhoton(file);
	
	fclose(file);
}

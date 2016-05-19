/*
    Fichier:    modele.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      20 mars 2016
    Version:    1.1
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


#define SUCCESS		1
#define ERROR		0

int modeleLecture(char* fileName)
{
	if(lecture(fileName) == SUCCESS)
		return SUCCESS;
	else
		return ERROR;
	return ERROR;
}

int modele_verification_rendu2(void)
{
	if(interReflecteur() == ERROR)
		return ERROR;
	if(reflInterAbs() == ERROR)
		return ERROR;
	if(reflInterProj() == ERROR)
		return ERROR;
	if(projInterAbs() == ERROR)
		return ERROR;

	return SUCCESS;
}	

void modeleDestroy(void)
{
	delListPhoton();
	delListAbsorbeur();
	delListProjecteur();
	delListReflecteur();
}

void modeleDraw()
{
	drawPhot();
	drawRefl();
	drawAbso();
	drawProj();
}

void modeleUpdate()
{
	updateProjecteur();
	updatePhoton();
	modeleDraw();
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

void modeleDestroyEntity(void)
{
	printf("Destroy Entity NOT IMPLEMENTED YET\n");
}

void modeleDestroyExtPhot(double xmin, double xmax, double ymin, double ymax)
{
	delOutside(xmin, xmax, ymin, ymax);
}

void modeleSuccess(){ error_success(); }

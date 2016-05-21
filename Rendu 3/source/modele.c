/*
    Fichier:    modele.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      20 mars 2016
    Version:    1.1
    Description:Module de simulation du projet de Programation II MT 
*/

#include <math.h>
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

#define PROJECTEUR_VAL	0
#define REFLECTEUR_VAL	1
#define ABSORBEUR_VAL	2

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

void modeleSelect(int8_t val, double x, double y)
{
	switch(val)
	{
		case PROJECTEUR_VAL:
			selectProjecteur(x, y);
			unselectRefl();
			unselectAbso();
			break;
		case REFLECTEUR_VAL:
			selectReflecteur(x, y);
			unselectProj();
			unselectAbso();
			break;
		case ABSORBEUR_VAL:
			selectAbsorbeur(x, y);
			unselectProj();
			unselectRefl();
			break;
	}
}

void modeleCreation(short val, short nbPt, POINT tab[MAX_PT])
{
	double alpha;
	switch(val)
	{
		case PROJECTEUR_VAL:
			alpha = asin((tab[1].y - tab[0].y)/
						utilitaireDistance2Points(tab[1], tab[0]));
			if(nbPt == 2)
				addProjecteur(tab[0], alpha);
			break;
		case REFLECTEUR_VAL:
			if(nbPt == 2)
				addReflecteur(tab[0], tab[1]);
			break;
		case ABSORBEUR_VAL:
			break; 
	}
	return ;
}

void modeleUnselect(void)
{
	unselectProj();
	unselectRefl();
	unselectAbso();
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

void modeleDestroyEntity(short entity)
{
	switch(entity)
	{
		case PROJECTEUR_VAL:
			projDelSelect();
			break;
		case REFLECTEUR_VAL:
			reflDelSelect();
			break;
		case ABSORBEUR_VAL:
			absoDelSelect();
			break;
	}
}

void modeleDestroyExtPhot(double xmin, double xmax, double ymin, double ymax)
{
	delOutside(xmin, xmax, ymin, ymax);
}

void modeleSuccess(){ error_success(); }

/*
	Fichier:	modele.c
	Auteur:		Alix Nepveux & Sven Borden
	Date :		20 mars 2016
	Version:	1.0
	Description:Module de simulation du projet de programation II MT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "absorbeur.h"
#include "constantes.h"
#include "error.h"
#include "reflecteur.h"
#include "photon.h"
#include "projecteur.h"
#include "lecture.h"

#define SUCCESS		0
#define ERROR		1
#define KEEP		0
#define SKIP		1
#define FINLISTE	2
#define NB_CMP		9
#define FIN_LISTE	"FIN_LISTE"

static int lectureProj(FILE *);
static int lectureRefl(FILE *);
static int lectureAbs(FILE *);
static int lecturePhot(FILE *);
static int skipLine(char[]);

int lecture(char fileName[MAX_FILE])
{
	FILE *pFile;
	pFile = fopen(fileName, "r");
	if(pFile == NULL)
	{
		error_fichier_inexistant();
		return ERROR;
	}

	if(lectureProj(pFile) != SUCCESS)
		return ERROR;
	if(lectureRefl(pFile) != SUCCESS)
		return ERROR;
	if(lectureAbs(pFile) != SUCCESS)
		return ERROR;
	if(lecturePhot(pFile)!= SUCCESS)
		return ERROR;
	printListPhoton();
	error_success();
	fclose(pFile);
	return SUCCESS;
}

static int lectureProj(FILE *pFile)
{
	char line[MAX_LINE];
	int nb = 0, i = 0;
	
	while(fgets(line, MAX_LINE, pFile) != NULL)
	{
		if(skipLine(line) == SKIP)
			continue;
		sscanf(line, "%d", &nb);
		if(nb < 0)
		{
			error_lect_nb_elements(ERR_PROJECTEUR);
			return ERROR;
		}
		break;
	}
	while(i < nb)
	{
		if(fgets(line, MAX_LINE, pFile) != NULL)
		{
			switch(skipLine(line))
			{
				case SKIP:		continue;
				case FINLISTE:	
					error_lecture_elements(ERR_PROJECTEUR, 
						ERR_PAS_ASSEZ);
					return ERROR;
			}
			if(projecteurSet(line) != SUCCESS)
				return ERROR;
			i++;
		}
		else
		{
			error_fichier_incomplet();
			return ERROR;
		}
	}
	if(fgets(line, MAX_LINE, pFile) == NULL)
	{
		error_fichier_incomplet();
		return ERROR;
	}
	if(strncmp(line, FIN_LISTE, NB_CMP) == 0)
		return SUCCESS;
	error_lecture_elements(ERR_PROJECTEUR, ERR_TROP);
	return ERROR;

}

static int lectureRefl(FILE *pFile)
{
	char line[MAX_LINE];
	int nb = 0, i = 0;
	
	while(fgets(line, MAX_LINE, pFile) != NULL)
	{
		if(skipLine(line) == SKIP)
			continue;
		sscanf(line, "%d", &nb);
		if(nb < 0)
		{
			error_lect_nb_elements(ERR_REFLECTEUR);
			return ERROR;
		}
		break;
	}
	while(i < nb)
	{
		if(fgets(line, MAX_LINE, pFile) != NULL)
		{
			switch(skipLine(line))
			{
				case SKIP:		continue;
				case FINLISTE:	
					error_lecture_elements(ERR_REFLECTEUR, 
						ERR_PAS_ASSEZ);
					return ERROR;
			}
			if(reflecteurSet(line) != SUCCESS)
				return ERROR;
			i++;
		}
		else
		{
			error_fichier_incomplet();
			return ERROR;
		}
	}
	if(fgets(line, MAX_LINE, pFile) == NULL)
	{
		error_fichier_incomplet();
		return ERROR;
	}
	if(strncmp(line, FIN_LISTE, NB_CMP) == 0)
		return SUCCESS;
	error_lecture_elements(ERR_REFLECTEUR, ERR_TROP);
	return ERROR;
}	

static int lectureAbs(FILE *pFile)
{
	char line[MAX_LINE];
	int nb = 0, i = 0;
	
	while(fgets(line, MAX_LINE, pFile) != NULL)
	{
		if(skipLine(line) == SKIP)
			continue;
		sscanf(line, "%d", &nb);
		if(nb < 0)
		{
			error_lect_nb_elements(ERR_PROJECTEUR);
			return ERROR;
		}
		break;
	}
	while(i < nb)
	{
		if(fgets(line, MAX_LINE, pFile) != NULL)
		{
			switch(skipLine(line))
			{
				case SKIP:		continue;
				case FINLISTE:	
					error_lecture_elements(ERR_ABSORBEUR, 
						ERR_PAS_ASSEZ);
					return ERROR;
			}
			if(absorbeurSet(line) != SUCCESS)
				return ERROR;
			i++;
		}
		else
		{
			error_fichier_incomplet();
			return ERROR;
		}
	}
	if(fgets(line, MAX_LINE, pFile) == NULL)
	{
		error_fichier_incomplet();
		return ERROR;
	}
	if(strncmp(line, FIN_LISTE, NB_CMP) == 0)
		return SUCCESS;
	error_lecture_elements(ERR_ABSORBEUR, ERR_TROP);
	return ERROR;

}

static int lecturePhot(FILE *pFile)
{
	char line[MAX_LINE];
	int nb = 0, i = 0;
					
	while(fgets(line, MAX_LINE, pFile) != NULL)
	{
		if(skipLine(line) == SKIP)
			continue;
		sscanf(line, "%d", &nb);
		if(nb < 0)
		{
			error_lect_nb_elements(ERR_PHOTON);
			return ERROR;
		}
		break;
	}
	while(i < nb)
	{
		if(fgets(line, MAX_LINE, pFile) != NULL)
		{
			switch(skipLine(line))
			{
				case SKIP:		continue;
				case FINLISTE:	
					error_lecture_elements(ERR_PHOTON, 
						ERR_PAS_ASSEZ);
					return ERROR;
			}
			if(photonSet(line) != SUCCESS)
				return ERROR;
			i++;
		}
		else
		{
			error_fichier_incomplet();
			return ERROR;
		}
	}
	if(fgets(line, MAX_LINE, pFile) == NULL)
	{
		error_fichier_incomplet();
		return ERROR;
	}
	if(strncmp(line, FIN_LISTE, NB_CMP) == 0)
		return SUCCESS;
	error_lecture_elements(ERR_PHOTON, ERR_TROP);
	return ERROR;

}

static int skipLine(char line[MAX_LINE])
{
	if(!strncmp(line, FIN_LISTE, NB_CMP))
		return FINLISTE;
	
	if(line[0] == '#' || line[0] == '\n' || line[0] == '\r')
		return SKIP;
	else
		return KEEP;
}

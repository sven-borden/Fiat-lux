#include <stdio.h>
#include <stdlib.h>
#include "absorbeur.h"
#include "reflecteur.h"
#include "photon.h"
#include "projecteur.h"
#include "error.h"

#define SUCCESS 0
#define ERROR	1
#define KEEP	0
#define SKIP	1
#define FINLISTE 2

int readProj(FILE *);
int readRefl(FILE *);
int readAbs(FILE *);
int readPhot(FILE *);
int skipLine(char[]);

int modeleLecture(char fileName[80])
{

	FILE *pFile;
	pFile = fopen(fileName, "r");
	
	if(pFile == NULL)
	{
		error_fichier_inexistant();
		return ERROR;
	}
	
	readProj(pFile);	
	readRefl(pFile);
	readAbs(pFile);
	readPhot(pFile);
	
	error_success();
	return SUCCESS;
}

int readProj(FILE *pFile)
{
	char line[130];
	int nb = 0, i = 0;
	
	while(fgets(line, 130, pFile) != NULL)
	{
		if(skipLine(line) == SKIP)
			continue;
		/*lecture du nbProj*/
		sscanf(line, "%d", &nb);
		break;
	}
	/*lecture des Proj*/
	while(i < nb)
	{
		if(fgets(line, 130, pFile) != NULL)
		{
			switch(skipLine(line))
			{
				case SKIP:	continue;
				case FINLISTE: //TODO ERROR FINLISTE
						return ERROR;
			}

			if(sscanf("%lf %lf %lf", &tabProjecteur[i].pos.x, 
				&tabProjecteur[i].pos.y, &tabProjecteur[i].alpha) != 3)
			error_lecture_elements();
			i++;
		}
		else	{ error_fichier_incomplet(); }
	}
	fgets(line, 130, pFile)
	if(line == "FINLISTE")
		return SUCCESS;
	error_lecture_elements();
	return ERROR;
}

int readRefl(FILE *pFile)
{

}

int readAbs(FILE *pFile)
{

}

int readPhot(FILE *pFile)
{

}

int skipLine(char line[130])
{
	if(line == "FIN_LISTE")
		return FINLISTE;
	
	if(line[0] == '#' || line[0] == '\n' || line[0] == '\r')
		return SKIP;
	else
		return KEEP;
}

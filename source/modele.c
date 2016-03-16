/*
    Autheur: Alix Nepveux & Sven Borden
    Date : 16 mars 2016
    Version: 0.9
*/

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

			if(sscanf(line, "%lf %lf %lf", &tabProjecteur[i].pos.x, 
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
    char line[130];
    int nb = 0, i = 0;
    
    while(fgets(line, 130, pFile) != NULL)
    {
        if(skipLine(line) == SKIP)
            continue;
        /*lecture du nbRefl*/
        sscanf(line, "%d", &nb);
        break;
    }
    /*lecture des refl*/
    while(i < nb)
    {
        if(fgets(line, 130, pFile) != NULL)
        {
            switch(skipLine(line))
            {
                case SKIP: continue;
                case FINLISTE: //TODO ERROR FINLISTE   
                    return ERROR;
            }
            
            if(sscanf(line, "%lf %lf %lf %lf", &tabReflecteur[i].a.x,
                &tabReflecteur[i].a.y, &tabProjecteur[i].b.x, 
                &tabProjecteur.b.y) != 4)
            error_lecture_elements();
            
            i++;
        }
        else    { error_fichier_incomplet(); }
    }
    fgets(line, 130, pFILE)
    if(line == "FINLISTE")
        return SUCCESS;
    error_lecture_elements();
    return ERROR;
}

int readAbs(FILE *pFile)
{
    char line[130];
    int nb = 0, i = 0;
    int nbPts = 0;
    while(fgets(line, 130, pFile) != NULL)
    {
        if(skipLine(line) == SKIP)
            continue;
        /*lecture du nbAbs*/
        sscanf(line, "%d", &nb);
        break;
    }
    
    /*lecture des abs*/
    while(i < nb)
    {
        if(fgets(line, 130, pFile) != NULL)
        {
            switch(skipLine(line))
            {
                case SKIP: continue;
                case FINLISTE: //TODO ERROR FINLISTE
                    return ERROR;
            }
            
            
        }
    }
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

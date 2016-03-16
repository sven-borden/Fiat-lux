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
	
	if(readProj(pFile) != SUCCESS)
        return ERROR;	
	if(readRefl(pFile) != SUCCESS)
        return ERROR;
	if(readAbs(pFile) != SUCCESS)
        return ERROR;
	if(readPhot(pFile)!= SUCCESS)
        return ERROR;
	
	error_success();
	return SUCCESS;
}

int readProj(FILE *pFile)
{
	char line[MAX_LINE];
	int nb = 0, i = 0;
    POINT pos;
	double alpha = 0.0;
	while(fgets(line, MAX_LINE, pFile) != NULL)
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
		if(fgets(line, MAX_LINE, pFile) != NULL)
		{
			switch(skipLine(line))
			{
				case SKIP:	continue;
				case FINLISTE: //TODO ERROR FINLISTE
						return ERROR;
			}

			if(sscanf(line, "%lf %lf %lf", &pos.x, &pos.y, &alpha) != 3)
			    error_lecture_elements();
                
            setProjecteur(pos, alpha);
			i++;
		}
		else	{ error_fichier_incomplet(); }
	}
	fgets(line, MAX_LINE, pFile)
	if(line == "FINLISTE")
		return SUCCESS;
	error_lecture_elements();
	return ERROR;
}

int readRefl(FILE *pFile)
{
    char line[MAX_LINE];
    int nb = 0, i = 0;
    POINT a, b;
    
    while(fgets(line, MAX_LINE, pFile) != NULL)
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
        if(fgets(line, MAX_LINE, pFile) != NULL)
        {
            switch(skipLine(line))
            {
                case SKIP: continue;
                case FINLISTE: //TODO ERROR FINLISTE   
                    return ERROR;
            }
            
            if(sscanf(line, "%lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y) != 4)
                error_lecture_elements();
            setReflecteur(a, b);
            
            i++;
        }
        else    { error_fichier_incomplet(); }
    }
    fgets(line, MAX_LINE, pFILE);
    if(line == "FIN_LISTE")
        return SUCCESS;
    error_lecture_elements();
    return ERROR;
}

int readAbs(FILE *pFile)
{
    char line[MAX_LINE];
    int nb = 0, i = 0, j = 0, nbPts = 0;
    POINT points[MAX_PT];
    char* start = NULL, end = NULL;
    
    while(fgets(line, MAX_LINE, pFile) != NULL)
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
        if(fgets(line, MAX_LINE, pFile) != NULL)
        {
            switch(skipLine(line))
            {
                case SKIP: continue;
                case FINLISTE: //TODO ERROR FINLISTE
                    return ERROR;
            }
            
            nbPts = (int)strtod(line, &end);
            start = end;
            
            for(j = 0; j < nbPts; j++)
            {
                points[j].x = strtod(&start, &end);
                if(start == end)
                    ;//call error
                start = end;
                points[j].y = strtod(&start, &end);
                if(start == end)
                    ;//call error
                start = end;
            }
            
            setAbsorbeur(nbPts, points);
            i++;
        }
        else    {error_fichier_incomplet(); }
    }
    fgets(line, MAX_LINE, pFile);
    if(line == "FIN_LISTE")
        return SUCCESS;
    error_lecture_elements();
    return ERROR;    
}

int readPhot(FILE *pFile)
{
    char line[MAX_LINE];
    int nb = 0, i = 0;
    POINT pos;
    double alpha;
    
    while(fgets(line, MAX_LINE, pFile) != NULL)
    {
        if(skipLine(line) == SKIP)
            continue;
        /*lecture du phot*/
        sscanf(line, "%d", &nb);
        break;
    }
    /*lecture des photon*/
    while(i < nb)
    {
        if(fgets(line, MAX_LINE, pFile) != NULL)
        {
            switch(skipLine(line))
            {
                case SKIP: continue;
                case FINLISTE: //TODO ERROR FINLISTE
                    return ERROR;
            }
            
            if(sscanf(line, "%lf %lf %lf", &pos.x, &pos.y, &alpha) != 3)
                error_lecture_elements();
            setPhoton(pos, alpha);
            
            i++;
        }
        else    { error_fichier_incomplet(); }
    }
    fgets(line, MAX_LINE, pFile);
    if(line == "FIN_LISTE")
        return SUCCESS;
    error_lecture_elements();
    return ERROR;
}

int skipLine(char line[MAX_LINE])
{
	if(line == "FIN_LISTE")
		return FINLISTE;
	
	if(line[0] == '#' || line[0] == '\n' || line[0] == '\r')
		return SKIP;
	else
		return KEEP;
}

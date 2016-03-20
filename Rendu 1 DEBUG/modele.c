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
#include "constantes.h"
#include <string.h>

#define SUCCESS 	0
#define ERROR		1
#define KEEP		0
#define SKIP		1
#define FINLISTE 	2


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
#ifdef DEBUG          
	printf("\nPROJ SUCCESS\n\n");
#endif
	if(readRefl(pFile) != SUCCESS)
        	return ERROR;
#ifdef DEBUG            
	printf("\nREFL SUCCESS\n\n");
#endif
	if(readAbs(pFile) != SUCCESS)
	        return ERROR;
#ifdef DEBUG
	printf("\nABSO SUCCESS\n\n");
#endif
	if(readPhot(pFile)!= SUCCESS)
	        return ERROR;
#ifdef DEBUG
	printf("\nPHOT SUCCESS\n\n");
#endif
	
	error_success();
	return SUCCESS;
}

int readProj(FILE *pFile)
{
#ifdef DEBUG
	printf("IN %s, LINE %d\n", __func__, __LINE__);
#endif
	char line[MAX_LINE];
	int nb = 0, i = 0;
    
	while(fgets(line, MAX_LINE, pFile) != NULL)
	{
		if(skipLine(line) == SKIP)
			continue;
		/*lecture du nbProj*/
		sscanf(line, "%d", &nb);
#ifdef DEBUG
		printf("IN %s, LINE %d\tnb = %d\n", __func__, __LINE__, nb);
#endif
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
				case FINLISTE:
                    	error_lecture_elements(ERR_PROJECTEUR, ERR_PAS_ASSEZ);
					return ERROR;
			}
#ifdef DEBUG
            printf("IN %s, LINE %d\tSetting Projecteur\n", __func__, __LINE__);
#endif
			if(setProjecteur(line) != SUCCESS)
                return ERROR;
                
			i++;
		}
		else
		{ 
            		error_fichier_incomplet();
            		return ERROR; 
	    }
	}
#ifdef DEBUG
    printf("IN %s, LINE %d\nEND OF PROJ\n", __func__, __LINE__);
#endif
	fgets(line, MAX_LINE, pFile);
	skipLine(line);
	if(strncmp(line, "FIN_LISTE", 9) == 0)
		return SUCCESS;
    error_lecture_elements(ERR_PROJECTEUR, ERR_TROP);
	return ERROR;
}

int readRefl(FILE *pFile)
{
#ifdef DEBUG
	printf("IN %s, LINE %d\n", __func__, __LINE__);
#endif

    char line[MAX_LINE];
    int nb = 0, i = 0;
        
    while(fgets(line, MAX_LINE, pFile) != NULL)
    {
        if(skipLine(line) == SKIP)
            continue;
        /*lecture du nbRefl*/
        sscanf(line, "%d", &nb);
#ifdef DEBUG
		printf("IN %s, LINE %d\tnb = %d\n", __func__, __LINE__, nb);
#endif
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
                case FINLISTE:  
                    error_lecture_elements(ERR_PROJECTEUR, ERR_PAS_ASSEZ);
					return ERROR;
            }
#ifdef DEBUG
            printf("IN %s, LINE %d\tSetting Reflecteur\n", __func__, __LINE__);
#endif
            if(setReflecteur(line) != SUCCESS)
		        return ERROR;
            
            i++;
        }
        else	
        { 
            error_fichier_incomplet();
            return ERROR; 
        }
    }
#ifdef DEBUG
	printf("IN %s, LINE %d\nEND OF REFL\n", __func__, __LINE__);
#endif
    fgets(line, MAX_LINE, pFile);
    if(strncmp(line, "FIN_LISTE", 9) == 0)
		return SUCCESS;
    error_lecture_elements(ERR_REFLECTEUR, ERR_TROP);
    return ERROR;
}

int readAbs(FILE *pFile)
{
#ifdef DEBUG
	printf("IN %s, LINE %d\n", __func__, __LINE__);
#endif

    char line[MAX_LINE];
    int nb = 0, i = 0;

	 
    while(fgets(line, MAX_LINE, pFile) != NULL)
    {
        if(skipLine(line) == SKIP)
            continue;
        /*lecture du nbAbs*/
        sscanf(line, "%d", &nb);
#ifdef DEBUG
		printf("IN %s, LINE %d\tnb = %d\n", __func__, __LINE__, nb);
#endif
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
                case FINLISTE:
                    error_lecture_elements(ERR_ABSORBEUR, ERR_PAS_ASSEZ);
					return ERROR;
            }
#ifdef DEBUG
            printf("IN %s, LINE %d\tSetting Absorbeur\n", __func__, __LINE__);
#endif
            if(setAbsorbeur(line) != SUCCESS)
                return ERROR;
            i++;
        }
        else	
        { 
            error_fichier_incomplet();
            return ERROR; 
        }
    }
#ifdef DEBUG
	printf("IN %s, LINE %d\nEND OF ABS\n", __func__, __LINE__);
#endif
    fgets(line, MAX_LINE, pFile);
    if(strncmp(line, "FIN_LISTE", 9) == 0)
		return SUCCESS;
    error_lecture_elements(ERR_ABSORBEUR, ERR_TROP);
    return ERROR;    
}

int readPhot(FILE *pFile)
{
#ifdef DEBUG
	printf("IN %s, LINE %d\n", __func__, __LINE__);
#endif

    char line[MAX_LINE];
    int nb = 0, i = 0;
    
    while(fgets(line, MAX_LINE, pFile) != NULL)
    {
        if(skipLine(line) == SKIP)
            continue;
        /*lecture du phot*/
        sscanf(line, "%d", &nb);
#ifdef DEBUG
		printf("IN %s, LINE %d\tnb = %d\n", __func__, __LINE__, nb);
#endif
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
                case FINLISTE: 
                    error_lecture_elements(ERR_PHOTON, ERR_PAS_ASSEZ);
					return ERROR;
            }
#ifdef DEBUG
            printf("IN %s, LINE %d\tSetting Photon\n", __func__, __LINE__);
#endif
            if(setPhoton(line) != SUCCESS)
                return ERROR;
            
            i++;
        }
        else	
        { 
            error_fichier_incomplet();
            return ERROR; 
        }
    }
#ifdef DEBUG
	printf("IN %s, LINE %d\nEND OF PHOT\n", __func__, __LINE__);
#endif
    fgets(line, MAX_LINE, pFile);
    if(strncmp(line, "FIN_LISTE", 9) == 0)
		return SUCCESS;
    error_lecture_elements(ERR_PHOTON, ERR_TROP);
    return ERROR;
}

int skipLine(char line[MAX_LINE])
{
	printf("%s", line);
	if(!strncmp(line, "FIN_LISTE", 10))
{
		printf("DETECTED FINLISTE\n");
		return FINLISTE;
}
	
	if(line[0] == '#' || line[0] == '\n' || line[0] == '\r')
	{
		printf("SKIP\n");
		return SKIP;
}
	else
	{
		printf("KEEP\n");
		return KEEP;
}
}


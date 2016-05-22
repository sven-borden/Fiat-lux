/*
    Fichier:    projecteur.c
    Auteur:     Alix Nepveux & Sven Borden
    Date :      20 mai 2016
    Version:    1.5
    Description:Module projecteur qui gere la structure
*/
/* identité :
 * cos(alpha + PI/2) = -sin(alpha)
 * sin(alpha + PI/2) =  cos(alpha)*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "absorbeur.h"
#include "constantes.h"
#include "error.h"
#include "graphic.h"
#include "photon.h"
#include "utilitaire.h"
#include "projecteur.h"

#define OK      	1
#define NO      	0
#define NB_ELEM 	3
#define PROJ_VAL	1
#define SELECT		1
#define UNSELECT	0
#define NONE		65353
typedef struct Projecteur PROJECTEUR;

struct Projecteur
{
	POINT pos;
	double alpha;
	unsigned int id;
	PROJECTEUR * next;
};

static int n = 0;
static unsigned int lastId = 0;
static unsigned int idSelected = NONE;
static PROJECTEUR * list;

int projecteurSet(char line[MAX_LINE])
{
	POINT pt;
	double  alpha = 0;
	if(sscanf(line, "%lf %lf %lf", &pt.x, &pt.y, &alpha) != NB_ELEM)
	{
		error_lecture_elements(ERR_PROJECTEUR, ERR_PAS_ASSEZ);
		return NO;
	}

	addProjecteur(pt, alpha);
	return OK;
}

int addProjecteur(POINT _pt, double _alpha)
{
	/*Crée un nouveau projecteur*/
	PROJECTEUR *p = (PROJECTEUR *) malloc(sizeof(PROJECTEUR));
	if(p!= NULL)
	{
		p->pos.x = _pt.x;
		p->pos.y = _pt.y;
		p->alpha = _alpha;
		p->id 	 = lastId;
		if(list != NULL)
			p->next = list;
		else
			p->next = NULL;
		list = p;
		lastId++;
		n++;
		
	}	
	else
	{
		free(p);
		p = NULL;
	}
	return (p != NULL);//retourne 1 (vrai) si est différent de NULL
}

int delProjecteur(int _id)
{
	if(n == 0)
		return OK;
	PROJECTEUR *p = list;
	if(p)
	{
		if(p->id == _id)
		{
			list = list->next;
			free(p);
		}
		else
		{
			PROJECTEUR *prec = p;
			while(prec->next && prec->next->id != _id)
				prec = prec->next;
			if(prec->next)
			{
				PROJECTEUR * del = prec->next;
				prec->next = prec->next->next;
				free(del);
				del = NULL;
			}
		}
	}
	n--;
	return OK;
}

void delProjTete(void)
{
	delProjecteur(list->id);
}

void drawProj(void)
{
	PROJECTEUR *p = list;
	while(p != NULL)
	{
		if(p->id == idSelected)
			graphicDrawProjecteur(p->pos, p->alpha, SELECT);
		else
			graphicDrawProjecteur(p->pos, p->alpha, UNSELECT);
		p = p->next;
	}
}

void selectProjecteur(double x, double y)
{
	PROJECTEUR *p = list;
	POINT pt;	pt.x = x;	pt.y = y;
	unsigned int tmpId = 0;
	double norme, normeMin = NONE;
	POINT fin;
	while(p)
	{
		fin.x = (-sin(p->alpha)*(NBPH-1)*EPSIL_PROJ) + p->pos.x;
		fin.y = (cos(p->alpha)*(NBPH-1)*EPSIL_PROJ) + p->pos.y;
		norme = utilitaireDistance2Points(p->pos, pt);
		if(norme < normeMin)
		{
			normeMin = norme;
			tmpId = p->id;
		}
		norme = utilitaireDistance2Points(fin, pt);
		if(norme < normeMin)
		{
			normeMin = norme;
			tmpId = p->id;
		}
		p = p->next;
	}
	idSelected = tmpId;
}

void unselectProj(void){	idSelected = NONE;	}

void projDelSelect(void)
{
	delProjecteur(idSelected);
	idSelected = NONE;
}

void writeProjecteur(FILE * file)
{
	PROJECTEUR *p = list;
	fprintf(file, "#projecteur\n%d\n", n);
	while(p != NULL)
	{
		fprintf(file, "%lf %lf %lf\n", p->pos.x, p->pos.y, p->alpha);
		p = p->next;
	}
	fprintf(file, "FIN_LISTE\n\n");
}

void printListProjecteur(void)
{
	PROJECTEUR *p = list;
	int i = 1;
	while(p != NULL)
	{
		printf("Projecteur %d\tx = %lf\ta.y = %lf\talpha = %lf\n",
			i, p->pos.x, p->pos.y, p->alpha);
		p = p->next;
		i++;
	}
	return ;
}

int projecteurExt(VECTOR v, int idV)
{
	PROJECTEUR * p = list;
	VECTOR vp;
	POINT *inter;
	while(p != NULL)
	{
		vp.ptDeb.x = p->pos.x;
		vp.ptDeb.y = p->pos.y;
		vp.ptFin.x = (-sin(p->alpha)*(NBPH-1)*EPSIL_PROJ) + p->pos.x;
		vp.ptFin.y = (cos(p->alpha)*(NBPH-1)*EPSIL_PROJ) + p->pos.y;

		inter = utilitaireIntersection(v, vp);
		if(inter != NULL)
		{
			error_lecture_intersection(ERR_PROJECTEUR, p->id, ERR_REFLECTEUR, idV);
			return NO;
		}
		p = p->next;
	}
	return OK;
}

int projInterAbs(void)
{
	PROJECTEUR *p = list;
	VECTOR v;
	while(p != NULL)
	{
		v.ptDeb.x = p->pos.x;
		v.ptDeb.y = p->pos.y;
		v.ptFin.x = (-sin(p->alpha)*(NBPH-1)*EPSIL_PROJ) + p->pos.x;
		v.ptFin.y = (cos(p->alpha)*(NBPH-1)*EPSIL_PROJ) + p->pos.y;

		if(absorbeurExt(v, p->id, PROJ_VAL) == NO)
			return NO;
		p = p->next;
	}	
	return OK;
}

void delListProjecteur(void)
{
	while(list)
	{
		PROJECTEUR *p = list;
		list = p->next;
		free(p);
	}
	n = 0;
	return ;
}

int nbProj(void) { return n; }

void updateProjecteur()
{
	PROJECTEUR *p = list;
	int i = 0;
	double portionX = 0; double portionY = 0;
	POINT pt;
	while(p)
	{
		/*crées les NBPH sur chaque proj*/
		portionX = (-sin(p->alpha)*(NBPH)*EPSIL_PROJ)/NBPH;
		portionY = (cos(p->alpha)*(NBPH)*EPSIL_PROJ)/NBPH;
		for(i = 0; i < NBPH; i++)
		{
			pt.x = portionX*i + p->pos.x;
			pt.y = portionY*i + p->pos.y;
			addPhoton(pt, p->alpha);
		}	
		p = p->next;
	}
}

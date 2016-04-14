#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "absorbeur.h"
#include "constantes.h"
#include "error.h"
#include "modele.h"
#include "photon.h"
#include "projecteur.h"
#include "reflecteur.h"
#include "utilitaire.h"
#define NB_LETTRES 9


// traite le fichier ligne par ligne.
int lecture_modele( char * nom_fichier)
{
	char tab[MAX_LINE];
	int erreur = 0;
	FILE * fichier = NULL;
	if((fichier = fopen (nom_fichier, "r")) != NULL) 
	{
		while(fgets(tab, MAX_LINE, fichier) != NULL)
		{
			// lignes à ignorer, on passe à la suivante
			if((tab[0]=='#')||(tab[0]=='\n')||(tab[0]=='\r')) continue; 
			erreur = decodage_ligne(tab);
			if(erreur == 1)
			{
				fclose(fichier);
				return 1;
			}
		}
		
		if(strncmp(tab, "FIN_LISTE", NB_LETTRES) != 0)
		{
			error_fichier_incomplet();
			fclose(fichier);
			return 1;
		}
		/*if(fgets(tab, MAX_LINE, fichier) == NULL)
		{
			error_fichier_incomplet();
			fclose(fichier);
			return 1;
		}*/
		fclose(fichier);
		error_success();
		return 0;
	}
	else 
	{
		fclose(fichier);
		error_fichier_inexistant();
		return 1;
	}
}



// décodage selon l'etat courant d'une ligne lue dans le fichier 
// met à jour l'etat
int decodage_ligne(char * tab)
{
	// états de l'automate de lecture
	enum Etat_lecture {NB_PR, PROJECTEUR, NB_R, REFLECTEUR, NB_A, ABSORBEUR, 
					   NB_PH, PHOTON, FIN_LISTE};
	static int etat = NB_PR; // état initial
	static int nb_pr = 0, nb_r = 0, nb_a = 0, nb_ph = 0; 
	int *ptr_nb_pr = &nb_pr, *ptr_nb_r = &nb_r;
	int *ptr_nb_a = &nb_a, *ptr_nb_ph = &nb_ph;
	static int i = 0, j = 0;
	int erreur = 0;

	
	switch(etat) 
	{
	case NB_PR: 
		erreur = decodage_nb_pr(tab, ptr_nb_pr);
		i = 0;
		if(erreur == 1) return 1;
		else if(*ptr_nb_pr == 0) etat = FIN_LISTE; 
		else etat = PROJECTEUR; 
		break;
	case PROJECTEUR: 
		erreur = projecteur(tab, i);
		++i;
		if(erreur == 1) return 1;
		else if(i == *ptr_nb_pr) etat = FIN_LISTE;
		break;
	case NB_R: 
		erreur = decodage_nb_r(tab, ptr_nb_r);
		i = 0;
		if(erreur == 1) return 1;
		else if(*ptr_nb_r == 0) etat = FIN_LISTE; 
		else etat = REFLECTEUR; 
		break;
	case REFLECTEUR: 
		erreur = reflecteur(tab, i);
		++i;
		if(erreur == 1) return 1;
		else if(i == *ptr_nb_r) etat = FIN_LISTE;
		break;
	case NB_A:
		erreur = decodage_nb_a(tab, ptr_nb_a);
		i = 0 ;
		if(erreur == 1) return 1;
		else if(*ptr_nb_a == 0) etat = FIN_LISTE; 
		else etat = ABSORBEUR;
		break;
	case ABSORBEUR:
		erreur = absorbeur(tab, i);
		++i; 
		if(erreur == 1) return 1;
		else if(i == *ptr_nb_a) etat = FIN_LISTE;
		break;
	case NB_PH: 
		erreur = decodage_nb_ph(tab, ptr_nb_ph);
		i = 0 ;
		if(erreur == 1) return 1;
		else if(*ptr_nb_ph == 0) etat = FIN_LISTE; 
		else etat = PHOTON;
		break;
	case PHOTON:
		erreur = photon(tab, i);
		++i;
		if(erreur == 1) return 1;	
		else if(i == *ptr_nb_ph) etat = FIN_LISTE;
		break;
	case FIN_LISTE:
		if(strncmp(tab, "FIN_LISTE", NB_LETTRES) == 0)
		{
			j++;
			if(j == 1) etat = NB_R;
			if(j == 2) etat = NB_A;
			if(j == 3) etat = NB_PH;
			if(j == 4) return 0;
		}
		else 
		{
			if(j == 0) 
			{
				error_lecture_elements(ERR_PROJECTEUR, ERR_TROP); 
				return 1;
			}
			if(j == 1)
			{
				 error_lecture_elements(ERR_REFLECTEUR, ERR_TROP);
				 return 1;
			}
			if(j == 2) 
			{
				error_lecture_elements(ERR_ABSORBEUR, ERR_TROP);
				return 1;
			}
			if(j == 3) 
			{
				error_lecture_elements(ERR_PHOTON, ERR_TROP); 
				return 1;
			}
		}
		break;
	default: 
		error_fichier_incomplet();
		return 1;
	}
	return 0;
} 

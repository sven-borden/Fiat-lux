#include "projecteur.h"

void projecteur (char* ligne, int numero)
{
	int i =0;
    if(numero>=MAX_RENDU1)
        error_lecture_elements(ERR_PROJECTEUR, ERR_TROP);
    if(numero<0)
        error_lecture_elements(ERR_PROJECTEUR, ERR_PAS_ASSEZ);
    
    if(sscanf(ligne, "%lf %lf %lf", &(tab_p[numero].x), &(tab_p[numero].y), &(tab_p[numero].alpha))!=3)
        error_fichier_incomplet();
    }

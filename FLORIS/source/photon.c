#include "photon.h"

void photon (char* ligne, int numero)
{
   if(numero>=MAX_RENDU1)
        error_lecture_elements(ERR_PROJECTEUR, ERR_TROP);
    if(numero<0)
        error_lecture_elements(ERR_PROJECTEUR, ERR_PAS_ASSEZ);
    
    if(sscanf(ligne, "%lf %lf %lf", &(tab_f[numero].x), &(tab_f[numero].y), &(tab_f[numero].alpha))!=3)
        error_fichier_incomplet();
}
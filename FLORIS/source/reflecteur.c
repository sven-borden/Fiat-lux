#include "reflecteur.h"

void reflecteur (char* ligne, int numero)
{
    double x1=0, y1=0, x2=0, y2=0;
    
    if (sscanf(ligne, "%lf %lf %lf %lf", &x1, &y1, &x2, &y2)!=4)
        error_fichier_incomplet();
    
    if (numero>MAX_RENDU1)
        error_lecture_elements(ERR_REFLECTEUR, ERR_TROP);
    if (numero<0)
        error_lecture_elements(ERR_REFLECTEUR, ERR_PAS_ASSEZ);
    
    if (sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))<EPSIL_CREATION)
            error_lecture_point_trop_proche(ERR_REFLECTEUR, numero);
    
    tab_r[numero].x1=x1;
    tab_r[numero].y1=y1;
    tab_r[numero].x2=x2;
    tab_r[numero].y2=y2;
}

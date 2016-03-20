#include "absorbeur.h"

void absorbeur (char* ligne, int numero)
{
    int nbP=0;
    
    if (sscanf(ligne, "%d", &nbP)==1)
    {
        int i=0;
        char *deb=ligne, *fin=NULL;
        strtod(deb, &fin);
        while (i<nbP)
        {
            if (sscanf(deb, "%lf %lf", &(tab_a[numero][i].x), &(tab_a[numero][i].y))==2)
            {
                strtod(deb, &fin);
                deb=fin;
            }
            else error_fichier_incomplet();
            i++;
        }
        
    }
}

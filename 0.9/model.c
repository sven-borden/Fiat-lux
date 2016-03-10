#include "model.h"
#include "reflector.h"
#include "emmit.h"
#include "photon.h"
#include "absorbor.h"


void modeleLecture()
{
    char line[MAX_LINE];
    char *deb = tab, 
    *fin=NULL;
    int nb, x, sum=0, i=0;
    FILE *fichier = fopen("", "r");//a completer pour le fichier de rendu 1 %TODO%%
    if(fichier)
    {
        while(fgets(tab, MAX_LINE, fichier)!=NULL)
        {
            if(sscanf(line, "%d", &nb)==1)
            {
                
                strtod(deb, &fin, 0); deb = fin;
                while(i < nb)
                {
                    if(sscanf(deb, "%d", &x)=1)
                    {
                        sum
                    }
                }
            }
        }
    }
}
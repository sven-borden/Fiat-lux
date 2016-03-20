#include "modele.h"


void modele_lecture(char *nomDuFichier)
{
    int etat=NB0;
    int i=0, total=0;
    
    FILE* fichier = NULL;
    char ligne[MAX_LINE] = {0};
    
    printf("*****************Avant boucle lecture***************** \n");
    if((fichier = fopen(nomDuFichier, "r")))
	{
		printf("*****************Dans boucle lecture*****************\n");
		while (fgets(ligne, MAX_LINE, fichier)!=NULL)
        {
            if ((ligne[0]=='#')||(ligne[0]=='\n')||(ligne[0]=='\r'))
                continue;
            switch (etat)
            {
                case NB0:
                    if (sscanf(ligne, "%d", &total)!=1) error_fichier_incomplet(); i=0; printf("*****************Nb0*****************\n");
                    if (total<0)
                        error_lect_nb_elements(ERR_PROJECTEUR);
                    if(total==0 ){
						fgets(ligne, MAX_LINE, fichier);
						if (strcmp(ligne,"FIN_LISTE"))
							etat=NB1;
						else error_fichier_incomplet();
					}
                    else etat=PROJECTEUR;
                    break;
                    
                case PROJECTEUR:
                    projecteur(ligne, i);
                    i++;
                    if((i==total) && (strcmp(ligne, "FIN_LISTE"))) etat=NB1;
                    break;
                    
                case NB1:
                    if (sscanf(ligne, "%d", &total)!=1){ error_fichier_incomplet(); i=0;printf("*****************Nb1*****************\n"); printf("%d \n", total);}

                    if (total<0)
                        error_lect_nb_elements(ERR_REFLECTEUR);
                    if(total==0 ){
						fgets(ligne,MAX_LINE, fichier);
						if (strcmp(ligne,"FIN_LISTE"))
							etat=NB2;
						else error_fichier_incomplet();
					}
                    else etat=REFLECTEUR;
                    break;
                    
                case REFLECTEUR:
                    reflecteur(ligne, i);
                    i++;
                    if((i==total) && (strcmp(ligne, "FIN_LISTE"))) etat=NB2;
                    break;
                    
                case NB2:
                    if (sscanf(ligne, "%d", &total)!=1) error_fichier_incomplet(); i=0;printf("*****************Nb2*****************\n");
                    if (total<0)
                        error_lect_nb_elements(ERR_ABSORBEUR);
                    if(total==0 ){
						fgets(ligne,MAX_LINE, fichier);
						if (strcmp(ligne,"FIN_LISTE"))
							etat=NB3;
						else error_fichier_incomplet();
					}
                    else etat=ABSORBEUR;
                    break;
                    
                case ABSORBEUR:
                    absorbeur(ligne, i);
                    i++;
                    if((i==total) && (strcmp(ligne, "FIN_LISTE"))) etat=NB3;
                    break;
                    
                case NB3:
                    if (sscanf(ligne, "%d", &total)!=1) error_fichier_incomplet(); i=0;printf("*****************Nb3*****************\n");
                    if (total<0)
                        error_lect_nb_elements(ERR_PHOTON);
                    if(total==0 ){
						fgets(ligne,MAX_LINE, fichier);
						if (strcmp(ligne,"FIN_LISTE"))
							etat=NB4;
						else error_fichier_incomplet();
					}
                    else etat=PHOTON;
                    break;
                    
                case PHOTON:
                    photon(ligne, i);
                    i++;
                    if((i==total) && (strcmp(ligne, "FIN_LISTE"))) etat=NB4;
                    break;
                
                case NB4:
                    fclose(fichier);
                    return;
            }
        }
    }
    else error_fichier_inexistant();
    return 0;
}

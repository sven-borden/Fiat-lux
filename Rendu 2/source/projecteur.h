/*
	Fichiers:	projecteur.h
	Autheurs:	Alix Nepveux & Sven Borden
	Date:		10 Avril 2016
	Description:Module projecteur qui gere la structure
*/

#ifndef PROJECTEUR_H
#define PROJECTEUR_H

int projecteurSet(char[]);
int addProjecteur(POINT, double);/*ajoute un projecteur dans la liste*/
int delProjecteur(int);/*supprime un projecteur de la liste*/
void printListProjecteur(void);/*imprime la liste des projecteurs*/
void delListReflecteur(void);/*nettoie la memoire*/
#endif

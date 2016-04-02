/*!
 \file error.c
 \brief Module qui gère les messages d'erreur. NE PAS MODIFIER
 \author PROG II
 \version 0.9
 \date 29 fevrier 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

// chaînes prédéfinies pour composer les messages d'erreur

const static char nom_orig[][20] = {"projecteur", "reflecteur", "absorbeur", 
									"photon"};
const static char nom_type[][20] = {"trop", "pas assez"};

//---------------------------------------------------------------------
// utilisable pour afficher des messages d'erreurs qui ne font pas
// partie de la liste des erreurs testées pour le rendu1
void error_msg(char * msg) {
    printf("erreur : %s\n", msg);
    exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------
// Erreurs testées en mode Error pour le rendu1 (et les rendus suivants)
//   ----> le paramètre indice commence à zéro

//---------------------------------------------------------------------
// A appeler pour le rendu1 en mode Error en cas d'absence d'erreur
void error_success(void) {
    printf("Fichier correct\n");
}

//---------------------------------------------------------------------
// impossible d'ouvrir le fichier, fichier inexistant
void error_fichier_inexistant(void) {
    printf("Erreur : Fichier inexistant\n");
}

//---------------------------------------------------------------------
// si la lecture d'une ligne du fichier échoue (on reçoit EOF)
// alors que la lecture des entités n'est pas terminée
void error_fichier_incomplet(void) {
    printf("Erreur : Fichier incomplet (EOF inattendu)\n");
}


//---------------------------------------------------------------------
// échec lecture du nombre d'élément: projecteur,reflecteur,absorbeur,photon
void error_lect_nb_elements(ERREUR_ORIG origine) {
    printf("Erreur : lecture du nb de %s\n", nom_orig[origine]);
}

//---------------------------------------------------------------------
// A appeler si le nombre de points d'un absorbeur est incorrect: ce nombre
// doit être supérieur ou égal à 2 et inférieur ou égal à MAX_PT
void error_lect_nb_points_absorbeur(void) {
    printf("Erreur : valeur interdite du nb de points"
		   " d'un absorbeur [2,MAX_PT]\n");
}	

//---------------------------------------------------------------------
// échec de la lecture des paramètres : trop, pas assez ou syntaxe
//
// REMARQUE1: pour l'absorbeur, on utilise cette fonction seulement pour 
// signaler une erreur de lecture d'une coordonnée d'un point
// REMARQUE2: on récupère seulement le nombre de points indiqué en début de
// ligne. s'il y a plus de coordonnées que nécessaire on les ignore sans 
// afficher de message d'erreur
void error_lecture_elements(ERREUR_ORIG origine, ERREUR_TYPE type) {
    printf("Erreur : lecture de %s : %s ou erreur de syntaxe\n",
           nom_orig[origine], nom_type[type]);
}

//---------------------------------------------------------------------
// échec de la lecture des paramètres : intersection entre 2 éléments
// IMPORTANT: la valeur des entiers element_id est de type "indice de
//            tableau". Elle est comprise entre 0 et nb_element-1
//
void error_lecture_intersection(ERREUR_ORIG element1, int element1_id,
                                ERREUR_ORIG element2, int element2_id) {
    printf("Erreur : le %s (id: %d) coupe le %s (id: %d).\n", 
		   nom_orig[element1], element1_id, nom_orig[element2], 
		   element2_id);
}

//---------------------------------------------------------------------
// échec de la lecture des paramètres : le dernier point lu est trop 
// proche du précédent. On fournit l'id du dernier point lu.
// IMPORTANT: la valeur de l'entier id est de type "indice de
//            tableau". Elle est comprise entre 0 et nb_element-1
//
void error_lecture_point_trop_proche(ERREUR_ORIG origine, int id) {
    printf("Erreur : lecture de %s (id: %d): point trop proche\n",
           nom_orig[origine], id);
}

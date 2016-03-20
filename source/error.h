/*!
 \file error.h
 \brief Module qui gère les messages d'erreur. NE PAS MODIFIER
 \author PROG II
 \version 0.9
 \date 16 fevrier 2016
 */

#ifndef ERROR_H
#define ERROR_H

//---------------------------------------------------------------------
// ces déclarations combinent deux outils du langage C : enum et typedef
// enum : déclare une liste de symboles équivalents à des entiers
//        le premier symbole vaut 0, le suivant vaut 1, etc...
// typedef : the nom de type rend le code plus lisible

//---------------------------------------------------------------------
// liste des symboles à utiliser pour appeler les fonctions d'erreur
// selon l'entité qui produit l'erreur
typedef enum ErreurOrig {
    ERR_PROJECTEUR, ERR_REFLECTEUR, ERR_ABSORBEUR, ERR_PHOTON
} ERREUR_ORIG;

//---------------------------------------------------------------------
// liste des symboles à utiliser pour appeler les fonctions d'erreur
// pour les cas où on a trop ou pas assez d'entité dans la liste
typedef enum ErreurType {
    ERR_TROP, ERR_PAS_ASSEZ
} ERREUR_TYPE;

// exemple d'appel: echec de la lecture des paramètres d'un photon
// le symbole ERR_PAS_ASSEZ est aussi utilisé en cas d'erreur de syntaxe
// car le programme ne peut pas faire la différence entre les deux cas.
//
// error_lecture_elements(ERR_PHOTON , ERR_PAS_ASSEZ)

//---------------------------------------------------------------------
// cette fonction est utilisable pour afficher des messages d'erreurs
// qui ne font pas partie de la liste des erreurs testées pour le rendu1
void error_msg(char * msg);

//---------------------------------------------------------------------
// Erreurs testées en mode Error pour le rendu1 (et les rendus suivants)
//   ----> le paramètre indice commence à zéro

//---------------------------------------------------------------------
// A appeler pour le rendu1 en mode Error en cas d'absence d'erreur
void error_success(void);

//---------------------------------------------------------------------
// impossible d'ouvrir le fichier, fichier inexistant
void error_fichier_inexistant(void);

//---------------------------------------------------------------------
// si la lecture d'une ligne du fichier échoue (on reçoit EOF)
// alors que la lecture des entités n'est pas terminée
void error_fichier_incomplet(void);

//---------------------------------------------------------------------
// échec lecture du nombre d'élément: projecteur,reflecteur,absorbeur,photon
void error_lect_nb_elements(ERREUR_ORIG origine);

//---------------------------------------------------------------------
// A appeler si le nombre de points d'un absorbeur est incorrect: ce nombre
// doit être supérieur ou égal à 2 et inférieur ou égal à MAX_PT
void error_lect_nb_points_absorbeur(void);

//---------------------------------------------------------------------
// échec de la lecture des paramètres : trop, pas assez ou syntaxe
//
// REMARQUE1: pour l'absorbeur, on utilise cette fonction seulement pour 
// signaler une erreur de lecture d'une coordonnée d'un point
// REMARQUE2: on récupère seulement le nombre de points indiqué en début de
// ligne. s'il y a plus de coordonnées que nécessaire on les ignore sans 
// afficher de message d'erreur

void error_lecture_elements(ERREUR_ORIG origine, ERREUR_TYPE type);

//---------------------------------------------------------------------
// échec de la lecture des paramètres : le dernier point lu est trop 
// proche du précédent. On fournit l'id du dernier point lu.
// IMPORTANT: la valeur de l'entier id est de type "indice de
//            tableau". Elle est comprise entre 0 et nb_element-1
//
void error_lecture_point_trop_proche(ERREUR_ORIG origine, int id);

//---------------------------------------------------------------------
// Erreur testée en mode Verification pour le rendu2 (et les suivants)
//   ----> le paramètre indice commence à zéro
//---------------------------------------------------------------------
// échec de la lecture des paramètres : intersection entre 2 éléments
// IMPORTANT: la valeur des entiers element_id est de type "indice de
//            tableau". Elle est comprise entre 0 et nb_element-1
//
void error_lecture_intersection(ERREUR_ORIG element1, int element1_id,
                                ERREUR_ORIG element2, int element2_id);


#endif


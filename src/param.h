/*
param.h
Définition des paramètres général du jeu ainsi que de l'IG
*/

#ifndef param
#define param

    #define TAILLE_BLOC         180 // Taille d'un bloc (carré) en pixels
    #define NB_BLOCS_LARGEUR    7 // 6 blocs pour le plateau + 1 pour les scores à droite
    #define NB_BLOCS_HAUTEUR    2 // 2 blocs de hauteur pour le plateau
    #define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR // Plus sur pour avoir une largeur adaptée
    #define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR //Pareil pour la hauteur

#endif
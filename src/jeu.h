#ifndef jeu
#define jeu


#include "param.h"
#include "jeu.h"
#include "awale.h"
#include "affichage_console.h"
#include "IA.h"

/*
Permet d'actualiser l'affichage des graines présentent sur le plateau
*/
void actualiser_graine(Plateau *p, SDL_Rect positionGraine, SDL_Surface* graine_init, SDL_Surface* plateau,SDL_Surface* ecran);

/*
Génération de l'écran de victoire pour la fin de la partie
*/
void victoire(int joueur,SDL_Surface* ecran);

/*
Permet d'actualiser l'affichage des scrores sur l'écran
*/
void actualiser_score(Stock *s, SDL_Rect positionScore, SDL_Surface* score_init, SDL_Surface* plateau,SDL_Surface* ecran,int current_player,int next_player);

/*
Permet de lancer la partie sur le plateau
*/
void jouer(SDL_Surface* ecran);


/*
Permet de lancer une partie joueur vs IA avec un niveau de difficulté
*/
void jouer_vs_IA(SDL_Surface* ecran,Difficulte diff);
    
#endif
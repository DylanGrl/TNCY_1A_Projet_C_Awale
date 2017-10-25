#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "param.h"
#include "jeu.h"
#include "awale.h"
#include "IA.h"
#include "affichage_console.h"

void actualiser_graine(Plateau *p, SDL_Rect positionGraine, SDL_Surface* graine_init, SDL_Surface* plateau,SDL_Surface* ecran){
    //Initialisation des graines sur le plateau
    int j;
    //SDL_SetAlpha(graine_init, SDL_SRCALPHA,0);
    for(j=0;j<6;j++){
        //Graine Joueur 2 -> Sens lecture plateau
        positionGraine.x = 900-(180*j);
        positionGraine.y = 0;
        char graine_j2[100];
        sprintf(graine_j2,"img/Graine/graine_%d.bmp",p->joueur_2[j]);
        graine_init = SDL_LoadBMP(graine_j2);
        //SDL_SetColorKey(graine_init, SDL_SRCCOLORKEY, SDL_MapRGB(graine_init->format, 161, 115, 44));
        SDL_BlitSurface(graine_init, NULL, plateau, &positionGraine);

        //Graine Joueur 1 -> Sens lecture plateau
        positionGraine.x = 180*j;
        positionGraine.y = 180;
        char graine_j1[100];
        sprintf(graine_j1,"img/Graine/graine_%d.bmp",p->joueur_1[j]);
        graine_init = SDL_LoadBMP(graine_j1);
        //SDL_SetColorKey(graine_init, SDL_SRCCOLORKEY, SDL_MapRGB(graine_init->format,  161, 115, 44));
        SDL_BlitSurface(graine_init, NULL, plateau, &positionGraine);

    }
    SDL_Flip(ecran);
}

void victoire(int joueur,SDL_Surface* ecran)
{
    
    ecran = NULL;
    SDL_Surface *plateau = NULL;
    SDL_Rect positionplateau;
    SDL_Event event;
    int x;
    int y;


    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    //Ajout d'une icone
    //SDL_WM_SetIcon(IMG_Load("icon.jpg"), NULL); 
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //Ajout d'un titre
    SDL_WM_SetCaption("Partie terminée", NULL);
    //Définition d'une image pour l'ecran :
    char resultat[100];
    sprintf(resultat,"img/Screen/win_screen_%d.bmp",joueur);
    plateau = SDL_LoadBMP(resultat);

    positionplateau.x = 0;
    positionplateau.y = 0;



    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            //GESTION DE LA CROIX POUR FERMER
            case SDL_QUIT:
                continuer = 0;
                break;
            //GESTION DES TOUCHES CLAVIER
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                        continuer = 0;
                        break;
                    case SDLK_RETURN:
                        continuer = 0;
                        break;
                }
                break;
        }

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(plateau, NULL, ecran, &positionplateau);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(plateau);
    SDL_FreeSurface(ecran);
    SDL_Quit();
}
void actualiser_score(Stock *s, SDL_Rect positionScore, SDL_Surface* score_init, SDL_Surface* plateau,SDL_Surface* ecran,int current_player,int next_player){
    //Initialisation des scores sur le plateau
    //JOUEUR 2
    positionScore.x = 1080;
    positionScore.y = 0;
    char pseudo_j2[100];
    if(current_player==2){
        sprintf(pseudo_j2,"img/Joueur/Joueur2_turn.bmp"); 
    }
    else{
        sprintf(pseudo_j2,"img/Joueur/Joueur2_wait.bmp"); 
    }
    score_init = SDL_LoadBMP(pseudo_j2);
    SDL_BlitSurface(score_init, NULL, plateau, &positionScore);

    positionScore.x = 1080;
    positionScore.y = 90;
    char score_j2[100];
    sprintf(score_j2,"img/Score/Score_%d.bmp",s->stock_j2);
    score_init = SDL_LoadBMP(score_j2);
    SDL_BlitSurface(score_init, NULL, plateau, &positionScore);

    //JOUEUR 1
    positionScore.x = 1080;
    positionScore.y = 180;
    char pseudo_j1[100];
    if(current_player==1){
        sprintf(pseudo_j1,"img/Joueur/Joueur1_turn.bmp"); 
    }
    else{
        sprintf(pseudo_j1,"img/Joueur/Joueur1_wait.bmp"); 
    }

    score_init = SDL_LoadBMP(pseudo_j1);
    SDL_BlitSurface(score_init, NULL, plateau, &positionScore);

    positionScore.x = 1080;
    positionScore.y = 270;
    char score_j1[100];
    sprintf(score_j1,"img/Score/Score_%d.bmp",s->stock_j1);
    score_init = SDL_LoadBMP(score_j1);
    SDL_BlitSurface(score_init, NULL, plateau, &positionScore);

    if(s->stock_j1 >= 24){
      printf("Victoire Joueur 1 !!\n");
      victoire(1,ecran);
    }
    if(s->stock_j2 >= 24){
      printf("Victoire Joueur 2 !!\n");
      victoire(2,ecran);
    }

    SDL_Flip(ecran);
}


void jouer(SDL_Surface* ecran)
{
    Plateau * p;
    p = (Plateau*)(malloc(sizeof(Plateau)));
    Stock * s;
    s= (Stock*)(malloc(sizeof(Stock)));
    int * j1;
    j1 = (int*)(malloc(sizeof(int)*6));
    int * j2;
    j2 = (int*)(malloc(sizeof(int)*6));
    p->joueur_1 = j1;
    p->joueur_2 = j2;
    remplissage(p,s);

    ecran = NULL;
    SDL_Surface *plateau = NULL, *fond=NULL, *bg=NULL, *graine_init=NULL,*score_init=NULL;
    SDL_Rect positionplateau;
    SDL_Event event;
    int x;
    int y;
    srand(time(NULL));
    SDL_Rect positionGraine;

    positionGraine.x = 0;
    positionGraine.y = 0;


    SDL_Rect positionScore;

    positionScore.x = 0;
    positionScore.y = 0;


    //Polices
    TTF_Font *police = NULL;
    TTF_Font *policev = NULL;
    TTF_Font *policec = NULL;
    TTF_Font *policep = NULL; //bouton play
    


    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    //Ajout d'une icone
    //SDL_WM_SetIcon(IMG_Load("icon.jpg"), NULL); 
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //Ajout d'un titre
    SDL_WM_SetCaption("Awale - Partie en cours - J1 vs J2", NULL);
    //Définition d'une image pour le plateau :
    plateau = SDL_LoadBMP("img/Screen/Plateau.bmp");

    positionplateau.x = 0;
    positionplateau.y = 0;


    int rand_player=(rand()%2)+1;
    int current_player,next_player;
    if(rand_player == 1){
        current_player = 1;
        next_player = 2;
    }
    else{
        current_player = 2;
        next_player = 1;
    }
    printf("Le joueur %d commence !\n",current_player);
    actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);

    //play_a_turn(1,3,p,s);
    //actualiser_graine(p,positionGraine,graine_init,plateau,ecran);


    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        	//GESTION DE LA CROIX POUR FERMER
            case SDL_QUIT:
                continuer = 0;
                break;
            //GESTION DES TOUCHES CLAVIER
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                        continuer = 0;
                        break;
                    case SDLK_KP1: // Demande à jouer
		                    printf("Coup aléatoire !\n");
                        srand(time(NULL));
                        int rand_player=rand()%2+1;
                        int rand_case = rand()%5+1;
                        play_a_turn(rand_player,rand_case,p,s);
                        actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                        actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
                        break;
                    case SDLK_RETURN:
		                  printf("Actualisation plateau + scores\n");
                      actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                      actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
		                  break;
                }
                break;
            //GESTION DES CLICKS
            case SDL_MOUSEBUTTONUP:
            	x = event.button.x;
            	y = event.button.y;
            	if(x>=0 && x<180 && y>=0 && y<180 && current_player ==2 ){
            		printf("Click Joueur 2 -> Case 6\n");
                    play_a_turn(2,5,p,s);
                    actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
            	}
            	if(x>=0 && x<180 && y>=180 && y<360 && current_player ==1){
            		printf("Click Joueur 1 -> Case 1\n");
                    play_a_turn(1,0,p,s);
                      actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
            	}
            	if(x>=180 && x<360 && y>=0 && y<180 && current_player ==2){
            		printf("Click Joueur 2 -> Case 5\n");
                    play_a_turn(2,4,p,s);
                      actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
            	}
            	if(x>=180 && x<360 && y>=180 && y<360 && current_player ==1){
            		printf("Click Joueur 1 -> Case 2\n");
                    play_a_turn(1,1,p,s);
                      actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
            	}
            	if(x>=360 && x<540 && y>=0 && y<180 && current_player ==2){
            		printf("Click Joueur 2 -> Case 4\n");
                    play_a_turn(2,3,p,s);
                      actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
            	}
            	if(x>=360 && x<540 && y>=180 && y<360 && current_player ==1){
            		printf("Click Joueur 1 -> Case 3\n");
                    play_a_turn(1,2,p,s);
                      actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
            	}
            	if(x>=540 && x<720 && y>=0 && y<180 && current_player ==2){
            		printf("Click Joueur 2 -> Case 3\n");
                    play_a_turn(2,2,p,s);
                      actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
            	}
            	if(x>=540 && x<720 && y>=180 && y<360 && current_player ==1){
            		printf("Click Joueur 1 -> Case 4\n");
                    play_a_turn(1,3,p,s);
                      actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
            	}
            	if(x>=720 && x<900 && y>=0 && y<180 && current_player ==2){
            		printf("Click Joueur 2 -> Case 2\n");
                    play_a_turn(2,1,p,s);
                      actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
            	}
            	if(x>=720 && x<900 && y>=180 && y<360 && current_player ==1){
            		printf("Click Joueur 1 -> Case 5\n");
                    play_a_turn(1,4,p,s);
                    actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
            	}
            	if(x>=900 && x<1080 && y>=0 && y<180 && current_player ==2){
            		printf("Click Joueur 2 -> Case 1\n");
                    play_a_turn(2,0,p,s);
                      actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                   actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
            	}
            	if(x>=900 && x<1080 && y>=180 && y<360 && current_player == 1){
            		printf("Click Joueur 1 -> Case 6\n");
                    play_a_turn(1,5,p,s);
                    actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                   actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
            	}
            	break;
        }

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(plateau, NULL, ecran, &positionplateau);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(plateau);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(bg);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(graine_init);
    SDL_FreeSurface(plateau);
    SDL_FreeSurface(score_init);

    SDL_Quit();
}

void jouer_vs_IA(SDL_Surface* ecran,Difficulte diff){
    Plateau * p;
    p = (Plateau*)(malloc(sizeof(Plateau)));
    Stock * s;
    s= (Stock*)(malloc(sizeof(Stock)));
    int * j1;
    j1 = (int*)(malloc(sizeof(int)*6));
    int * j2;
    j2 = (int*)(malloc(sizeof(int)*6));
    p->joueur_1 = j1;
    p->joueur_2 = j2;
    remplissage(p,s);

    ecran = NULL;
    SDL_Surface *plateau = NULL, *fond=NULL, *bg=NULL, *graine_init=NULL,*score_init=NULL;
    SDL_Rect positionplateau;
    SDL_Event event;
    int x;
    int y;
    srand(time(NULL));
    SDL_Rect positionGraine;

    positionGraine.x = 0;
    positionGraine.y = 0;


    SDL_Rect positionScore;

    positionScore.x = 0;
    positionScore.y = 0;

    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    //Ajout d'une icone
    //SDL_WM_SetIcon(IMG_Load("icon.jpg"), NULL); 
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //Ajout d'un titre
    SDL_WM_SetCaption("Awale - Partie en cours - J1 vs IA", NULL);
    //Définition d'une image pour le plateau :
    plateau = SDL_LoadBMP("img/Screen/Plateau.bmp");

    positionplateau.x = 0;
    positionplateau.y = 0;


    int rand_player=(rand()%2)+1;
    int current_player,next_player;
    if(rand_player == 1){
        current_player = 1;
        next_player = 2;
    }
    else{
        current_player = 2;
        next_player = 1;
    }
    printf("Le joueur %d commence !\n",current_player);
    actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);

    //play_a_turn(1,3,p,s);
    //actualiser_graine(p,positionGraine,graine_init,plateau,ecran);


    while (continuer)
    {
        int cas[11];
        int i;
        for(i=0;i<6;i++){
            cas[i] = p->joueur_1[i];
            cas[i+6] = p->joueur_2[i];
        }
        if(current_player == 2){
          int case_to_play = IA(p,diff);
          if(case_to_play==-1){
            victoire(1,ecran);
          }
          play_a_turn(2,case_to_play,p,s);
          actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
          int tmp = current_player;
          current_player = next_player;
          next_player = tmp;
          actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
        }
        SDL_WaitEvent(&event);
        switch(event.type)
        {
          //GESTION DE LA CROIX POUR FERMER
            case SDL_QUIT:
                continuer = 0;
                break;
            //GESTION DES TOUCHES CLAVIER
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                        continuer = 0;
                        break;
                }
                break;
            //GESTION DES CLICKS
            case SDL_MOUSEBUTTONUP:
              x = event.button.x;
              y = event.button.y;
              

              
              if(x>=0 && x<180 && y>=180 && y<360 && current_player ==1){
                printf("Click Joueur 1 -> Case 1\n");
                if(check_playable_case(0,cas,1)){
                    play_a_turn(1,0,p,s);
                      actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
              }}
              
              if(x>=180 && x<360 && y>=180 && y<360 && current_player ==1){
                printf("Click Joueur 1 -> Case 2\n");
                if(check_playable_case(1,cas,1)){
                    play_a_turn(1,1,p,s);
                      actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
              }}
             
              if(x>=360 && x<540 && y>=180 && y<360 && current_player ==1){
                printf("Click Joueur 1 -> Case 3\n");
                if(check_playable_case(2,cas,1)){
                    play_a_turn(1,2,p,s);
                      actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
              }}
              
              if(x>=540 && x<720 && y>=180 && y<360 && current_player ==1){
                printf("Click Joueur 1 -> Case 4\n");
                if(check_playable_case(3,cas,1)){
                    play_a_turn(1,3,p,s);
                      actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
              }}
              if(x>=720 && x<900 && y>=180 && y<360 && current_player ==1){
                printf("Click Joueur 1 -> Case 5\n");
                if(check_playable_case(4,cas,1)){
                    play_a_turn(1,4,p,s);
                    actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                    actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
              }}
              if(x>=900 && x<1080 && y>=180 && y<360 && current_player == 1){
                printf("Click Joueur 1 -> Case 6\n");
                if(check_playable_case(5,cas,1)){
                    play_a_turn(1,5,p,s);
                    actualiser_graine(p,positionGraine,graine_init,plateau,ecran);
                    int tmp = current_player;
                    current_player = next_player;
                    next_player = tmp;
                   actualiser_score(s,positionScore,score_init,plateau,ecran,current_player,next_player);
              }}
              break;
        }

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(plateau, NULL, ecran, &positionplateau);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(plateau);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(bg);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(graine_init);
    SDL_FreeSurface(plateau);
    SDL_FreeSurface(score_init);
    SDL_Quit();
}
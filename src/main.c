#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "param.h"
#include "jeu.h"
#include "IA.h"

int main(int argc, char *argv[])
{
  SDL_Surface *ecran = NULL, *menu = NULL, *fond=NULL, *bg=NULL;
    SDL_Rect positionMenu;
    SDL_Event event;


    


    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    //Ajout d'une icone
    //SDL_WM_SetIcon(IMG_Load("icon.jpg"), NULL); 
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //Ajout d'un titre
    SDL_WM_SetCaption("Awale le jeu", NULL);
    //Définition d'une image pour le menu :
    menu = SDL_LoadBMP("img/Screen/Menu.bmp");

    positionMenu.x = 0;
    positionMenu.y = 0;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                        continuer = 0;
                        break;
                    case SDLK_KP1: // Demande à jouer
		                jouer(ecran);
                        printf("1vs1\n");
                        break;
                    case SDLK_RETURN:
		                jouer(ecran);
                    	printf("1vs1\n");
                        break;
                    case SDLK_KP2:
                        jouer_vs_IA(ecran,TRES_FACILE);
                        printf("1vsIA - Très facile \n");
                        break;
                    case SDLK_t:
                        jouer_vs_IA(ecran,TRES_FACILE);
                        printf("1vsIA - Très facile \n");
                        break;
                    case SDLK_KP3:
                        jouer_vs_IA(ecran,FACILE);
                        printf("1vsIA - Facile \n");
                        break;
                    case SDLK_f:
                        jouer_vs_IA(ecran,FACILE);
                        printf("1vsIA - Facile \n");
                        break;
                     case SDLK_KP4:
                        jouer_vs_IA(ecran,MOYEN);;
                        printf("1vsIA - Moyen \n");
                        break;
                    case SDLK_m:
                        jouer_vs_IA(ecran,MOYEN);
                        printf("1vsIA - Moyen \n");
                        break;
                    case SDLK_KP5:
                        //jouer_vs_IA(ecran,2);
                        printf("1vsIA - Difficile \n");
                        break;
                    case SDLK_d:
                        jouer_vs_IA(ecran,DIFFICILE);
                        printf("1vsIA - Difficile \n");
                        break;
                }
                break;
        }

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(menu);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(bg);
    SDL_Quit();

    return EXIT_SUCCESS;
}

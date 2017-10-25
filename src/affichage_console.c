#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "awale.h"
#include "affichage_console.h"

void afficher(Plateau *p, Stock *s){
	system("clear");
	printf("+----------------------------------+\n");
	printf("|                                  |\n");
	printf("|    +---+---+---+---+---+---+     |\n");
	printf("| J2:| %d | %d | %d | %d | %d | %d |     |\n",p->joueur_2[5],p->joueur_2[4],p->joueur_2[3],p->joueur_2[2],p->joueur_2[1],p->joueur_2[0]);
	printf("|    +---+---+---+---+---+---+     |\n");
	printf("| J1:| %d | %d | %d | %d | %d | %d |     |\n",p->joueur_1[0],p->joueur_1[1],p->joueur_1[2],p->joueur_1[3],p->joueur_1[4],p->joueur_1[5]);
	printf("|    +---+---+---+---+---+---+     |\n");
	printf("|                                  |\n");
	printf("+----------------------------------+\n");
	printf("C'est au tour du joueur !\n");
	printf("Joueur 1 : %d \n",s->stock_j1 );
	printf("Joueur 2 : %d \n",s->stock_j2);

}
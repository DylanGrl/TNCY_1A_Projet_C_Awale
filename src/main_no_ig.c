#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "awale.h"
#include "affichage_console.h"
#include "IA.h"

int main(){
	/**
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
	afficher(p,s);

	//fonctions de test pour play_a_turn
	
	play_a_turn(2,3,p,s);
	afficher(p,s);
	**/
/*
	play_a_turn(1,5,p,s);
	afficher(p,s);
	play_a_turn(1,5,p,s);
	afficher(p,s);
	play_a_turn(2,5,p,s);
	afficher(p,s);
	play_a_turn(1,4,p,s);
	afficher(p,s);	
	p->joueur_1[5] = 24;
	afficher(p,s);	
	play_a_turn(1,5,p,s);
	afficher(p,s);
	*/
	//test attaque
	int cas[11];
	cas[0]=2;	//6 6 6 6 6 6
	cas[1]=2;	//2 2 3 1 2 1
	cas[2]=3;
	cas[3]=1;
	cas[4]=2;
	cas[5]=1;
	cas[6]=6;
	cas[7]=6;
	cas[8]=6;
	cas[9]=6;
	cas[10]=6;
	cas[11]=6;
	int *r;
	r=(int*)(malloc(sizeof(int)*2));
	r=best_attack(cas);
	printf("best attaque:%d\n Value: %d\n", *(r+0),*(r+1));
	//valeur attendue : 5
	//test defense
	cas[0]=6;			
	cas[1]=6;		//2 2 2 2 2 5
	cas[2]=6;		//6 6 6 6 6 6
	cas[3]=6;		
	cas[4]=6;
	cas[5]=6;
	cas[6]=5;
	cas[7]=2;
	cas[8]=2;
	cas[9]=2;
	cas[10]=2;
	cas[11]=2;
	int *s;
	s=(int*)(malloc(sizeof(int)*2));
	s=best_defense(cas);
	printf("best best defense:%d\n Value: %d\n", *(s+0),*(s+1));
	//valeur attendue : 0
	//test2 defense
	cas[0]=6;			
	cas[1]=6;		//1 2 2 3 2 2
	cas[2]=6;		//6 6 6 6 6 6
	cas[3]=6;		
	cas[4]=6;
	cas[5]=6;
	cas[6]=2;
	cas[7]=2;
	cas[8]=3;
	cas[9]=2;
	cas[10]=2;
	cas[11]=1;
	int *t;
	t=(int*)(malloc(sizeof(int)*2));
	t=best_defense(cas);
	printf("best best defense:%d\n Value: %d\n", *(t+0),*(t+1));
	//valeur attendue : 0

	/**
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
    for(i=0;i<6;i++){
		p->joueur_1[i] = cas[i];
		p->joueur_2[i] = cas[i+6];
	}
	**/


	return 0;
}

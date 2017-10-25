#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "awale.h"




void score_a_zero(Stock * s){
	s->stock_j1 = 0;
	s->stock_j2 = 0;
}

/*

*/
void remplissage(Plateau * p,Stock * s){
	int i=0;
	for(i=0;i<6;i++){
		p->joueur_1[i] = 4;
		p->joueur_2[i] = 4;
	}
	score_a_zero(s);
}


int check_playable_case(int indice,int cas[11],int current_player){

	if(cas[indice]==0){//cas ou il n'y a aucune graine dans la case
		return 0;
	}

	if(current_player==1){//cas ou on ne peut pas affamer son adversaire pour le joueur 1 et 2
		if(cas[7]+cas[8]+cas[9]+cas[10]+cas[11]+cas[12]==0 && cas[indice]+indice<6){
			return 0;
		}

	}
	else{
		if(cas[0]+cas[1]+cas[2]+cas[3]+cas[4]+cas[5]==0 && cas[indice]+indice<11){
			return 0;
		}
	}

	//if(current_player==1 && cas[indice]


	return 1;
}


void capture(int current_player,int joueur_side,int last_case, Plateau *p, Stock * s){
	if(last_case >5 || last_case < 0){
		printf("Erreur sur l'indice : %d \n",last_case);
		return;
	}
	if(current_player == 1){
		if(joueur_side!=current_player){
			while(p->joueur_2[last_case]>1 && p->joueur_2[last_case]<=3 && last_case>=0){
				s->stock_j1 += p->joueur_2[last_case];
				printf("Stock J1 : %d \n",s->stock_j1);
				p->joueur_2[last_case]=0;
				last_case--;
			}
		}
	}
	else{
		if(joueur_side!=current_player){
			while(p->joueur_1[last_case]>1 && p->joueur_1[last_case]<=3 && last_case>=0){
				s->stock_j2 += p->joueur_1[last_case];
				printf("Stock J2 : %d \n",s->stock_j2);
				p->joueur_1[last_case]=0;
				last_case--;
			}
		}		
	}
}

/**
Fonction temporaire utilisant l'ancienne structure
Refaire avec gestion du joueur pour répartir directement dans les bon indices du tableau
*/
void play_a_turn(int current_player,int indice,Plateau *p,Stock *s){
	//printf("Je suis dans play_a_turn\n");
	int cas[11];
	int i;
	indice=indice+6*(current_player-1);
	for(i=0;i<6;i++){
		cas[i] = p->joueur_1[i];
		cas[i+6] = p->joueur_2[i];
	}
	if(check_playable_case(indice,cas,current_player)==1){

		//int tour=cas[indice]/12;
		//printf("tour :%d\n", tour);
		for (i=1;i<cas[indice]+1;i++){
			cas[(indice+i)%12]+=1;
		//printf("%d \n",cas[(indice+i)%12]);
		}
		int last_case = (cas[indice]+indice)%12;

		int joueur_side;
		if(last_case>5){
			joueur_side=2;
		}
		else{
			joueur_side=1;
		}

		last_case = last_case-6*(joueur_side-1);
		cas[indice] = 0;

		for(i=0;i<6;i++){
			p->joueur_1[i] = cas[i];
		 //printf("i[%d] = %d \n",i,cas[i]);
		 //printf("i[%d] = %d \n",i,p->joueur_1[i]);
			p->joueur_2[i] = cas[i+6];
		}
		capture(current_player,joueur_side,last_case,p,s);
		cas[indice]=0;
		//printf("J'ai fini play_a_turn\n");
	}
	else{
		printf("Impossible de jouer ce coup\n");
	}
}

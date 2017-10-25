#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "awale.h"

void remplissage(int * cas){
	int i;
	for (i=0;i<12;i++){
		cas[i]=4;
	}	
}
/*
	check_playable_case, retourne un booléen correspondant à
	la possibilité de jouer un coup. On ne peut pas jouer une 
	case vide. Il prend en compte la rêgle de famine ou on ne
	peut pas ne pas donner de graine à son adversaire s'il 
	n'en a plus. 
*/
bool check_playable_case(int indice){
	if(cas[indice]==0){
		return false;
	}
	else if(indice<6){
		if(cas[7]+cas[8]+cas[9]+cas[10]+cas[11]+cas[12]==0 && cas[indice]+indice<6){
			return false;
		}
		else{
			return true;
		}

	}
	else{
		if(cas[0]+cas[1]+cas[2]+cas[3]+cas[4]+cas[5]==0 && cas[indice]+indice<11{
			return false;
		}
		else{
			return true
		}
	}
}

	/*
	indice représente la case dont on prendra les graines
	on prend le graine et on les dépose une par une dans les
	cases suivantes modulo 12 pour revenir au début du plateau.
	On fait attention de ne pas remettre une graine dans la case
	de départ grâce au 'if', du coup on rajoute une case dans
	laquelle on met une graine car on saute cette case sans
	déposer de graine dedans.
	*/
void play_a_coup(int indice, int * cas){

	int i;
	int tour=cas[indice]/12;
	for (i=1;i<cas[indice]+1+tour;i++){
		if(i+indice!=12){
			cas[(indice+i)%12]+=1;
		}
	}
	if (!famine){
		capture(cas[indice]+tour,cas,graine);
		cas[indice]=0;
	}
}
	/*
	la capture prend en paramètres l'indice de la dernière case où des graines
	ont été déposées, le tableau de jeu et le nombre de graine des joueurs
	*/
void capture(int indice, int * cas, int * graine){
	if(current_player==0 && indice>5 && cas[indice]<=3 && cas[indice]>1){
		int i=0;
		while(cas[indice-i]<=3 && cas[indice-i]>1 && indice-i>5){
			graine[0]+=cas[indice-i];
			printf("%d graines capturées\n", cas[indice-i] );
			cas[indice-i]=0;
			i++;
		}
	}
	else if(current_player==1 && indice<6 && cas[indice]<=3 && cas[indice]>1){
		int i=0;
		while(cas[indice-i]<=3 && cas[indice-i]>1 && indice-i>=0){
			graine[1]+=cas[indice-i];
			printf("%d graines capturées\n", );
			cas[indice-i]=0;
			i++;
		}
	}

}
/*
	famine returne si le coup joué met le joueur adverse en état de famine
*/
bool famine(int indice, int * cas){
	int dummmy[12];
	int i;
	for (i=0;i<12;i++){
		dummy[i]=cas[i];
	}
	int dummygraine={0,0};
	int somme=0;
	capture(dummy[indice]+tour,dummy,dummygraine);
	if(current_player==1){
	for (i=0;i<5;i++){
		somme+=dummy[i];
	}
	if(somme==0){
		return false;
	}
	else{
		return true;
	}
}
	else{
		somme=0
		for(i=6;i<12;i++){
			somme+=dummy[i];
		}
		if(somme==0){
			return false;
		}
	}
	return true;
}

int main(int argv, char* argc[]){
	/*
	cas correspond aux valeurs des différentes cases qui composent le jeu
	la case 0 est utlisée au début pour choisir le mode de jeu
	*/
	int cas[11];
	/*
	graine corresponde aux graines possédées par les joueurs 1 et 2
	*/
	int graine[2]={0,0};
	/*
	current_player représente le joueur actuel, il peut être égal à 0 ou 1
	le joueur du bas est 0 et celui du haut 1
	*/ 
	int current_player;

	cas[0]=splash_screen();

/*
	switch (cas[0]){

		case 1:
			player_vs_player();
			break;

		case 2:
			player_vs_random();
			break;
	}
*/
	remplissage(cas);

	interface(cas);
	current_player=rand()%2
	printf("Le joueur %d commence!\n", current_player+1);
	int input;
	scanf("%d",&input);
	play_a_coup(input,cas);
	interface(cas);



	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <SDL/SDL.h>
#include "param.h"
#include "jeu.h"
#include "awale.h"
#include "affichage_console.h"
#include "IA.h"
#include <math.h>


//la fonction renvoie l'indice du meilleur coup et la valeur de prise du meilleur coup
	int tres_facile(int cas[11]){
		int play;
			for(play=0;play<6;play++){
				if(check_playable_case(6+play,cas,2)){
					do{
						play=rand()%6;
					}while(!check_playable_case(6+play,cas,2));
					return play;
				}
			}
			return -1;
	}
	int facile(int cas[11]){
		int *r;
		r=best_attack(cas);
		if(!r[1]){
			return tres_facile(cas);
		}
		else{
			return r[0];
		}
	}

//Fonction de capture adapter à l'IA
	int captureIA(int current_player,int joueur_side,int last_case,int cas[11]){
		int last_case6 = last_case-6*(joueur_side-1);
		int seed_taken=0;
		if(joueur_side!=current_player){
			while(cas[last_case]>1 && cas[last_case]<=3 && last_case6>=0){
				seed_taken+=cas[last_case];
				cas[last_case]=0;
				last_case--;
				last_case6--;
			}
			return seed_taken;
		}
	}	


//Fonction permettant de jouer un coup adapter pour l'IA
	int play_a_turnIA(int current_player,int indice,int cas[11]){

		if(check_playable_case(indice,cas,current_player)==1){

		//int tour=cas[indice]/12;
		//printf("tour :%d\n", tour);
			int i;
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
			cas[indice] = 0;
			int capt;
			capt=captureIA(current_player,joueur_side,last_case,cas);
			cas[indice]=0;
			return capt;
		//printf("J'ai fini play_a_turn\n");
		}
		else{
			return -1000;
		}
	}

//Fonction renvoyant la meilleure attaque pour l'IA
int * best_attack(int cas[11]){
		int i;
		int value;
		int max_value=0;
		int indice=-1;
		static int r[2];

		for(i=6;i<12;i++){
			//printf("max_value set to:%d\n", max_value );
			//printf("indice set to:%d\n",i);
			int last_case=((cas[i]+i)+(cas[i])/12)%12;//dernière case où on va jouer
			value=0;
			if(last_case<6){//on verifie que le dernier coup arrive bien chez l'adversaire			
				while((cas[last_case]==2 || cas[last_case]==1) && last_case>-1){
					value+=cas[last_case]+1;
					last_case--;
				}
				if(value>max_value && check_playable_case(i,cas,2)){
					max_value=value;
					indice=i;
				}
			}
		}
		r[0]=indice%6;
		r[1]=max_value;
		return r;
}

//Fonction renvoyant la meilleure attaque pour le joueur (dans le but d'être contré par l'IA)
int * best_attackplayer(int cas[11]){

	int i;
	int value;
	int max_value=0;
	int indice=-1;
	static int r[2];

	for(i=0;i<6;i++){
		//printf("max_value set to:%d\n", max_value );
		//printf("indice set to:%d\n",i);
		int last_case=((cas[i]+i)+(cas[i])/12)%12;//dernière case où on va jouer
		value=0;
		if(last_case>5){//on verifie que le dernier coup arrive bien chez l'adversaire			
			while((cas[last_case]==2 || cas[last_case]==1) && last_case>5){
				value+=cas[last_case]+1;
				last_case--;
			}
			if(value>max_value){
				max_value=value;
				indice=i;
			}
		}
	}
	r[0]=indice%6;
	r[1]=max_value;
	return r;
}
//la fonction renvoie l'indice du coup à jouer pour limiter le nombre de graines prise par
//l'adversaire. Dans le cas ou il n'en prendrait pas, la fonction retourne -1 pour indiquer
//que le joueur peut attaquer.
int * best_defense(int cas[11]){

	int value;
	int max_value=-24;
	int indice=0;
	int *r;
	r=(int*)(malloc(sizeof(int)*2));
	int castemp[11];
	int i;
	for (i=6; i<12;i++){
		int j;
		for(j=0;j<12;j++){
			castemp[j]=cas[j];
		}
		int capt;
		capt=play_a_turnIA(2,i,castemp);
	   	if(capt!=-1000){
			r=best_attackplayer(castemp);

			if(capt-r[1]>max_value){
				max_value=capt-r[1];
				indice=i;
			}
			//printf("max_value=%d\n",max_value);
		}
	}
	//play_a_turn(int current_player,int indice,ptemp,stemp)
	r[0]=indice%6;
	r[1]=max_value;
	return r;
}

//Il s'agit de la fonction réalisant le principal de l'approche min max, elle est donc sensé nous retourner
//le meilleur coup possible à jouer en anticipant à l'avance d'une profondeur donnée les éventuels possibilités du jeu
int helper(int cas[11],int depth,int value,int current_player,int max_depth){
	if(depth==max_depth){
		printf("value : %d\n",value);
		return value;
	}
	int sol;
	int castemp[11];
	int i;
	int results[6];
	//Ici on parcourt les différentes possiblités de coup
	//pour l'humain (joueur 1) ou L'IA (joueur 2)
	for(i=0;i<6;i++){
		printf("i:%d\n",i);
		int j;
		for (j=0;j<12;j++){
			castemp[j]=cas[j];// on créé un plateau temporaire
		}
		int jouer=play_a_turnIA(current_player,i,castemp);
		if(current_player==1){
			//printf("joueur_1 joue\n");
				int new_depth=depth+1;
				//printf("new_depth:%d\n\n", new_depth );
				if(jouer==-1000){
					results[i]=-1000;
				}
				else{
					int new_value=value-jouer;
					results[i]=helper(castemp,new_depth,new_value,2,max_depth);
				}
		}
		else{
			//printf("joueur_2 joue\n");
				int new_depth=depth+1;
				//printf("new_depth:%d\n\n", new_depth );
				if(jouer==-1000){
					results[i]=-1000;
				}
				else{
					int new_value=value+jouer;
					results[i]=helper(castemp,new_depth,new_value,1,max_depth);
				}
			
		}
	}
	sol=results[0];
	if(current_player==1){
		int g;
		for(g=1;g<6;g++){
			if(sol<results[g]){
				sol=results[g];
			}
		}
	}
	else{
		int g;
		int final_result;
		for(g=1;g<6;g++){
			if(sol<results[g]){
				sol=results[g];
				final_result=g;
			}
		}
		if(depth==0){
			return final_result;
		}
	}
	return sol;
}
int Minmax(int cas[11]){
	int max_depth=2;
	int rt=helper(cas,0,0,2,max_depth);
	//printf("rt: %d\n",rt );
	return rt;

}


int IA(Plateau *p,Difficulte diff){
	int cas[11];
	int i;
	for(i=0;i<6;i++){
		cas[i] = p->joueur_1[i];
		cas[i+6] = p->joueur_2[i];
	}
	switch(diff){
		case TRES_FACILE: return tres_facile(cas);

		case FACILE: return facile(cas);

		case MOYEN: return best_defense(cas)[0];

		case DIFFICILE: return Minmax(cas);
	}
	

}
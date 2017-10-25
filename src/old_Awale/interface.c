#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void interface(int cas[11]){
	printf("+----------------------------------+\n");
	printf("|                                  |\n");
	printf("|    +---+---+---+---+---+---+     |\n");
	printf("|    | %d | %d | %d | %d | %d | %d |     |\n",cas[11],cas[10],cas[9],cas[8],cas[7],cas[6]);
	printf("|    +---+---+---+---+---+---+     |\n");
	printf("|    | %d | %d | %d | %d | %d | %d |     |\n",cas[0],cas[1],cas[2],cas[3],cas[4],cas[5]);
	printf("|    +---+---+---+---+---+---+     |\n");
	printf("|                                  |\n");
	printf("+----------------------------------+\n");
	printf("C'est au tour du joueur %d !\n",  current_player+1);
	printf("Joueur 1 : %d \n",graine[0] );
	printf("Joueur 2 : %d \n",graine[1] );

}
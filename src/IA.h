#ifndef IA_Awale
#define IA_Awale

typedef enum Difficulte Difficulte;
enum Difficulte{
	TRES_FACILE,
	FACILE,
	MOYEN,
	DIFFICILE
};
int tres_facile(int cas[11]);
int facile(int cas[11]);
int captureIA(int current_player,int joueur_side,int last_case,int cas[11]);
int play_a_turnIA(int current_player,int indice,int cas[11]);
int * best_attack(int cas[11]);
int * best_attackplayer(int cas[11]);
int * best_defence(int cas[11]);
int helper(int cas[11],int depth,int value,int current_player,int max_depth);
int Minmax(int cas[11]);
int IA(Plateau *p,Difficulte diff);
#endif
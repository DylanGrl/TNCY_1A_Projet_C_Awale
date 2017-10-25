#ifndef awale
#define awale
struct Plateau
{
	int * joueur_1;

	int * joueur_2;
};
typedef struct Plateau Plateau;

struct Stock
{
	int stock_j2;
	int stock_j1;
};
typedef struct Stock Stock;


/**
Fonction permettant l'initialisation des scores en début de partie
Prend en paramètre le stock
*/
void score_a_zero(Stock * s);

/**
Fonction permettant de remplir un plateau en début de partie et d'initialiser les scores
Prend en paramètre le plateau de jeu et le stock des joueurs
*/
void remplissage(Plateau * p,Stock * s);

/**
Vérifie si une case à un indice donnée et jouable par le joueur en cours
*/
int check_playable_case(int indice,int cas[11],int current_player);

/**
Effectue la capture des graine si il le faut
Prend en paramètre le numéro du joueur courant, le côté du plateau sur lequel on arrive,
le numéro de la case, le plateau et le stock
*/
void capture(int current_player,int joueur_side,int last_case, Plateau *p, Stock * s);

/**
Fonction permettant la répartition des graines 
Prend en paramètre le numéro du joueur, l'indice de la case à joueur, le plateau et le stock
*/
void play_a_turn(int current_player,int indice,Plateau *p,Stock *s);
#endif
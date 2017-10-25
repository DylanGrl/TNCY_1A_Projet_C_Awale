all:
		make awale_game
		make console_game

awale_game: jeu.o awale.o affichage_console.o IA.o main.c
		gcc -w -o  awale_game main.c jeu.o awale.o affichage_console.o IA.o -lSDLmain -lSDL -lSDL_ttf
		#gcc -o awale_game main.c awale.o affichage_console.o

console_game: awale.o affichage_console.o IA.o main.c
		gcc -w -o console_game main_no_ig.c awale.o IA.o affichage_console.o

jeu.o: jeu.c
		gcc -c jeu.c

awale.o: awale.c
		gcc -c awale.c

affichage_console.o: affichage_console.c
		gcc -c affichage_console.c

IA.o: IA.c
		gcc -c IA.c

clean:
		rm *.o

mrproper:
		rm awale_game & rm console_game

fullrm:
		rm *.o & rm awale_game & rm console_game

	
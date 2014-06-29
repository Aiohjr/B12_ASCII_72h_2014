all:card_game

card_game:
	gcc main.c generate.c shuffle.c rng.c -o cg -lpdcurses
ruzzle.exe: dico.o jeu.o main.o grille.o
	gcc -o ruzzle.exe dico.o jeu.o main.o grille.o 
dico.o: dico.c
	gcc -c dico.c -Wall -W
grille.o: grille.c jeu.h
	gcc -c grille.c -Wall -W
jeu.o: jeu.c
	gcc -c jeu.c -Wall -W
main.o: main.c dico.h grille.h jeu.h
	gcc -c main.c dico.h grille.h jeu.h -Wall -W

/**
 \file TP3.c
 \brief  Ruzzle
 \author Baptiste et Maxime
 \version 4.0.0
 \date 28 octobre 2015
 */

#include <stdio.h>
#include <stdlib.h>
#define N 4
#define M 4
#include <time.h>
#include <unistd.h>
#include "dico.h"
#include "grille.h"
#include "jeu.h"


/**
 \fn int main();
 \brief programme principal
 */
int main(){
    /*Initialisation*/
    printf("*******RUZZLE*******");
    char grille[N][M];
    int score;
    creation_grille(grille);
    /*traitement*/
    affichage_grille(grille);
    liste_mots_trouve(grille);
    score=jeu(grille);
    printf("\n Vous avez marquer un total de %d points",score);
    return 0;
}

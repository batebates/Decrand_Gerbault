//
//  ruzzle
//
//
//  Created by Decrand Baptiste on 17/10/2015.
//
//

#include <stdio.h>
#include <stdlib.h>
#define N 4
#define M 4
#include <time.h>
#include <unistd.h>
#include "dico.h"
#include "grille.h"
#include "jeu.h"

int main(){
    /*Initialisation*/
    printf("*******RUZZLE*******");
    char grille[N][M];
    int score;
    creation_grille(grille);
    /*traitement*/
    affichage_grille(grille);
    tri_mot(grille);
    score=jeu(grille);
    printf("\n Vous avez marquer un total de %d points",score);
    return 0;
}

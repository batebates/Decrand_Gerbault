/**
 \file TP3.c
 \brief  Ruzzle
 \author Baptiste et Maxime
 \version 4.0.0
 \date 28 octobre 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/dico.h"
#include "../include/grille.h"
#include "../include/struct.h"


/**
 \fn int main();
 \brief programme principal
 */
int main(){
    /*Initialisation*/
	printf("\n\n%d\n\n",N);
    printf("************************************\n");
	printf("************************************\n");
	printf("******                        ******\n");
	printf("******        RUZZLE          ******\n");
	printf("******                        ******\n");
	printf("************************************\n");
	printf("************************************\n");
    t_lettre grille[N][M];
    creation_grille(grille);
    /*traitement*/
    affichage_grille(grille);
    liste_mots_trouve(grille);
	trier_score_decroissant();
    return 0;
}

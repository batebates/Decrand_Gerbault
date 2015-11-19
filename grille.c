/**
\file grille.c
\brief reunie les fonctions gerant la grille(creation,affichage...)
\author Baptiste Decrand & Maxime Gerbault
\version 0.5
\date 07/11/2015
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 4
#define M 4
/**
\fn void creation_grille(char grille[N][M]);
\brief creer une grille de lettres
\param une grille de caractère
*/
void creation_grille(char grille[N][M]){
    srand(time(NULL));
    /*Initialisation*/
    int i;
    int j;
    int prob[26]={30,34,45,52,98,102,107,111,140,141,142,153,161,184,202,209,211,238,269,291,302,305,306,307,308,310};
    /*traitement*/
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
			/*On tire un nombre entre 0 et 310,la lettre obtenue correspond à la place du nombre dans le tableau prob*/
            int p=rand()%310;
            int t=0;
                while(prob[t]<p) t++;
                    grille[i][j]=97+t;
        }
    }

}


/**
\fn void underscore();
\brief Fonction dessinant une ligne de taille 4*M
*/
void underscore(){

    /*Initialisation*/
    int i;
    for(i=0;i<M;i++)printf("-----");
}
/**
\fn void affichage_grille(char grille[N][M]);
\brief Affiche la grille
\param la grille a afficher
*/
void affichage_grille(char grille[N][M]){

    /*Initialisation*/
    int i;
    int j;
	int point[26]={1,3,3,2,1,4,4,4,1,8,10,1,2,1,1,3,8,1,1,1,1,4,10,10,10,10};
    /*traitement*/
    printf("\n");
    for(i=0;i<N;i++){
        underscore();
        printf("\n|");
        for(j=0;j<M;j++){
        printf(" %c  |",grille[i][j]);
        }
		printf("\n|");
		for(j=0;j<M;j++){
        printf("  %d |",point[grille[i][j]-97]);
        }
        printf("\n");
    }
    underscore();
}
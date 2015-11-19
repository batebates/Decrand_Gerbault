#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define N 4
#define M 4

void creation_grille(char grille[N][M]){
    srand(time(NULL));
    /*Initialisation*/
    int i;
    int j;
    int prob[26]={30,34,45,52,98,102,107,111,140,141,142,153,161,184,202,209,211,238,269,291,302,305,306,307,308,310};
    /*traitement*/
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            int p=rand()%310;
            int t=0;
                while(prob[t]<p) t++;
                    grille[i][j]=97+t;
        }
    }

}

/*Fonction dessinant une ligne de taille N*/
void underscore(){

    /*Initialisation*/
    int i;
    for(i=0;i<M*2;i++)printf("--");
}

void affichage_grille(char grille[N][M]){

    /*Initialisation*/
    int i;
    int j;
    /*traitement*/
    printf("\n");
    for(i=0;i<N;i++){
        underscore();
        printf("\n|");
        for(j=0;j<M;j++){
        printf(" %c |",grille[i][j]);
        }
        printf("\n");
    }
    underscore(grille);
}

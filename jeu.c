#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "grille.h"
#define N 4
#define M 4
#define tmax 20
FILE* dico_resultat;
int search_mot_dico(char mot_chercher[tmax],char dico[tmax]){
    dico_resultat=fopen(dico,"r");
    char carac_dico;
    char mot[tmax];
    int k=0;
    do{
        carac_dico=fgetc(dico_resultat);
        if(carac_dico=='\n'){
            mot[k]='\0';
            if(strcmp(mot_chercher,mot)==0){
                    fclose(dico_resultat);
                    return 1;
            }
            k=0;
        }
        else {
            mot[k]=carac_dico;
            k++;
        }
    }while(carac_dico != EOF);
    fclose(dico_resultat);
    return 0;
}

int add_mot_dico(char mot[tmax],char dico[tmax]){
    dico_resultat=fopen(dico,"a");
    fprintf(dico_resultat,"%s\n",mot);
    fclose(dico_resultat);
    return 0;
}

int jeu(char grille[N][M]){
    char mot_joueur[tmax];
    int score=0;
    while(!kbhit())
    {
        printf("\nMot?:");
        scanf("%s",mot_joueur);
        if(search_mot_dico(mot_joueur,"dico_resultat.txt") && !search_mot_dico(mot_joueur,"dico_trouve.txt")){
                printf("\nLe mot est valide");
                add_mot_dico(mot_joueur,"dico_trouve.txt");
                score += strlen(mot_joueur);


        }
        else printf("\nLe mot n'est pas valide");
        affichage_grille(grille);
        if(clock() >= 120000)/*2minutes*/
        {
            printf("\n Le temps est ecoule",mot_joueur);
            break;
        }
    }
    remove("dico_trouve.txt");
    remove("dico_resultat.txt");
    return score;
}

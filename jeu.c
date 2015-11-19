#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    carac_dico=fgetc(dico_resultat);
    while(carac_dico != EOF){
        if(carac_dico!='\n'){
            mot[k]=carac_dico;
            k++;
            
        }
        else {
            mot[k]='\0';
            if(strcmp(mot_chercher,mot)==0){
                fclose(dico_resultat);
                return 1;
            }
            k=0;
            
        }
        carac_dico=fgetc(dico_resultat);
    }
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
    printf("\nMot?:");
    scanf("%s",mot_joueur);
    printf("tamer");
    while(mot_joueur[0]!='Q'){
        if(search_mot_dico(mot_joueur,"dico_resultat.txt") && !search_mot_dico(mot_joueur,"dico_trouve.txt")){
            int n;
            scanf("%i",&n);
                printf("\nLe mot est valide");
                add_mot_dico(mot_joueur,"dico_trouve.txt");
                score = score+strlen(mot_joueur);


        }
        else printf("\nLe mot n'est pas valide");
        affichage_grille(grille);
       printf("\nMot?:");
       scanf("%s",mot_joueur);
    }
    remove("dico_trouve.txt");
    remove("dico_resultat.txt");
    return score;
}
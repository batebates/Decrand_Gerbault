//
//  ruzzle
//
//
//  Created by Decrand Baptiste on 17/10/2015.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define N 4
#define M 4
#define tmax 20
typedef struct{int x;int y;}t_coord;
int sommet;
t_coord pile[tmax];
/*Fonction Pile*/
void push(int x,int y){
    if(sommet<tmax-1){
        sommet++;
        pile[sommet].x=x;
        pile[sommet].y=y;
    }
}
void depush(){
    if(sommet>-1){
        sommet--;
    }
}
void initpile(void){
    sommet=-1;
}
int sommetpile_x(void){
        if(sommet>-1){
        return pile[sommet].x;
    }
    else return -1;
}
int sommetpile_y(void){
        if(sommet>-1){
        return pile[sommet].y;
    }
    else return -1;
}
void add_coord(t_coord redondance[N*M],int x,int y){
        int i=0;
        do{i++;}while(redondance[i].x!=-1);
        redondance[i].x=x;
        redondance[i].y=y;

}
int search_redondance(t_coord redondance[N*M],int x,int y){
    int i;
    for(i=0;i<=16;i++){
        if(redondance[i].x==x && redondance[i].y==y) return 1;
    }
    return 0;

}
void chemin(char grille[N][M],char lettre,int *k,t_coord redondance[N*M]){
    int x=sommetpile_x();
    int y=sommetpile_y();
    if(0<=x-1 && 0<=y-1 && grille[x-1][y-1]== lettre && !search_redondance(redondance,x-1,y-1)){
        push(x-1,y-1);
        add_coord(redondance,x-1,y-1);
        *k=*k+1;
    }
    else if(0<=x-1 && grille[x-1][y]== lettre && !search_redondance(redondance,x-1,y)){
        push(x-1,y);
        add_coord(redondance,x-1,y);
        *k=*k+1;
    }
    else if(0<=x-1 && y+1<M && grille[x-1][y+1]== lettre && !search_redondance(redondance,x-1,y+1)){
        push(x-1,y+1);
        add_coord(redondance,x-1,y+1);
        *k=*k+1;
    }
    else if(y+1<M && grille[x][y+1]==lettre &&!search_redondance(redondance,x,y+1)){
        push(x,y+1);
        add_coord(redondance,x,y+1);
        *k=*k+1;
    }
    else if(x+1<N && y+1<M && grille[x+1][y+1]== lettre && !search_redondance(redondance,x+1,y+1)){
        push(x+1,y+1);
        add_coord(redondance,x+1,y+1);
        *k=*k+1;
    }
    else if(x+1<N && grille[x+1][y]== lettre && !search_redondance(redondance,x+1,y)){
        push(x+1,y);
        add_coord(redondance,x+1,y);
        *k=*k+1;
    }
    else if(x+1<N && 0<=y-1 && grille[x+1][y-1]== lettre &&!search_redondance(redondance,x+1,y-1)){
        push(x+1,y-1);
        add_coord(redondance,x+1,y-1);
        *k=*k+1;
    }
    else if(0<=y-1 && grille[x][y-1]== lettre && !search_redondance(redondance,x,y-1)){
        push(x,y-1);
        add_coord(redondance,x,y-1);
        *k=*k+1;
    }
    else{
        depush();
        if(*k>0) *k=*k-1;
    }
}
int recherche_grille(char mot[tmax],char grille[N][M]){
    int i,j,k=0;
    //recherche du depart
    for(i=0;i<N ;i++){
        for(j=0;j<M;j++){
               if(grille[i][j]==mot[k]){
                    int p;
                    t_coord redondance[N*M];
                    for(p=0;p<N*M;p++) redondance[p].x=-1;
                    initpile();
                    push(i,j);
                    k++;
                    redondance[0].x=i;
                    redondance[0].y=j;
                    while(sommet!=-1){
                        if(mot[k]=='\0') return 1;
                        chemin(grille,mot[k],&k,redondance);
                    }
               }
        }
    }
    return 0;
}
void tri_mot(char grille[N][M]){
    FILE* dico = NULL;
    FILE* mot_trouve= NULL;
    dico = fopen("dicotrie.txt", "r");
    mot_trouve = fopen("dico_resultat.txt", "w");
    char mot[tmax];
    char carac_dico;
    int k=0;
    do{
        carac_dico=fgetc(dico);
        if(carac_dico=='\n'){
            mot[k]='\0';
            if(recherche_grille(mot,grille)){
                    fprintf(mot_trouve,"%s\n",mot);
            }
            k=0;
        }
        else {
            mot[k]=carac_dico;
            k++;
        }
    }while(carac_dico != EOF);
    fclose(dico);
    fclose(mot_trouve);
}

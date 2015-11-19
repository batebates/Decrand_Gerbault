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
#define t_max N*M
typedef struct{int x;int y;}t_coord;
/**
 \fn void push(int x,int y,t_coord pile[t_max],int *sommet);
 \brief ajoute les coordonnees x,y a une pile
 \param (coordonnée x,coordonnée y,pile de type t_coord,sommet de la pile)
 */
void push(int x,int y,t_coord pile[t_max],int *sommet){
    if(*sommet<t_max-1){
        *sommet=*sommet+1;
        pile[*sommet].x=x;
        pile[*sommet].y=y;
    }
}

/**
 \fn void depush(int *sommet);
 \brief enleve les coordonnees x,y du sommet d'une pile
 \param (sommet de la pile)
 */
void depush(int *sommet){
    if(*sommet>-1){
        *sommet=*sommet-1;
    }
}

/**
 \fn void initpile(int *sommet);
 \brief initialise une pile
 \param (sommet de la pile)
 */
void initpile(int *sommet){
    *sommet=-1;
}

/**
 \fn int sommetpile_x(t_coord pile[t_max],int *sommet);
 \brief recupere la coordonnee x du sommet d'une pile
 \param (la pile de type t_coord,sommet de la pile)
 \return la coordonnée x
 */
int sommetpile_x(t_coord pile[t_max],int *sommet){
        if(*sommet>-1){
        return pile[*sommet].x;
    }
    else return -1;
}

/**
 \fn int sommetpile_y(t_coord pile[t_max],int *sommet);
 \brief recupere la coordonnee y du sommet d'une pile
 \param (la pile de type t_coord,sommet de la pile)
 \return la coordonnée y
 */
int sommetpile_y(t_coord pile[t_max],int *sommet){
        if(*sommet>-1){
        return pile[*sommet].y;
    }
    else return -1;
}

/**
 \fn int search_redondance(int x,int y,t_coord pile[t_max],int *sommet);
 \brief recherche une coordonnée dans la pile
 \param (la coord x,la coord y,la pile de type t_coord,le sommet de la pile)
 \return 1 si la coord est presente 0 sinon
 */
int search_redondance(int x,int y,t_coord pile[t_max],int *sommet){
    int i;
    for(i=0;i<=*sommet;i++){
        if(pile[i].x==x && pile[i].y==y) return 1;
    }
    return 0;

}

/**
 \fn void chemin(char grille[N][M],char lettre,int *k,t_coord chemin_mot_pile[t_max],t_coord redondance_lettre_pile[t_max],int *adr_chemin_mot_sommet,int *redondance_lettre_sommet);
 \brief recherche la prochaine lettre d'un mot.
 \param (la grille du ruzzle,la pile la coord x,la coord y,la pile de type t_coord,le sommet de la pile)
 */
void chemin(char grille[N][M],char lettre,int *k,t_coord chemin_mot_pile[t_max],t_coord redondance_lettre_pile[t_max],int *adr_chemin_mot_sommet,int *redondance_lettre_sommet){
    int x=sommetpile_x(chemin_mot_pile,adr_chemin_mot_sommet);
    int y=sommetpile_y(chemin_mot_pile,adr_chemin_mot_sommet);
    if(0<=x-1 && 0<=y-1 && grille[x-1][y-1]== lettre && !search_redondance(x-1,y-1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x-1,y-1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x-1,y-1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
    else if(0<=x-1 && grille[x-1][y]== lettre && !search_redondance(x-1,y,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x-1,y,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x-1,y,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
    else if(0<=x-1 && y+1<M && grille[x-1][y+1]== lettre && !search_redondance(x-1,y+1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x-1,y+1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x-1,y+1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
    else if(y+1<M && grille[x][y+1]==lettre &&!search_redondance(x,y+1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x,y+1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x,y+1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
    else if(x+1<N && y+1<M && grille[x+1][y+1]== lettre && !search_redondance(x+1,y+1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x+1,y+1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x+1,y+1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
    else if(x+1<N && grille[x+1][y]== lettre && !search_redondance(x+1,y,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x+1,y,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x+1,y,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
    else if(x+1<N && 0<=y-1 && grille[x+1][y-1]== lettre &&!search_redondance(x+1,y-1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x+1,y-1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x+1,y-1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
    else if(0<=y-1 && grille[x][y-1]== lettre && !search_redondance(x,y-1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x,y-1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x,y-1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
    else{
        depush(adr_chemin_mot_sommet);
        if(*k>0) *k=*k-1;
    }
}
/**
 \fn recherche_mot_grille(char mot[t_max],char grille[N][M]);
 \brief recherche un mot dans la grille
 \param (le mot,la grille)
  \return 1 si le mot est present 0 sinon
 */
int recherche_mot_grille(char mot[t_max],char grille[N][M]){
    int i,j,k=0;
    int chemin_mot_sommet,redondance_lettre_sommet;
    t_coord chemin_mot_pile[t_max];
    t_coord redondance_lettre_pile[t_max];
    //recherche du depart
    for(i=0;i<N ;i++){
        for(j=0;j<M;j++){
               if(grille[i][j]==mot[k]){
                    initpile(&chemin_mot_sommet);
                    initpile(&redondance_lettre_sommet);
                    push(i,j,chemin_mot_pile,&chemin_mot_sommet);
                    push(i,j,redondance_lettre_pile,&redondance_lettre_sommet);
                    k++;
                    while(chemin_mot_sommet!=-1){
                        if(mot[k]=='\0') return 1;
                        chemin(grille,mot[k],&k,chemin_mot_pile,redondance_lettre_pile,&chemin_mot_sommet,&redondance_lettre_sommet);
                    }
               }
        }
    }
    return 0;
}

/**
 \fn liste_mots_trouve(char grille[N][M]);
 \brief parcours les mots dans un dictionaire et les écrit dans un.txt si ils sont présent dans la grille
 \param (la grille)
 */
void liste_mots_trouve(char grille[N][M]){
    FILE* dico = NULL;
    FILE* mot_trouve= NULL;
    dico = fopen("dicotrie.txt", "r");
    mot_trouve = fopen("dico_resultat.txt", "w");
    char mot[t_max];
    char carac_dico;
    int k=0;
    do{
        carac_dico=fgetc(dico);
        if(carac_dico=='\n'){
            mot[k]='\0';
            if(recherche_mot_grille(mot,grille)){
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

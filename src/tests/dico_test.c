/**
\file dico_test.c
\brief reunie les fonctions recherchant les mots dans une grille à l'aide d'un dictionnaire
\author Baptiste Decrand & Maxime Gerbault
\version 0.5
\date 07/11/2015
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/struct.h"
#include "../../include/dico.h"

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


void calc_score(t_valeurmot *mot_dico,t_coord chemin_mot_pile[t_max],int *adr_chemin_mot_sommet,t_lettre grille[N][M]){
	int double_mot=0,triple_mot=0;
	mot_dico->score=0;
	if(strlen(mot_dico->mot)>=5) mot_dico->score+=5*(strlen(mot_dico->mot)-4);
	while(*adr_chemin_mot_sommet !=-1){
		if(grille[sommetpile_x(chemin_mot_pile,adr_chemin_mot_sommet)][sommetpile_y(chemin_mot_pile,adr_chemin_mot_sommet)].bonus==1){
			mot_dico->score += 2*grille[sommetpile_x(chemin_mot_pile,adr_chemin_mot_sommet)][sommetpile_y(chemin_mot_pile,adr_chemin_mot_sommet)].pts;
		}
		else if (grille[sommetpile_x(chemin_mot_pile,adr_chemin_mot_sommet)][sommetpile_y(chemin_mot_pile,adr_chemin_mot_sommet)].bonus==2){
			mot_dico->score += 3*grille[sommetpile_x(chemin_mot_pile,adr_chemin_mot_sommet)][sommetpile_y(chemin_mot_pile,adr_chemin_mot_sommet)].pts;
		}
		else if (grille[sommetpile_x(chemin_mot_pile,adr_chemin_mot_sommet)][sommetpile_y(chemin_mot_pile,adr_chemin_mot_sommet)].bonus==3){
			double_mot=1;
		}
		else if (grille[sommetpile_x(chemin_mot_pile,adr_chemin_mot_sommet)][sommetpile_y(chemin_mot_pile,adr_chemin_mot_sommet)].bonus==4){
			triple_mot=1;
		}
		else mot_dico->score += grille[sommetpile_x(chemin_mot_pile,adr_chemin_mot_sommet)][sommetpile_y(chemin_mot_pile,adr_chemin_mot_sommet)].pts;
		depush(adr_chemin_mot_sommet);
		
	}
	if(double_mot) mot_dico->score=mot_dico->score*2;
	if(triple_mot) mot_dico->score=mot_dico->score*3;
	
}
/**
 \fn void chemin(t_lettre grille[N][M],char lettre,int *k,t_coord chemin_mot_pile[t_max],t_coord redondance_lettre_pile[t_max],int *adr_chemin_mot_sommet,int *redondance_lettre_sommet);
 \brief recherche la prochaine lettre d'un mot.
 \param (la grille du ruzzle,la pile la coord x,la coord y,la pile de type t_coord,le sommet de la pile)
 */
void chemin(t_lettre grille[N][M],char lettre,int *k,t_coord chemin_mot_pile[t_max],t_coord redondance_lettre_pile[t_max],int *adr_chemin_mot_sommet,int *redondance_lettre_sommet){
	/*On recupère les coordonnées du sommet de la pile chemin*/
    int x=sommetpile_x(chemin_mot_pile,adr_chemin_mot_sommet);
    int y=sommetpile_y(chemin_mot_pile,adr_chemin_mot_sommet);
	/*SI La Lettre situé au coin  haut gauche de la cellule x,y correspond à la prochaine lettre du mot et que le chemin est disponible*/
    if(0<=x-1 && 0<=y-1 && grille[x-1][y-1].c== lettre && !search_redondance(x-1,y-1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x-1,y-1,chemin_mot_pile,adr_chemin_mot_sommet);//On ajoute cette coordonnée à notre chemin
        push(x-1,y-1,redondance_lettre_pile,redondance_lettre_sommet);// On indique que l'on est passé par cette coordonnée
        *k=*k+1;//On passe à la lettre suivante
    }
	/*lettre au dessus*/
    else if(0<=x-1 && grille[x-1][y].c== lettre && !search_redondance(x-1,y,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x-1,y,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x-1,y,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
	/*lettre coin haut droite*/
    else if(0<=x-1 && y+1<M && grille[x-1][y+1].c== lettre && !search_redondance(x-1,y+1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x-1,y+1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x-1,y+1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
	/*lettre à droite*/
    else if(y+1<M && grille[x][y+1].c==lettre &&!search_redondance(x,y+1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x,y+1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x,y+1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
	/*Lettre bas droite*/
    else if(x+1<N && y+1<M && grille[x+1][y+1].c== lettre && !search_redondance(x+1,y+1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x+1,y+1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x+1,y+1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
	/*Lettre en bas*/
    else if(x+1<N && grille[x+1][y].c== lettre && !search_redondance(x+1,y,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x+1,y,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x+1,y,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
	/*Lettre coin bas gauche*/
    else if(x+1<N && 0<=y-1 && grille[x+1][y-1].c== lettre &&!search_redondance(x+1,y-1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x+1,y-1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x+1,y-1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
	/*Lettre à gauche*/
    else if(0<=y-1 && grille[x][y-1].c== lettre && !search_redondance(x,y-1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(x,y-1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(x,y-1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
	/*SINON on a pas trouve la lettre suivante du mot*/
    else{
        depush(adr_chemin_mot_sommet); //on enleve la coordonnee x,y au chemin 
        if(*k>0) *k=*k-1;//on retourne à la lettre precedente
    }
}

/**
 \fn recherche_mot_grille(t_valeurmot mot_dico,t_lettre grille[N][M]);
 \brief recherche un mot dans la grille
 \param (le mot,la grille)
  \return 1 si le mot est present 0 sinon
 */
int recherche_mot_grille(t_valeurmot *mot_dico,t_lettre grille[N][M]){
    int i,j,k=0;
    int chemin_mot_sommet,redondance_lettre_sommet;	
    t_coord chemin_mot_pile[t_max];
    t_coord redondance_lettre_pile[t_max];
	
    /*On recherche la premiere lettre du mot parmis la grille,ce sera nos points de departs*/
    for(i=0;i<N ;i++){
        for(j=0;j<M;j++){
				/*Si on trouve un point de depart*/
               if(grille[i][j].c==mot_dico->mot[k]){
					/*On initialise nos piles de chemin et de redondance*/
                    initpile(&chemin_mot_sommet);
                    initpile(&redondance_lettre_sommet);
					/*On push les coordonnées de depart à nos piles*/
                    push(i,j,chemin_mot_pile,&chemin_mot_sommet);
                    push(i,j,redondance_lettre_pile,&redondance_lettre_sommet);
                    k++;
					/*TANT QUE tout les chemins ne sont pas teste*/
                    while(chemin_mot_sommet!=-1){
                        if(mot_dico->mot[k]=='\0'){
                        		calc_score(mot_dico,chemin_mot_pile,&chemin_mot_sommet,grille);
					return 1;
                        } 
                        chemin(grille,mot_dico->mot[k],&k,chemin_mot_pile,redondance_lettre_pile,&chemin_mot_sommet,&redondance_lettre_sommet); // on cherche le chemin de la prochaine lettre du mot
                    }
               }
        }
    }
	 /*On a parcouru la grille sans trouve de mot on retourne donc 0*/
   return 0;
}



/**
 \fn liste_mots_trouve(t_lettre grille[N][M]);
 \brief parcours les mots dans un dictionaire et les écrit dans un.txt si ils sont présent dans la grille
 \param la grille
 */
void liste_mots_trouve(t_lettre grille[N][M]){
    FILE* dico = NULL;
    FILE* mot_trouve= NULL;
    dico = fopen("words++.txt", "r");
    mot_trouve = fopen("dico_resultat.txt", "w");
    t_valeurmot mot_dico;
    char carac_dico;
    int k=0;
	/*On recupere chaque mots du dictionnaire*/
    do{
        carac_dico=fgetc(dico);
        if(carac_dico=='\n'){
            mot_dico.mot[k]='\0';			
            if(recherche_mot_grille(&mot_dico,grille)){
				
		fprintf(mot_trouve,"%s %d\n",mot_dico.mot,mot_dico.score);
	}
            k=0;
        }
        else {
            mot_dico.mot[k]=carac_dico;
            k++;
        }
    }while(carac_dico != EOF);
    fclose(dico);
    fclose(mot_trouve);
}



void trier_score_decroissant(void){
    //declaration
    t_valeurmot tab[3000];
    FILE*resultat;
    resultat=fopen("dico_resultat.txt","r");
    int i=0,j=0;
    int stock=0;
    int compteur=0;
    char mot[20];
    //traitement

    for(j=0;!feof(resultat);j++){
        fscanf(resultat,"%s %d\n",tab[j].mot,&tab[j].score);
        compteur++;
    }
    for(i=0;i<compteur;i++){
		for(j=compteur-1;j>i;j--){
			if(tab[j-1].score>tab[j].score){
				stock=tab[j].score;
				strcpy(mot,tab[j].mot);
				tab[j].score=tab[j-1].score;
				strcpy(tab[j].mot,tab[j-1].mot);
				tab[j-1].score=stock;
				strcpy(tab[j-1].mot,mot);
			}
		}
	}
	//affichage des mots et leur score par ordre décroissant
	printf("\n");
    for(j=compteur-1;j>=0;j--){
        printf("\tmot: %s\t point: %d\n",tab[j].mot,tab[j].score);
    }
    fclose(resultat);
}

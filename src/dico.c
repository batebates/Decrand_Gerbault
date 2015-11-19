/**
\file dico.c
\brief reunie les fonctions recherchant les mots dans une grille à l'aide d'un dictionnaire
\author Baptiste Decrand & Maxime Gerbault
\version 0.5
\date 07/11/2015
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/struct.h"
#include "../include/dico.h"

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
 \fn int sommetpile(t_coord pile[t_max],int *sommet,t_coord *adr_coord_pile);
 \brief recupere les coordonnees du sommet d'une pile
 \param (la pile de type t_coord,sommet de la pile,les coordonnées à indenter)
 */
void sommetpile(t_coord pile[t_max],int *sommet,t_coord *adr_coord_pile){
        if(*sommet>-1){
			adr_coord_pile->x=pile[*sommet].x;
			adr_coord_pile->y=pile[*sommet].y;
    }
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
 \fn int search_redondance(int x,int y,t_coord pile[t_max],int *sommet);
 \brief attribue le score d'un mot en fonction de sa constitution et des règles du ruzzle
 \param (le mot et sa valeur,la pile contenant le chemin du mot,le sommet de la pile)
 */
void calc_score(t_valeurmot *mot_dico,t_coord chemin_mot_pile[t_max],int *adr_chemin_mot_sommet,t_lettre grille[N][M]){
	int double_mot=0,triple_mot=0;
	mot_dico->score=0;
	if(strlen(mot_dico->mot)>=5) mot_dico->score+=5*(strlen(mot_dico->mot)-4);
	while(*adr_chemin_mot_sommet !=-1){
		t_coord coord_pile;
		sommetpile(chemin_mot_pile,adr_chemin_mot_sommet,&coord_pile);
		if(grille[coord_pile.x][coord_pile.y].bonus==1){
			mot_dico->score += 2*grille[coord_pile.x][coord_pile.y].pts;
		}
		else if (grille[coord_pile.x][coord_pile.y].bonus==2){
			mot_dico->score += 3*grille[coord_pile.x][coord_pile.y].pts;
		}
		else if (grille[coord_pile.x][coord_pile.y].bonus==3){
			double_mot++;
		}
		else if (grille[coord_pile.x][coord_pile.y].bonus==4){
			triple_mot++;
		}
		else mot_dico->score += grille[coord_pile.x][coord_pile.y].pts;
		depush(adr_chemin_mot_sommet);
		
	}
	if(double_mot) mot_dico->score=mot_dico->score*2*double_mot;
	if(triple_mot) mot_dico->score=mot_dico->score*3*triple_mot;
	
}
/**
 \fn void chemin(t_lettre grille[N][M],char lettre,int *k,t_coord chemin_mot_pile[t_max],t_coord redondance_lettre_pile[t_max],int *adr_chemin_mot_sommet,int *redondance_lettre_sommet);
 \brief recherche la prochaine lettre d'un mot.
 \param (la grille du ruzzle,la pile la coord x,la coord y,la pile de type t_coord,le sommet de la pile)
 */
void chemin(t_lettre grille[N][M],char lettre,int *k,t_coord chemin_mot_pile[t_max],t_coord redondance_lettre_pile[t_max],int *adr_chemin_mot_sommet,int *redondance_lettre_sommet){
	/*On recupère les coordonnées du sommet de la pile chemin*/
	t_coord coord_pile;
	sommetpile(chemin_mot_pile,adr_chemin_mot_sommet,&coord_pile);
	/*SI La Lettre situé au coin  haut gauche de la cellule x,y correspond à la prochaine lettre du mot et que le chemin est disponible*/
    if(0<=coord_pile.x-1 && 0<=coord_pile.y-1 && grille[coord_pile.x-1][coord_pile.y-1].c== lettre && !search_redondance(coord_pile.x-1,coord_pile.y-1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(coord_pile.x-1,coord_pile.y-1,chemin_mot_pile,adr_chemin_mot_sommet);//On ajoute cette coordonnée à notre chemin
        push(coord_pile.x-1,coord_pile.y-1,redondance_lettre_pile,redondance_lettre_sommet);// On indique que l'on est passé par cette coordonnée
        *k=*k+1;//On passe à la lettre suivante
    }
	/*lettre au dessus*/
    else if(0<=coord_pile.x-1 && grille[coord_pile.x-1][coord_pile.y].c== lettre && !search_redondance(coord_pile.x-1,coord_pile.y,redondance_lettre_pile,redondance_lettre_sommet)){
        push(coord_pile.x-1,coord_pile.y,chemin_mot_pile,adr_chemin_mot_sommet);
        push(coord_pile.x-1,coord_pile.y,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
	/*lettre coin haut droite*/
    else if(0<=coord_pile.x-1 && coord_pile.y+1<M && grille[coord_pile.x-1][coord_pile.y+1].c== lettre && !search_redondance(coord_pile.x-1,coord_pile.y+1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(coord_pile.x-1,coord_pile.y+1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(coord_pile.x-1,coord_pile.y+1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
	/*lettre à droite*/
    else if(coord_pile.y+1<M && grille[coord_pile.x][coord_pile.y+1].c==lettre &&!search_redondance(coord_pile.x,coord_pile.y+1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(coord_pile.x,coord_pile.y+1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(coord_pile.x,coord_pile.y+1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
	/*Lettre bas droite*/
    else if(coord_pile.x+1<N && coord_pile.y+1<M && grille[coord_pile.x+1][coord_pile.y+1].c== lettre && !search_redondance(coord_pile.x+1,coord_pile.y+1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(coord_pile.x+1,coord_pile.y+1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(coord_pile.x+1,coord_pile.y+1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
	/*Lettre en bas*/
    else if(coord_pile.x+1<N && grille[coord_pile.x+1][coord_pile.y].c== lettre && !search_redondance(coord_pile.x+1,coord_pile.y,redondance_lettre_pile,redondance_lettre_sommet)){
        push(coord_pile.x+1,coord_pile.y,chemin_mot_pile,adr_chemin_mot_sommet);
        push(coord_pile.x+1,coord_pile.y,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
	/*Lettre coin bas gauche*/
    else if(coord_pile.x+1<N && 0<=coord_pile.y-1 && grille[coord_pile.x+1][coord_pile.y-1].c== lettre &&!search_redondance(coord_pile.x+1,coord_pile.y-1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(coord_pile.x+1,coord_pile.y-1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(coord_pile.x+1,coord_pile.y-1,redondance_lettre_pile,redondance_lettre_sommet);
        *k=*k+1;
    }
	/*Lettre à gauche*/
    else if(0<=coord_pile.y-1 && grille[coord_pile.x][coord_pile.y-1].c== lettre && !search_redondance(coord_pile.x,coord_pile.y-1,redondance_lettre_pile,redondance_lettre_sommet)){
        push(coord_pile.x,coord_pile.y-1,chemin_mot_pile,adr_chemin_mot_sommet);
        push(coord_pile.x,coord_pile.y-1,redondance_lettre_pile,redondance_lettre_sommet);
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


/**
 \fn void trier_score_decroissant(void);
 \brief trie un fichier de t_valeurmot en fonction du score dans l'ordre décroisant
 */
void trier_score_decroissant(void){
    //initialisation
    t_valeurmot tab[3000];
    FILE*resultat;
    resultat=fopen("dico_resultat.txt","r");
    int i,j;
    int tampon=0,cpt=0,sommescore=0;
    char mot[t_max];
    //traitement
    for(j=0;!feof(resultat);j++){
        fscanf(resultat,"%s %d\n",tab[j].mot,&tab[j].score);
		sommescore+=tab[j].score;
        cpt++;
    }
    for(i=0;i<cpt;i++){
		for(j=cpt-1;j>i;j--){
			if(tab[j-1].score>tab[j].score){
				tampon=tab[j].score;
				strcpy(mot,tab[j].mot);
				tab[j].score=tab[j-1].score;
				strcpy(tab[j].mot,tab[j-1].mot);
				tab[j-1].score=tampon;
				strcpy(tab[j-1].mot,mot);
			}
		}
	}
	//affichage des mots et leur score par ordre décroissant
	printf("************************************\n");
	printf("******        RESULTATS       ******\n");
	printf("************************************\n");
	printf("\n  nombre de mot:%d\n  score max=%d \n\n",cpt,sommescore);
    for(j=cpt-1;j>=0;j--){
        printf("\tmot: %s\t point: %d\n",tab[j].mot,tab[j].score);
    }
    fclose(resultat);
}

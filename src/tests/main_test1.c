/**
 \file TP3.c
 \brief  test_ruzzle
 \author Baptiste et Maxime
 \version 7.0.0
 \date 28 octobre 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include "./CUnitLocal/include/CUnit/Basic.h"
#include "./CUnitLocal/include/CUnit/CUnit.h"
#define N 4
#define M 4
#define t_max N*M
typedef struct{int x;int y;}t_coord;
typedef struct{char mot[t_max] ;int score;}t_valeurmot;
typedef enum {rien, dl, tl, dw, tw} t_bonus;
typedef struct {char c; int pts; t_bonus bonus;} t_lettre;

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
 \fn int main();
 \brief programme principal
 */
int main(){
	CU_pSuite pSuite = NULL;
	t_lettre grille[4][4]={{{'z',0,0},{'q',0,0},{'t',0,0},{'c',0,0}},
							{{'u',0,0},{'c',0,0},{'y',0,0},{'a',0,0}},
								{{'r',0,0},{'i',0,0},{'b',0,0},{'o',0,0}},
								{{'t',0,0},{'n',0,0},{'e',0,0},{'a',0,0}}};
	t_valeurmot mot1={"bobine",0};
	t_valeurmot mot2={"truc",0};
	t_valeurmot mot3={"tri",0};
	void test_grille(void){
		CU_ASSERT_EQUAL(recherche_mot_grille(&mot1,grille), 1);
		CU_ASSERT_EQUAL(recherche_mot_grille(&mot2,grille), 1);
		CU_ASSERT_EQUAL(recherche_mot_grille(&mot3,grille), 1);
	}
	
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();
    pSuite = CU_add_suite("Suite_1", 0, 0);
    if (!pSuite) {
            CU_cleanup_registry();
            return CU_get_error();
    }

    if (!CU_add_test(pSuite, "test of fprintf()", test_grille))
    {   CU_cleanup_registry();
    return CU_get_error();
    }
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

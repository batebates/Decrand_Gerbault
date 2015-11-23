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

int calc_score(t_valeurmot *mot_dico,t_coord chemin_mot_pile[t_max],int *adr_chemin_mot_sommet,t_lettre grille[N][M]){
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
	return mot_dico->score;
}

/**
 \fn int main();
 \brief programme principal
 */
int main(){
	CU_pSuite pSuite = NULL;
	t_lettre grille[4][4]={{{'z',0,0},{'q',0,0},{'t',0,0},{'c',0,0}},
							{{'u',0,0},{'c',0,0},{'y',0,0},{'b',0,0}},
								{{'r',0,0},{'i',0,0},{'b',0,0},{'o',0,0}},
								{{'t',0,0},{'n',0,0},{'e',0,0},{'a',0,0}}};
	t_valeurmot mot_dico1={"bobine",0};
	t_valeurmot mot_dico2={"truc",0};
	t_coord chemin_mot_pile1[6]={{1,3},{2,3},{2,2},{2,1},{3,1},{3,2}};
	t_coord chemin_mot_pile2[4]={{0,3},{0,2},{0,1},{1,1}};
	int chemin_mot_sommet1=5;
	int chemin_mot_sommet2=3;
	calc_score(&mot_dico1,chemin_mot_pile1,&chemin_mot_sommet1,grille);
	calc_score(&mot_dico1,chemin_mot_pile2,&chemin_mot_sommet2,grille);
	void test_score(void){
		CU_ASSERT_EQUAL(mot_dico1.score, 10);
		CU_ASSERT_EQUAL(mot_dico2.score, 2);
	}
	
	    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();
    pSuite = CU_add_suite("Suite_1", 0, 0);
    if (!pSuite) {
            CU_cleanup_registry();
            return CU_get_error();
    }

    if (!CU_add_test(pSuite, "test of fprintf()", test_score))
    {   CU_cleanup_registry();
    return CU_get_error();
    }
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

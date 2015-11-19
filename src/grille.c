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
#include "../include/struct.h" 

/**
\fn void creation_grille(t_lettre grille[N][M]);
\brief creer une grille de lettres
\param une grille de caractère
*/
void creation_grille(t_lettre grille[N][M]){
    srand(time(NULL));
    /*Initialisation*/
    int i;
    int j;
    int v;
    int prob[26]={30,34,45,52,98,102,107,111,140,141,142,153,161,184,202,209,211,238,269,291,302,305,306,307,308,310};
    t_lettre lettre;
   
    /*traitement*/
    for(i=0;i<N;i++){
       
        for(j=0;j<M;j++){
			
			/*On tire un nombre entre 0 et 310,la lettre obtenue correspond à la place du nombre dans le tableau prob*/
            int p=rand()%310;
            int t=0;
                while(prob[t]<p) t++;
               
                lettre.c=97+t;
                
                switch (lettre.c){
                	case 'a':
                	lettre.pts=1;
                	break;
                	
                	case 'e':
                	lettre.pts=1;
                	break;
                	
                	case 'i':
                	lettre.pts=1;
                	break;
                	
                	case 'l':
                	lettre.pts=1;
                	break;
                	
                	case 'n':
                	lettre.pts=1;
                	break;
                	
                	case 'o':
                	lettre.pts=1;
                	break;
                	
                	case 'r':
                	lettre.pts=1;
                	break;
                	
                	case 's':
                	lettre.pts=1;
                	break;
                	
                	case 't':
                	lettre.pts=1;
                	break;
                	
                	case 'u':
                	lettre.pts=1;
                	break;

                	case 'd':
                	lettre.pts=2;
                	break; 
                	
                	case 'm':
                	lettre.pts=2;
                	break; 
                	
                	
                	case 'g':
                	lettre.pts=2;
                	break; 
                	
                	
                	case 'b':
                	lettre.pts=3;
                	
                	case 'c':
                	lettre.pts=3;
                	
                	
                	case 'p':
                	lettre.pts=3;
                	
                	
                	case 'f':
                	lettre.pts=4;
                	break;
                	
                	case 'h':
                	lettre.pts=4;
                	break;
                	
                	
                	case 'v':
                	lettre.pts=4;
                	break;
                	
                	case 'j':
                	lettre.pts=8;
                	break;
                	
                	case 'q':
                	lettre.pts=8;
                	break;
                	
                	case 'k':
                	lettre.pts=10;
                	break;
                	
                	case 'w':
                	lettre.pts=10;
                	break;
                	
                	case 'x':
                	lettre.pts=10;
                	break;
                	
                	case 'y':
                	lettre.pts=10;
                	break;
                	
                	case 'z':
                	lettre.pts=10;
                	break;
                }
                
                v=rand()%100;
                
                if(v > 80 && v <=90 ) lettre.bonus=dl;
                else if(v > 90 && v <= 94) lettre.bonus=tl;
                else if(v > 94 && v <= 98) lettre.bonus=dw;
                else if(v > 98) lettre.bonus=tw;
                else lettre.bonus=rien;
                

                grille[i][j]= lettre;	
                	
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
    for(i=0;i<M;i++)printf("--------");
}

/**
\fn void affichage_grille(t_lettre grille[N][M]);
\brief Affiche la grille
\param la grille a afficher
*/
void affichage_grille(t_lettre grille[N][M]){

    /*Initialisation*/
    int i;
    int j;
	
    
    /*traitement*/
    printf("\n");
    for(i=0;i<N;i++){
        underscore();
        printf("\n");
        printf("\n|");
        for(j=0;j<M;j++){
        printf(" %c %i ",grille[i][j].c, grille[i][j].pts);
        switch(grille[i][j].bonus){
        	case 0:
        		printf("   |");
        		break;
        	
        	case 1:
        		printf("DL |");
        		break;
        	
        	case 2: 
        		printf("TL |");
        		break;
        	
        	case 3:
        		printf("DW |");
        		break;
        		
        	case 4:
        		printf("TW |");
        		break;
        	}		
        			
        				
        }
	   printf("\n");
        printf("\n");
    }
    underscore();
	printf("\n");
}

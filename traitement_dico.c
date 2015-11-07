//
//  traitement_dico.c
//  
//
//  Created by Decrand Baptiste on 04/11/2015.
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
int main(){
        FILE* dico = NULL;
        FILE* dicobis= NULL;
        dico = fopen("words.txt", "r");
        dicobis = fopen("words++.txt", "w");
        char mot[t_max];
        char carac_dico;
        int k=0;
        do{
            carac_dico=fgetc(dico);
            if(carac_dico=='\n'){
                mot[k]='\0';
                if(2<strlen(mot)&&strlen(mot)<17){
                    fprintf(dicobis,"%s\n",mot);
                }
                k=0;
            }
            else {
                mot[k]=carac_dico;
                k++;
            }
        }while(carac_dico != EOF);
        fclose(dico);
        fclose(dicobis);
    
}

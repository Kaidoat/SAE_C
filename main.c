#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#pragma warning(disable:4996)

//#include "inscription .h"
enum{LONGUEUR_MAX=30, LIMITE=100 };

typedef struct{
    char nom_etu[LONGUEUR_MAX];
    int no_groupe;
    int id;
}Etudiants ;

Etudiants etudiants[LIMITE];




void inscription(char*nom_etu, int no_groupe ) {
    Etudiants e;

    int nb_etudiants=0;


    if (nb_etudiants < LIMITE) {
        if (!existe_etudiant(e.nom_etu, e.no_groupe)) {
            etudiants[LIMITE].id = nb_etudiants + 1;
            strcpy(etudiants[nb_etudiants].nom_etu, e.nom_etu);
            etudiants[nb_etudiants].no_groupe = e.no_groupe;
            nb_etudiants++;
            printf("Inscription enregistree (%d)\n", nb_etudiants);
        }
        else  {
            printf("Nom incorrect\n");
        }
    }
    else {
        printf("Erreur : nombre maximum d'étudiants atteint\n");
    }
}


int main(){
    Etudiants e;
    inscription(e.nom_etu, e.no_groupe);



    exit(EXIT_FAILURE);
}


















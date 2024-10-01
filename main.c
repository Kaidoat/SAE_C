#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#pragma warning(disable:4996)


#define LONGUEUR_MAX_COMMANDE 20
#define LIMITE 100
#define LONGUEUR_MAX_ETUDIANT 30

//#include "inscription .h"


typedef struct{
    char nom_etu[LONGUEUR_MAX_ETUDIANT];
    int no_groupe;
    int id;
}Etudiant ;

Etudiant etudiants[LIMITE];


int verifier_nom(Etudiant etudiants[], int nb_etudiants, char nom_etu[], int no_groupe) {
    for (int i = 0; i < nb_etudiants; i++) {
        if (strcmp(etudiants[i].nom_etu, nom_etu) == 0 && etudiants[i].no_groupe == no_groupe) {
            return 1; // Nom déjà utilisé dans ce groupe
        }
    }
    return 0;
}

void inscription(){
    Etudiant e;
    int nb_etudiants = 0;
    char nom_etu[LONGUEUR_MAX_ETUDIANT];
    int no_groupe;

    while (nb_etudiants < LIMITE) {
        scanf("%s %d", nom_etu, &no_groupe);


        // Vérification de la longueur du nom
        if (strlen(nom_etu) > LONGUEUR_MAX_ETUDIANT - 1) {
            printf("Nom incorrect\n");
            continue;
        }

        // Vérification si le nom existe déjà dans le groupe
        if (verifier_nom(etudiants, nb_etudiants, nom_etu, no_groupe)) {
            printf("Nom incorrect\n");
            continue;
        }


        // Enregistrement de l'étudiant
        strcpy(etudiants[nb_etudiants].nom_etu, nom_etu);
        etudiants[nb_etudiants].no_groupe = no_groupe;
        nb_etudiants++;

        // Affichage de l'inscription enregistrée avec l'identifiant
        printf("Inscription enregistree (%d)\n", nb_etudiants);
    }
}



//----------C1------------//



int main(int argc, char **argv){

    char input[LONGUEUR_MAX_COMMANDE];

    do{
        scanf("%s",input);
        if (strcmp(input, "inscription")==0){ //----------C1---------//
            inscription();
        }

    } while(strcmp(input, "exit")!=0); //--------C0-----------//


}


















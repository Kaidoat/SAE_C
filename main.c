#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#pragma warning(disable:4996)


#define LONGUEUR_MAX_COMMANDE 20
#define LIMITE 100
#define LONGUEUR_MAX_ETUDIANT 30

//#include "inscription .h"


typedef struct {
    char nom_etu[LONGUEUR_MAX_ETUDIANT];
    int no_groupe;
    int nb_absences;
}Etudiant;

Etudiant etudiants[LIMITE];
int nb_etudiants = 0;

//---------------C1--------------//

int verifier_nom(Etudiant etudiants[], int nb_etudiants, char* nom_etu, int no_groupe) {
    for (int i = 0; i < nb_etudiants; i++) {
        if (strcmp(etudiants[i].nom_etu, nom_etu) == 0 && etudiants[i].no_groupe == no_groupe) {
            return 1; // Nom déjà utilisé dans ce groupe
        }
    }
    return 0;
}

void inscription() {
    Etudiant e;
    char nom_etu[LONGUEUR_MAX_ETUDIANT];
    int no_groupe;

    scanf("%s %d", nom_etu, &no_groupe);

    if (nb_etudiants < LIMITE) {
        // Vérification de la longueur du nom
        if (strlen(nom_etu) > LONGUEUR_MAX_ETUDIANT - 1) {
            printf("Nom incorrect\n");
            return;
        }

        // Vérification si le nom existe déjà dans le groupe
        if (verifier_nom(etudiants, nb_etudiants, nom_etu, no_groupe)) {
            printf("Nom incorrect\n");
            return;
        }

        // Enregistrement de l'étudiant en derniere position dans le tableau
        strcpy(etudiants[nb_etudiants].nom_etu, nom_etu);
        etudiants[nb_etudiants].no_groupe = no_groupe;

        // augmente le nb d'etudiants inscrits
        nb_etudiants++;

        // Affichage de l'inscription enregistrée avec l'identifiant
        printf("Inscription enregistree (%d)\n", nb_etudiants);
    }
    else {
        printf("Nb max d'etudiants atteint\n");
    }
}




//-------------------C2 essais-----------//
void absence() {
    char nom_etu[LONGUEUR_MAX_ETUDIANT];
    int jour = 0;
    int no_etudiant = 0;
    char am_pm [3];


    scanf("%d %d %s", &no_etudiant, &jour, am_pm);
    // transforme le num etudiant en index du tableau
    no_etudiant--;

    if (no_etudiant >= nb_etudiants) {
        printf("Identifiant incorrecte \n");
        return;
    }

    etudiants[no_etudiant].nb_absences++;
    printf("Absence enregistree [%d]", etudiants[no_etudiant].nb_absences);
    return;
    

    // Si l'étudiant n'est pas trouvé
    printf("Etudiant inconnu\n");
}


//----------------------C3--------------//
void etudiant() {
//
//
//         int
//         scanf("%d");
}




//----------Main------------//

int main(int argc, char** argv) {
    char input[LONGUEUR_MAX_COMMANDE];
    do {
        scanf("%s", input);
        if (strcmp(input, "inscription") == 0) { //----------C1---------//
            inscription();
        }
        else if (strcmp(input, "absence") == 0) { //----------C2---------//
            absence();
        }

             else if (strcmp(input, "etudiants") == 0) { //----------C3---------//
                    etudiant();
                }

                else if (strcmp(input, "exit") == 0) {
                    break;
                }

        else {
            printf("Commande inconnue\n");
            // elimine tous les caracteres jusqu'a fin de ligne
            while (fgetc(stdin) != '\n');
        }

    } while (strcmp(input, "exit") != 0); //--------C0-----------//
}


















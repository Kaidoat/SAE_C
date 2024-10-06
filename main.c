#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#pragma warning(disable:4996)


#define LONGUEUR_MAX_COMMANDE 20
#define LIMITE 100
#define LONGUEUR_MAX_ETUDIANT 30
#define JOUR_MAX 40
#define LEN_AM_PM 3
#define EXCUSE_MAX 80

#define AM 0
#define PM 1

//#include "inscription .h"
typedef struct {
    unsigned int jour;
    int demi_journee;
    char excuse[EXCUSE_MAX];
    bool excuse_valide;
}Absence;

typedef struct {
    char nom_etu[LONGUEUR_MAX_ETUDIANT];
    unsigned int no_groupe;
    unsigned int nb_absences;
    Absence absences[JOUR_MAX * 2];
}Etudiant;




Etudiant etudiant[LIMITE];
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
        if (verifier_nom(etudiant, nb_etudiants, nom_etu, no_groupe)) {
            printf("Nom incorrect\n");
            return;
        }

        // Enregistrement de l'étudiant en derniere position dans le tableau
        strcpy(etudiant[nb_etudiants].nom_etu, nom_etu);
        etudiant[nb_etudiants].no_groupe = no_groupe;

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
    Etudiant e;
    char nom_etu[LONGUEUR_MAX_ETUDIANT];
    int no_etudiant = 0;
    int jour = 0;
    char am_pm[LEN_AM_PM];
    int demi_journee;


    scanf("%d %d %s", &no_etudiant, &jour, am_pm);
    // transforme le num etudiant en index du tableau
    no_etudiant--;

    if (jour < 1 || jour > JOUR_MAX) {
        printf("Jour incorrect\n");
        return;
    }


    if (no_etudiant >= nb_etudiants) {
        printf("Identifiant incorrect\n");
        return;
    }

    if (no_etudiant >= nb_etudiants || no_etudiant < 0) {
        printf("Identifiant incorrect\n");
        return;
    }

    etudiant[no_etudiant].absences[etudiant[no_etudiant].nb_absences].jour = jour;


    if (strcmp(am_pm, "am") == 0) {
        demi_journee = AM;
    }
    else if (strcmp(am_pm, "pm") == 0) {
        demi_journee = PM;
    }
    else {
        printf("Commande inconnu/n");
        return;
    }

    etudiant->absences[etudiant->nb_absences].demi_journee = am_pm;

    
    etudiant[no_etudiant].nb_absences++;
    printf("Absence enregistree [%d]\n", etudiant[no_etudiant].nb_absences);
    return;

}


//----------------------C3--------------//
void etudiants() {


    int nb_annee;
    scanf("%d", &nb_annee);
    if (nb_etudiants == 0) {
        printf("Aucun inscrit\n");
        return;
    }

    if (nb_annee == 0) {
        printf("Date incorrect\n");
    }
    int T = 0;
    while (nb_etudiants > T) {
        printf("(%d) %c %d\n", nb_etudiants, etudiant[nb_etudiants].nom_etu, etudiant[nb_etudiants].no_groupe);
        T++;
    }

}




//----------Main------------//

int main() {
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
            etudiants();
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


















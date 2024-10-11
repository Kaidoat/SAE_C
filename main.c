#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#pragma warning(disable:4996)

#define MAX_INPUT 150
#define LONGUEUR_MAX_COMMANDE 20
#define LIMITE 100
#define LONGUEUR_MAX_ETUDIANT 30
#define JOUR_MAX 40
#define LEN_AM_PM 3
#define EXCUSE_MAX 80
#define LONGUEUR_MAX_JUSTIF 50

#define AM 0
#define PM 1

typedef enum {
    A_FOURNIR = 0,
    A_VALIDER,
    ACCEPTEE,
    REFUSEE
} StatutExcuse;


typedef struct {
    unsigned int jour;
    int demi_journee;
    char excuse[EXCUSE_MAX];
    StatutExcuse statut_excuse;
}Absence;

typedef struct {
    char nom_etu[LONGUEUR_MAX_ETUDIANT+1]; // +1 pour zero final
    unsigned int no_groupe;
    unsigned int nb_absences;
    Absence absences[JOUR_MAX * 2];
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
    char nom_etu[MAX_INPUT];
    int no_groupe;

    scanf("%s %d", nom_etu, &no_groupe);

    if (nb_etudiants < LIMITE) {
        // Vérification de la longueur du nom
        if (strlen(nom_etu) > LONGUEUR_MAX_ETUDIANT) {
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




//-------------------C2----------------//
void absence() {
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

    if (strcmp(am_pm, "am") == 0) {
        demi_journee = AM;
    }
    else if (strcmp(am_pm, "pm") == 0) {
        demi_journee = PM;
    }
    else {
        printf("Commande inconnue/n");
        return;
    }

    etudiants[no_etudiant].absences[etudiants[no_etudiant].nb_absences].jour = jour;
    etudiants[no_etudiant].absences[etudiants[no_etudiant].nb_absences].demi_journee = demi_journee;
    etudiants[no_etudiant].absences[etudiants[no_etudiant].nb_absences].excuse[0] = 0;
    etudiants[no_etudiant].absences[etudiants[no_etudiant].nb_absences].statut_excuse = A_FOURNIR;
    
    etudiants[no_etudiant].nb_absences++;
    printf("Absence enregistree [%d]\n", etudiants[no_etudiant].nb_absences);

}


int compare_etudiants(Etudiant* E1, Etudiant* E2) {
    if (E1->no_groupe != E2->no_groupe)
        return E1->no_groupe - E2->no_groupe;
    else
        return strcmp(E1->nom_etu, E2->nom_etu);
}

int compte_absence(int jour, int id) {
    int compte_absence=0;
    for (int i = 0; i < compte_absence; ++i) {
        if (absences[i].id == id && absences[i].jour <= jour) {
            ++compte_absence;
        }
    }
    return compte_absence;
}


//----------------------C3--------------//
void liste_etudiants() {

    Etudiant e;
    int nb_annee;
    scanf("%d", &nb_annee);

    if (nb_etudiants == 0) {
        printf("Aucun inscrit\n");
        return;
    }

    if (nb_annee == 0) {
        printf("Date incorrect\n");
    }

        else {
            qsort(etudiants, nb_etudiants, sizeof(Etudiant), compare_etudiants);
            int taille = savoir_max_caractere();
            for (int i = 0; i < Compteur_etudiants; ++i) {
                printf("(%d) %-*s %3d %2d\n", etudiants[i].numero, taille, etudiants[i].nom,
                       etudiants[i].groupe, savoir_nombres_absences(jour, etudiants[i].numero));



            }
}

//--------------C4-----------//
void depot_justificatif() {
    int no_etudiant, jour;
    char justificatif[LONGUEUR_MAX_JUSTIF];  // pour le texte de l'excuse

    scanf("%d %d %[^\n]", &no_etudiant, &jour, justificatif);

    if (no_etudiant > nb_etudiants || no_etudiant <= 0) {
        printf("Identifiant incorrect\n");
        return;
    }

    Etudiant* etudiant = &etudiant[no_etudiant - 1];

    // Recherche de l'absence correspondant au jour
    int index_absence = 0;
    for (int i = 0; i < etudiant->nb_absences; i++) {
        if (etudiant->absences[i].jour == jour) {
            index_absence = i;
            break;
        }
    }

    Absence* absence = &etudiant->absences[index_absence];


    // cas ou le justif est deja fourni
    if (absence->statut_excuse == ACCEPTEE) {
        printf("Justificatif deja connu\n");
        return;
    }


    // Verification si justificatif est fourni dans les temps (3j max)
    if (jour <= absence->jour + 3) {
        strcpy(absence->excuse, justificatif);
        absence->statut_excuse = A_VALIDER;
        printf("Justificatif enregistre\n");
    }
    else {
        strcpy(absence->excuse, justificatif);
        absence->statut_excuse = REFUSEE;
        printf("Justificatif enregistre\n");
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
            liste_etudiants();
        }

        else if (strcmp(input, "justificatif") ==0){ //---------C4----------//
            depot_justificatif();
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




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct etudiant
typedef struct {
    int id;
    char nom[30];
    int groupe;
    int absences;
} Etudiant;

//struct absence
typedef struct {
    int id;
    int id_etudiant;
    int jour;
    char demi_journee[3];
    char justificatif[51];
    int valide;
} Absence;

Etudiant etudiants[100];

Absence absences[100];

int nb_etudiants = 0;

int nb_absences = 0;

// Fonction inscrire un étudiant
void inscription(char *nom, int groupe) {
    if (nb_etudiants < 100) {
        if (!existe_etudiant(nom, groupe)) {
            etudiants[nb_etudiants].id = nb_etudiants + 1;
            strcpy(etudiants[nb_etudiants].nom, nom);
            etudiants[nb_etudiants].groupe = groupe;
            etudiants[nb_etudiants].absences = 0;
            nb_etudiants++;
            printf("Inscription enregistree (%d)\n", nb_etudiants);
        }
        else {
            printf("Nom incorrect\n");
        }
    }
    else {
        printf("Erreur : nombre maximum d'étudiants atteint\n");
    }
}

// existe étduiant a faire ensuite

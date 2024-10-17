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
#define LONGUEUR_MAX_JUSTIF 51
#define LONGUEUR_MAX_ABSENCE 100

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
} Absence;

typedef struct {
    char nom_etu[LONGUEUR_MAX_ETUDIANT + 1]; // +1 pour zero final
    unsigned int no_groupe;
    unsigned int nb_absences;
    Absence absences[JOUR_MAX * 2];
    int id;
} Etudiant;




//---------------C1--------------//

int verifier_nom(Etudiant etudiants[], int nb_etudiants, char* nom_etu, int no_groupe) {
    for (int i = 0; i < nb_etudiants; i++) {
        if (strcmp(etudiants[i].nom_etu, nom_etu) == 0 && etudiants[i].no_groupe == no_groupe) {
            return 1; // Nom déjà utilisé dans ce groupe
        }
    }
    return 0;
}

void inscription(Etudiant etudiants[], int* nb_etudiants) {
    Etudiant e;
    char nom_etu[MAX_INPUT];
    int no_groupe = -1;

    scanf("%s %d", nom_etu, &no_groupe);

    if (no_groupe==-1){
        printf("Groupe incorrect\n ");
        return;
    }


    if (*nb_etudiants < LIMITE) {
        // Vérification de la longueur du nom
        if (strlen(nom_etu) > LONGUEUR_MAX_ETUDIANT) {
            printf("Nom incorrect\n");
            return;
        }

        // Vérification si le nom existe déjà dans le groupe
        if (verifier_nom(etudiants, *nb_etudiants, nom_etu, no_groupe)) {
            printf("Nom incorrect\n");
            return;
        }


        // Enregistrement de l'étudiant en derniere position dans le tableau
        strcpy(etudiants[*nb_etudiants].nom_etu, nom_etu);
        etudiants[*nb_etudiants].no_groupe = no_groupe;
        etudiants[*nb_etudiants].nb_absences = 0;
        etudiants[*nb_etudiants].id = *nb_etudiants+1;

        // augmente le nb d'etudiants inscrits
        (*nb_etudiants)++;



        // Affichage de l'inscription enregistrée avec l'identifiant
        printf("Inscription enregistree (%d)\n", *nb_etudiants);
    } else {
        printf("Nb max d'etudiants atteint\n");
    }
}

int verif_absence(Etudiant etudiants[], int no_etudiant, int jour, int demi_journee){

    for(int i =0;i<etudiants[no_etudiant].nb_absences;i++){
        if (etudiants[no_etudiant].absences[i].jour == jour && etudiants[no_etudiant].absences[i].demi_journee == demi_journee){
            printf("Absence deja connue ");
            return 0;
        }

    }
    return 1 ;
}

//-------------------C2----------------//
void absence(Etudiant etudiants[], int nb_etudiants, int*Nb_absencesTotal) {

    char nom_etu[LONGUEUR_MAX_ETUDIANT];
    int no_etudiant = 0;
    int jour = 0;
    char am_pm[MAX_INPUT];
    int demi_journee = 0;
    int var_retour;

    scanf("%d %d %s", &no_etudiant, &jour, am_pm);
    // transforme le num etudiant en index du tableau
    no_etudiant--;

    if (jour < 1 || jour > JOUR_MAX) {
        printf("Date incorrecte\n");
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
    } else if (strcmp(am_pm, "pm") == 0) {
        demi_journee = PM;
    } else {
        printf("Demi-journee incorrecte \n");
        return;
    }


    var_retour = verif_absence(etudiants,no_etudiant,jour, demi_journee);
    if (var_retour){

        etudiants[no_etudiant].absences[etudiants[no_etudiant].nb_absences].jour = jour;
        etudiants[no_etudiant].absences[etudiants[no_etudiant].nb_absences].demi_journee = demi_journee;
        etudiants[no_etudiant].absences[etudiants[no_etudiant].nb_absences].excuse[0] = 0;
        etudiants[no_etudiant].absences[etudiants[no_etudiant].nb_absences].statut_excuse = A_FOURNIR;

        etudiants[no_etudiant].nb_absences++;
        (*Nb_absencesTotal)++;
        printf("Absence enregistree [%d]\n",*Nb_absencesTotal);
    }


}

int savoir_max_caractere(Etudiant etudiants[], int nb_etudiants) {
    if (nb_etudiants  == 0)
        return 0;

    int caract = 0;
    for (int i = 0; i < nb_etudiants; ++i) {
        if (strlen(etudiants[i].nom_etu) > caract)
            caract = strlen(etudiants[i].nom_etu);
    }
    return caract;
}




//----------------------C3--------------//
void liste_etudiants(Etudiant etudiants[], int nb_etudiants ) {

    Absence a ;
    a.jour=0;
    scanf("%d", &a.jour );
    if (nb_etudiants == 0) {
        printf("Aucun inscrit\n");
        return;
    }

    if (a.jour < 1) {
        printf("Date incorrecte\n");
        return;
    }

// Trier les étudiants par groupe (ordre décroissant) puis par nom (ordre croissant)
    for (int i = 0; i < nb_etudiants - 1; i++) {
        for (int j = i + 1; j < nb_etudiants; j++) {
            // Si le groupe de l'étudiant i est plus petit que celui de l'étudiant j (ordre décroissant)
            // ou si les groupes sont égaux et le nom de l'étudiant i est plus grand que celui de l'étudiant j (ordre croissant)
            if (etudiants[i].no_groupe < etudiants[j].no_groupe ||
                (etudiants[i].no_groupe == etudiants[j].no_groupe && strcmp(etudiants[i].nom_etu, etudiants[j].nom_etu) < 0)) {

                // Échanger les deux étudiants
                Etudiant temp = etudiants[i];
                etudiants[i] = etudiants[j];
                etudiants[j] = temp;
            }
        }
    }


    int taille = savoir_max_caractere(etudiants, nb_etudiants);
    for (int i = 0; i < nb_etudiants; ++i) {
        // Utiliser i + 1 pour avoir les indices dans le bon ordre
        printf("(%d) %-*s %2d %d\n", etudiants[nb_etudiants - 1 - i].id, taille, etudiants[nb_etudiants - 1 - i].nom_etu,
            etudiants[nb_etudiants - 1 - i].no_groupe, etudiants[nb_etudiants - 1 - i].nb_absences);
    }
}


//--------------------C4-----------------------------//
void depot_justificatif(Etudiant etudiants[], int nb_etudiants) {

    int no_etudiant, jour;
    char justificatif[LONGUEUR_MAX_JUSTIF];  // pour le texte de l'excuse

    scanf("%d %d %[^\n]", &no_etudiant, &jour, justificatif);

    if (no_etudiant > nb_etudiants || no_etudiant <= 0) {
        printf("Identifiant incorrect\n");
        return;
    }

    Etudiant* etudiant = &etudiants[no_etudiant - 1];

    // Recherche de l'absence correspondant au jour
    int index_absence = -1; // aucune absence trouvee
    for (int i = 0; i < etudiant->nb_absences; i++) {
        if (etudiant->absences[i].jour == jour) {
            index_absence = i;
            break;
        }
    }

    if(index_absence==-1){
        printf("Absence non trouvée");
        return;

    }



    Absence* absence = &etudiant->absences[index_absence];


    // cas ou le justif est deja fourni
    if (absence->statut_excuse != A_FOURNIR) {
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


void validations (){

}



//----------Main------------//
int main() {
    Etudiant etudiants[LIMITE];
    int nb_etudiants = 0;
    char input[LONGUEUR_MAX_COMMANDE+1];
    int NB_absences_Total=0;

    do {
        scanf("%s", input);
        if (strcmp(input, "inscription") == 0) { //----------C1---------//
            inscription(etudiants, &nb_etudiants);

        } else if (strcmp(input, "absence") == 0) { //----------C2---------//
            absence(etudiants, nb_etudiants, &NB_absences_Total);
        } else if (strcmp(input, "etudiants") == 0) { //----------C3---------//
            liste_etudiants(etudiants, nb_etudiants);
        } else if (strcmp(input, "justificatif") == 0) { //---------C4----------//
            depot_justificatif(etudiants, nb_etudiants);
        }

        else if (strcmp(input, "validations") == 0){
            validations();
        }
        else if (strcmp(input, "exit") == 0) { //---------C4----------//
            break;
        }
        else if (strcmp(input, "exit") == 0) { //---------C4----------//
            printf("Commande inconnue\n");
        }
    } while (strcmp(input, "exit") != 0); //--------C0-----------//
}

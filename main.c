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


typedef struct{
    int id_absence;
    int id_etudiant;
    char nom_etu[LONGUEUR_MAX_ETUDIANT + 1];
    int no_groupe;
    unsigned int jour;
    int demi_journee;
   char excuse[EXCUSE_MAX];

}Validations;






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



int savoir_nombres_absences(Etudiant etudiant, int jour) {

    int compte_absence = 0;
    for (int i = 0; i < etudiant.nb_absences; ++i) {
        if (etudiant.absences[i].jour <= jour) {
            ++compte_absence;
        }
    }
    return compte_absence;
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
        int nb_absences_jusqu_a_jour = savoir_nombres_absences(etudiants[nb_etudiants - 1 - i], a.jour);
        // Utiliser i + 1 pour avoir les indices dans le bon ordre
        printf("(%d) %-*s %2d %d\n", etudiants[nb_etudiants - 1 - i].id, taille, etudiants[nb_etudiants - 1 - i].nom_etu,
            etudiants[nb_etudiants - 1 - i].no_groupe, nb_absences_jusqu_a_jour);
    }
}


//--------------------C4-----------------------------//
void depot_justificatif(Etudiant etudiants[], int nb_etudiants, int nb_absences_total) {

    int id_absence, jour;
    char justificatif[LONGUEUR_MAX_JUSTIF];  // pour le texte de l'excuse

    scanf("%d %d %[^\n]", &id_absence, &jour, justificatif);

    if (id_absence <= 0 || id_absence > nb_absences_total) {
        printf("Identifiant incorrect\n");
        return;
    }

    Absence* absence = NULL;
    Etudiant* etu = NULL;
    int compteur_absence = 0;


    for (int i = 0; i < nb_etudiants; i++) {
        for (int j = 0; j < etudiants[i].nb_absences; j++) {
            compteur_absence++;
            if (compteur_absence == id_absence) {
                etu = &etudiants[i];
                absence = &etudiants[i].absences[j];
                break;
            }
        }
        if (absence != NULL) break;
    }

    if (absence == NULL) {
        printf("Absence non trouvée\n");
        return;
    }

    // Vérification de la date par rapport à l'absence
    if (jour < absence->jour) {
        printf("Date incorrecte\n");
        return;
    }

    // Vérifier si un justificatif a déjà été déposé
    if (absence->statut_excuse != A_FOURNIR) {
        printf("Justificatif deja connu\n");
        return;
    }

    // Vérification si le justificatif est fourni dans les temps (3 jours)
    if (jour <= absence->jour + 3) {
        strcpy(absence->excuse, justificatif);
        absence->statut_excuse = A_VALIDER;
        printf("Justificatif enregistre\n");
    }
    else {
        strcpy(absence->excuse, justificatif);
        absence->statut_excuse = REFUSEE;
        printf("Justificatif enregistre en retard\n");
    }
}

//--------------------C5-----------------------------//
void validations (Etudiant etudiants[], int nb_etudiants){

        bool a_des_validations = false;
        int nb_validations = 0;
        Validations validations[LONGUEUR_MAX_ABSENCE];



        for(int i =0;i<nb_etudiants;i++){
            for(int j=0;j<etudiants[i].nb_absences;j++){
                Absence *absence= &etudiants[i].absences[j];


                if (absence->statut_excuse ==A_VALIDER){
                    a_des_validations = true;

                    validations[nb_validations].id_absence =j+1;
                    validations[nb_validations].id_etudiant = etudiants[i].id;
                    strcpy(validations[nb_validations].nom_etu, etudiants[i].nom_etu);
                    validations[nb_validations].no_groupe = etudiants[i].no_groupe;
                    validations[nb_validations].jour = absence->jour;
                    validations[nb_validations].demi_journee= absence->demi_journee;
                    strcpy(validations[nb_validations].excuse, absence->excuse);
                    nb_validations++;
                }

            }

        }

    if (!a_des_validations){
        printf("Aucune validation en attente\n ");
        return;
    }

    for (int i = 0; i < nb_validations - 1; i++) {
        for (int j = i + 1; j < nb_validations; j++) {
            if (validations[i].id_etudiant > validations[j].id_etudiant ||
                (validations[i].id_etudiant == validations[j].id_etudiant && validations[i].jour > validations[j].jour)) {
                Validations temp = validations[i];
                validations[i] = validations[j];
                validations[j] = temp;
            }
        }
    }

    for(int i= 0;i<nb_validations;i++){
        printf("[%d] (%d) %s %2d %d/%s (%s)\n",
               validations[i].id_absence,
               validations[i].id_etudiant,
               validations[i].nom_etu,
               validations[i].no_groupe,
               validations[i].jour,
               (validations[i].demi_journee == AM)?"am":"pm",
               validations[i].excuse);

    }

}

//-----------------C6-----------------//
//void validation(){
//    if (strcmp(am_pm, "am") == 0) {
//        demi_journee = AM;
//    } else if (strcmp(am_pm, "pm") == 0) {
//        demi_journee = PM;
//    } else {
//        printf("Demi-journee incorrecte \n");
//        return;
//    }
//
//
//
//
//
//
//
//
//}



void situation_etudiant (Etudiant etudiants[], int nb_etudiants) {

    int no_etudiant;
    int jour;

    scanf("%d %d", &no_etudiant, &jour);
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

    //pour acceder à l'etudiant
    Etudiant* etu = &etudiants[no_etudiant - 1];

    //affichage
    printf("(%d) %s %d %d\n", no_etudiant, etu->nom_etu, etu->no_groupe, etu->nb_absences);

    bool type_absence_affiche = false;

    // Catégorie en attente justificatif
    for (int i = 0; i < etu->nb_absences; i++) {
        Absence* absence = &etu->absences[i];
        if (absence->jour <= jour && absence->statut_excuse == A_FOURNIR) {
            if (!type_absence_affiche) {
                printf("- En attente justificatif\n");
                type_absence_affiche = true;  // affiche la catégorie une seule fois
            }
            printf("[%d] %d/%s\n", i + 1, absence->jour, absence->demi_journee == AM ? "am" : "pm");
        }
    }

    type_absence_affiche = false;  // Réinitialiser pour la catégorie suivante

    //Catégorie en attente de validation
    for (int i = 0; i < etu->nb_absences; i++) {
        Absence* absence = &etu->absences[i];
        if (absence->jour <= jour && absence->statut_excuse == A_VALIDER) {
            if (!type_absence_affiche) {
                printf("- En attente validation\n");
                type_absence_affiche = true;
            }
            printf("[%d] %d/%s (%s)\n", i + 1, absence->jour, absence->demi_journee == AM ? "am" : "pm", absence->excuse);
        }
    }

    type_absence_affiche = false;

    //Catégorie justifiées
    for (int i = 0; i < etu->nb_absences; i++) {
        Absence* absence = &etu->absences[i];
        if (absence->jour <= jour && absence->statut_excuse == ACCEPTEE) {
            if (!type_absence_affiche) {
                printf("- Justifiees\n");
                type_absence_affiche = true;
            }
            printf("[%d] %d/%s (%s)\n", i + 1, absence->jour, absence->demi_journee == AM ? "am" : "pm", absence->excuse);
        }
    }

    type_absence_affiche = false;

    // Catégorie non-justifiées
    for (int i = 0; i < etu->nb_absences; i++) {
        Absence* absence = &etu->absences[i];
        if (absence->jour <= jour && absence->statut_excuse == REFUSEE) {
            if (!type_absence_affiche) {
                printf("- Non-justifiees\n");
                type_absence_affiche = true;
            }
            printf("[%d] %d/%s (%s)\n", i + 1, absence->jour, absence->demi_journee == AM ? "am" : "pm", absence->excuse);
        }
    }
}


//----------Main------------//
int main() {

    Etudiant etu;
    Etudiant etudiants[LIMITE];
    int nb_etudiants = 0;
    char input[LONGUEUR_MAX_COMMANDE+1];
    int nb_absences_total=0;


    do {
        scanf("%s", input);
        if (strcmp(input, "inscription") == 0) { //----------C1---------//
            inscription(etudiants, &nb_etudiants);

        } else if (strcmp(input, "absence") == 0) { //----------*C2*---------//
            absence(etudiants, nb_etudiants, &nb_absences_total);

        } else if (strcmp(input, "etudiants") == 0) { //----------*C3*---------//
            liste_etudiants(etudiants, nb_etudiants);

        } else if (strcmp(input, "justificatif") == 0) { //---------*C4*----------//
            depot_justificatif(etudiants, nb_etudiants, nb_absences_total);
        }
        else if (strcmp(input, "validations") == 0){ //----------*C5*---------//
            validations(etudiants, nb_etudiants);
        }
        else if (strcmp(input, "validation") == 0){ //---------*C6*----------//
           // validation();
        }
        else if (strcmp(input, "etudiant") == 0){ //---------*C7*-----------//
            void situation_etudiant(etudiants, nb_etudiants);
        }
        else if (strcmp(input, "exit") == 0) { //---------*C4*----------//
            break;
        }
        else {
            printf("Commande inconnue\n");
        }
    } while (strcmp(input, "exit") != 0); //--------C0-----------//
}

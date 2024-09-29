//#ifndef SAE_C_INSCRIPTION_H
//#define SAE_C_INSCRIPTION_H
//
//enum{LONGUEUR_MAX=30, LIMITE=100 };
//
//typedef struct{
//    char nom_etu[LONGUEUR_MAX];
//    int no_groupe;
//    int id;
//}Etudiants ;
//
//
//Etudiants etudiants[LIMITE];
//
//void inscription(char*nom_etu, int no_groupe ) {
//
//    int nb_etudiants=0;
//
//
//    if (nb_etudiants < LIMITE) {
//        if (!existe_etudiant(nom_etu, no_groupe)) {
//            etudiants[LIMITE].id = nb_etudiants + 1;
//            strcpy(etudiants[nb_etudiants].nom_etu, nom_etu);
//            etudiants[nb_etudiants].no_groupe = no_groupe;
//            nb_etudiants++;
//            printf("Inscription enregistree (%d)\n", nb_etudiants);
//        }
//        else  {
//            printf("Nom incorrect\n");
//        }
//    }
//    else {
//        printf("Erreur : nombre maximum d'étudiants atteint\n");
//    }
//}
//
//
//// ---------------------------existe etudiant a finir et C1 finis  ----------------------------
//#endif //SAE_C_INSCRIPTION_H

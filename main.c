#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#include "inscription .h"

int get_int(char* ch) {
    int x;
    sscanf(ch, "%d", &x);
    return x;
}


    int main(int argc, char** argv){
        
        int run = 1;
        
        char entree[200];
        char* elements_entree[10];
        int nb_params = 0;

        while (run) {  
            scanf("%[^\n]", &entree);
            fgetc(stdin);

            const char* separators = " ";
            nb_params = 0;

            // On cherche à récupérer, un à un, tous les mots (token) de la phrase
            // et on commence par le premier.
            char* strToken = strtok(entree, separators);
            while (strToken != NULL) {
                printf("%s\n", strToken);
                elements_entree[nb_params++]  = strdup(strToken);
                // On demande le token suivant.
                strToken = strtok(NULL, separators);
            }
            
            printf("Nb params: %d\n", nb_params);

            for (int i = 0; i < nb_params; i++)
            {
                printf("%d %s\n", i, elements_entree[i]);
            }

            if (strcmp("exit", elements_entree[0]) == 0) {
                run = 0;
            }
            else if (strcmp("inscription", elements_entree[0]) == 0 && nb_params == 3) {

                inscription(elements_entree[1], get_int(elements_entree[2]));
            }

            // libere la chaine allouee par le strdup
            for (int i = 0; i < nb_params; i++) {
                free(elements_entree[i]);
            }

        }


        //inscription(nom_etu,no_groupe);


       exit(EXIT_FAILURE); //---------------C0-----------------------

        }


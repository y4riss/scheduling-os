#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"




int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr,"Utilisation : %s nom_fichier",argv[0]);
        return 1;
    }

    Processus* processus = parse_file(argv[1]);

    while (processus->date_arrivee != -1)
    {
        printf("nom : %s\n",processus->nom);
        printf("date arrivee : %d ms\n",processus->date_arrivee);
        printf("temps de traitement : %d ms\n",processus->duree_cycle);
        processus++;
    }
    free(processus);

    return 0;
}

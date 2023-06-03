#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nom[50];
    int date_arrivee;
    int duree_cycle;
} Processus;


Processus *parse_file(const char* filename) {

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr,"Impossible d'ouvrir le fichier de configuration.\n");
        exit(1);
    }

    // younes

    char buffer[256];
    char *ptr = NULL;
    int nb_processus;
    int line = -1;
    Processus *processus = NULL; // tableau de process

    // get line by line
    while (fgets(buffer, sizeof(buffer), file)) {

        // skip whitespaces
        ptr = buffer;
        while(*ptr && (*ptr > 0 && *ptr < 33 )) ptr++;
        if (!(*ptr) || *ptr == '\n' || *ptr == '#') {
            continue;
        }

        if (line == -1)
        {
            sscanf(ptr, "%d",&nb_processus);
            line++;
            processus = malloc(( nb_processus + 1) * sizeof(Processus));
            processus[nb_processus].date_arrivee = -1;
            continue;
        }

        Processus p;
        sscanf(ptr, "%s %d %d", p.nom, &p.date_arrivee, &p.duree_cycle);
        processus[line++] = p;
    }


    fclose(file);
    return processus;
}

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

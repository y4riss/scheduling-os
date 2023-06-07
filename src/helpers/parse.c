#include "utils.h"



Processus *parse_file(const char* filename) {

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr,"Impossible d'ouvrir le fichier de configuration.\n");
        exit(1);
    }

    char buffer[256];
    char *ptr = NULL;
    nb_processus = 0;
    
    Processus *processus = malloc(256 * sizeof(Processus));// tableau de process
    Processus p;


    // get line by line
    while (fgets(buffer, sizeof(buffer), file) && nb_processus < 256) {

        // skip whitespaces
        ptr = buffer;
        while(*ptr && (*ptr > 0 && *ptr < 33 )) ptr++;
        if (!(*ptr) || *ptr == '\n' || *ptr == '#') {
            continue;
        }

        sscanf(ptr, "%s %d %d", p.nom, &p.date_arrivee, &p.duree_cycle);
        processus[nb_processus] = p;
        processus[nb_processus].finished = 0;
        processus[nb_processus].index = 0;
        processus[nb_processus].last_total_execution = 0;


        nb_processus++;
    }
    processus[nb_processus].date_arrivee = -1;
    processus = realloc(processus, nb_processus * sizeof(Processus));
    fclose(file);
    return processus;
}
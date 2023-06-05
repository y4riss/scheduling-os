#include "utils.h"



Processus *parse_file(const char* filename) {

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr,"Impossible d'ouvrir le fichier de configuration.\n");
        exit(1);
    }

    char buffer[256];
    char *ptr = NULL;
    
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
            continue;
        }

        Processus p;
        sscanf(ptr, "%s %d %d", p.nom, &p.date_arrivee, &p.duree_cycle);
        processus[line++] = p;
    }
    processus[line].date_arrivee = -1;
    fclose(file);
    return processus;
}
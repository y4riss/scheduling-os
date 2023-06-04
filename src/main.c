#include "utils.h"




int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr,"Utilisation : %s nom_fichier",argv[0]);
        return 1;
    }

    Processus* processus = parse_file(argv[1]);

    menu();
    free(processus);

    return 0;
}

#include "utils.h"




int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr,"Utilisation : %s nom_fichier",argv[0]);
        return 1;
    }
    Processus* processus = parse_file(argv[1]);
    int choice;
    algorithm_functions functions[5];
    menu(functions);
    printf("Algorithm > ");
    scanf("%d",&choice);
    functions[choice](processus);

    free(processus);
    return 0;
}

#include "utils.h"




int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr,"Utilisation : %s nom_fichier",argv[0]);
        return 1;
    }
    Processus* processus = parse_file(argv[1]);
    // int choice;
    // algorithm_functions functions[5];
    
    // printf("before sorting...\n");
    dump(processus);

    // sort_process(processus);

    // printf("after sorting...\n");
    // dump(processus);
    
    // menu(functions);
    // printf("choose : ");
    // scanf("%d",&choice);
    // functions[choice](processus);

    free(processus);
    return 0;
}

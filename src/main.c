#include "utils.h"




int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr,"Utilisation : %s nom_fichier",argv[0]);
        return 1;
    }
    char choice;
    int nb_of_functions;

    Processus* processus = parse_file(argv[1]);
    algorithm_functions functions[5];
    menu(functions,&nb_of_functions);
    if (nb_of_functions == 0)
    {
        fprintf(stderr,"no available algorithms to execute\n");
        return 1;
    }
    while (1) {
    printf("Algorithm > ");
    choice = getchar();
    if (choice == '\n' || choice == '\r') continue;
    while(getchar() != '\n'); // To consume the newline character

    if ( '1' <= choice && choice <= (nb_of_functions + 48) )
        break;
    else
        printf("Invalid input.\n");
    }
    functions[choice - 48](processus);
    free(processus);
    return 0;
}

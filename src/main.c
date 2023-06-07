#include "utils.h"

void get_user_input(algorithm_functions *functions, int n, Processus *processus)
{
    char choice;

    if (n == 0)
    {
        fprintf(stderr,"no available algorithms to execute\n");
        exit(1);
    }
    while (1) {
    printf("Algorithm > ");
    choice = getchar();
    if (choice == '\n' || choice == '\r') continue;
    while(getchar() != '\n'); // To consume the newline character

    if ( '1' <= choice && choice <= (n + 48) )
        break;
    else
        printf("Invalid input.\n");
    }
    functions[choice - 48](processus);
}


int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr,"Utilisation : %s nom_fichier",argv[0]);
        return 1;
    }
    int nb_of_functions;
    algorithm_functions functions[10];
    Processus* processus;

    processus = parse_file(argv[1]);
    menu(functions,&nb_of_functions);
    get_user_input(functions, nb_of_functions, processus);
    
    free(processus);
    return 0;
}

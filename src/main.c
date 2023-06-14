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
    printf("\n\nAlgorithm > ");
    choice = getchar();
    if (choice == '\n' || choice == '\r') continue;
    while(getchar() != '\n'); // To consume the newline character

    if ( '1' <= choice && choice <= (n + 48) )
        break;
    else
        printf("Invalid input.\n");
    }
    functions[choice - 48](processus); // execute algorithm
}


int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr,"Utilisation : %s nom_fichier",argv[0]);
        return 1;
    }
    int nb_of_functions;
    int choix;

    algorithm_functions functions[10];
    Processus* processus;

    while (1)
    {
        printf("\033[2J\033[H");
        processus = parse_file(argv[1]);
        menu(functions,&nb_of_functions);
        get_user_input(functions, nb_of_functions, processus);
        free(processus);
        
        printf("Vous voulez afficher le menu ?\n");
        printf("\t1 - Afficher menu\n\t2 - Quitter\n");
        printf("Votre choix > ");
        scanf("%d",&choix);
        while(getchar() != '\n'); 
        if (choix != 1)
            break;        
    }
    
    return 0;
}

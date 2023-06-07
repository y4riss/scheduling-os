#include "utils.h"


void plot_diagram(Processus *processus)
{
    int i;
    int j;
    int k;
    int l;
    int x;

    x = 0;

    printf("\n\n\t\t------Diagramme de Gantt------\n\n");

    //first vertical lines
    for(i = 0 ; i < 3 ; i++)
    {   
        char c;
        l = 0;

        if (i == 0) c = '^';
        else c = '|';
        puts("");
        while (l++ <= SPACE) printf(" ");
        printf(" %c",c);
    }


    for(i = 0 ; i < nb_processus; i++)
    {
        puts("");
        l = strlen(processus[i].nom);
        while (l++ <= SPACE ) printf(" ");

        printf("%s |",processus[i].nom);
        for(j = 0 ; j < processus[i].temps_datt[0] + processus[i].date_arrivee ;  j++) printf(" ");
        for(k = 0 ; k < processus[i].duree_cycle ; k++) printf("-");
        x+= processus[i].duree_cycle;
    }

    // last vertical lines
    for(i = 0 ; i < 3 ; i++)
    {   
        l = 0;
        puts("");
        while (l++ <= SPACE) printf(" ");
        if (i == 2) printf("  ");
        else
        printf(" |");
    }
    for(k = 0 ; k < x + 20 ; k++) printf("-");
    printf(">\n\n");
}
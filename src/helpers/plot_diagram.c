#include "utils.h"


void plot_diagram(Processus *processus)
{
    int i;
    int j;
    int k;
    int l;
    int x;
    int total_execution;

    x = 0;
    total_execution = 0;

    printf("\n\n----------------------Diagram de Gantt----------------------\n\n");

    //first lines
    for(i = 0 ; i < 3 ; i++)
    {   
        char c;
        l = 0;

        if (i == 0) c = '^';
        else c = '|';
        puts("");
        while (l++ <= 20) printf(" ");
        printf(" %c",c);
    }


    for(i = 0 ; i < nb_processus; i++)
    {
        puts("");
        l = strlen(processus[i].nom);
        while (l++ <= 20 ) printf(" ");

        printf("%s |",processus[i].nom);
        for(j = 0 ; j < total_execution;  j++) printf(" ");
        for(k = 0 ; k < processus[i].duree_cycle ; k++) printf("-");
        x+= processus[i].duree_cycle;
        total_execution += processus[i].duree_cycle;
    }

    // last lines
    for(i = 0 ; i < 3 ; i++)
    {   
        l = 0;
        puts("");
        while (l++ <= 20) printf(" ");
        if (i == 2) printf("  ");
        else
        printf(" |");
    }
    for(k = 0 ; k < x + 20 ; k++) printf("-");
    printf(">\n\n");
}
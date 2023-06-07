#include "utils.h"


void plot_diagram_preemptif(Processus *processus, int quantum)
{
    int i;
    int j;
    int k;
    int l;
    int cycle;
    int condition;


    printf("\n\n----------------------Diagram de Gantt----------------------\n\n");

    //first vertical lines
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

        cycle = 0;
        for(j = 0 ; j <= processus[i].index ; j++) // loop through temps dattente
        {
            if (j == 0)
                condition = processus[i].temps_datt[j] + processus[i].date_arrivee;
            else
                condition = processus[i].temps_datt[j];
            for(k = 0 ; k <  condition ; k++) printf(" ");
            cycle = min(quantum, processus[i].duree_cycle);
            processus[i].duree_cycle -= cycle;
            for(k = 0 ; k < cycle ; k++) printf("_");

        }
    }

    // last vertical lines
    for(i = 0 ; i < 3 ; i++)
    {   
        l = 0;
        puts("");
        while (l++ <= 20) printf(" ");
        if (i == 2) printf("  ");
        else
        printf(" |");
    }
    for(k = 0 ; k < 60 ; k++) printf("-");
    printf(">\n\n");
}
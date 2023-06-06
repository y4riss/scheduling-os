#include "utils.h"



void sjf(Processus* processus)
{
    
    int *temps_att, *temps_rot, i, j , k;
    int total_execution;

    temps_att = malloc(sizeof(int) * nb_processus);
    temps_rot = malloc(sizeof(int) * nb_processus);
    Processus processus_in_order[256];
    int finished[256] = {0};
    Processus shortest;

    sort_by_date_arrivee(processus);
    puts("");

    temps_att[0] = 0;
    temps_rot[0] = processus[0].duree_cycle;
    total_execution = processus[0].duree_cycle;
    processus_in_order[0] = processus[0];
    finished[0] = 1;

    printf("\nProcessus \t|Temps d'attente \t |Temps de rotation\n");
    for(i = 0; i < 30; i++) printf("--");
    i = 0;
    printf("\n%s\t\t|%d\t\t\t |%d",processus_in_order[i].nom,temps_att[i],temps_rot[i]);

    for(i = 1 ; i < nb_processus ; i++)
    {
        // select the shortest process
        shortest.duree_cycle = 0x7fffffff;
        for(j = 1 ; j < nb_processus ; j++)
        {
            if (finished[j] == 0 && processus[j].date_arrivee <= total_execution ) // process arrived and hasnt been treated yet
            {
                if (processus[j].duree_cycle < shortest.duree_cycle)
                {
                    shortest = processus[j]; // update shortest process
                    k = j;                   // save shortest index to marke it finished
                }

            }
        }
        processus_in_order[i] = shortest; 
        finished[k] = 1; // marke the shortest process as finished

        // calculate rotation and waiting time
        temps_att[i] = total_execution - processus_in_order[i].date_arrivee;
        temps_rot[i] = temps_att[i] + processus_in_order[i].duree_cycle;
        total_execution += processus_in_order[i].duree_cycle;
        printf("\n%s\t\t|%d\t\t\t |%d",processus_in_order[i].nom,temps_att[i],temps_rot[i]);
    }

    puts("\n");
    plot_diagram(processus_in_order); 
    free(temps_att);
    free(temps_rot);
}
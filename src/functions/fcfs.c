#include "utils.h"


void print_table(Processus *processus, float avtemps_att, float avtemps_rot)
{
    int i;

    printf("\nProcessus \t|Temps d'attente \t |Temps de rotation\n");
    for(i = 0; i < 30; i++) printf("--");

    for(i=0; i<nb_processus; i++)
        printf("\n%s\t\t|%d\t\t\t |%d",processus[i].nom, processus[i].temps_datt, processus[i].rot);
 
    puts("");
    for(i = 0; i < 30; i++) printf("--");
    printf("\nMoyenne\t\t|%0.2f\t\t\t |%0.2f\n", avtemps_att, avtemps_rot);
    
}
void fcfs(Processus* processus)
{

    int     i;
    int     j;
    int     k;
    int     total_execution;
    float   avtemps_att;
    float   avtemps_rot;
    Processus p; // tmp to save current process to handle


    avtemps_att = 0;
    avtemps_rot = 0;
    total_execution = 0;

    for(i =0 ; i < nb_processus; i++)
    {
        p.date_arrivee = 0x7ffffff;
        for(j = 0 ; j < nb_processus ; j++)
        {
            if (processus[j].finished == 0 && processus[j].date_arrivee < p.date_arrivee)
            {
                p = processus[j];
                k = j; // save process index
            }
        }
        processus[k].finished = 1; // marke it as finished
        processus[k].temps_datt = total_execution -  processus[k].date_arrivee;    // calculate waiting time
        processus[k].rot = total_execution + processus[k].duree_cycle - processus[k].date_arrivee;  // burst time ( rotation )
        avtemps_att += processus[k].temps_datt;
        avtemps_rot += processus[k].rot;

        total_execution += processus[k].duree_cycle;
    }
    avtemps_att /= nb_processus;
    avtemps_rot /= nb_processus;

    print_table(processus, avtemps_att, avtemps_rot);
    plot_diagram(processus); 
}
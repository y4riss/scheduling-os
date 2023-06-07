#include "utils.h"



void sjf(Processus* processus)
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
        p.duree_cycle = 0x7ffffff;
        for(j = 0 ; j < nb_processus ; j++)
        {
    if (processus[j].finished == 0 && processus[j].date_arrivee <= total_execution && processus[j].duree_cycle < p.duree_cycle )
    {
        p = processus[j];
        k = j; // save process index
    }
        }
        processus[k].finished = 1; // marke it as finished
        processus[k].temps_datt[0] = total_execution -  processus[k].date_arrivee;    // calculate waiting time
        processus[k].rot[0] = (total_execution - processus[k].date_arrivee) + processus[k].duree_cycle ;  // burst time ( rotation )
        avtemps_att += processus[k].temps_datt[0];
        avtemps_rot += processus[k].rot[0];

        total_execution += processus[k].duree_cycle;
    }
    avtemps_att /= nb_processus;
    avtemps_rot /= nb_processus;

    print_table(processus, avtemps_att, avtemps_rot);
    plot_diagram(processus); 
}
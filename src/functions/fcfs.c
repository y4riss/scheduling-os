#include "utils.h"


void fcfs(Processus* processus)
{
    int *temps_att, *temps_rot, avtemps_att=0, avtemps_rot=0, i, j;
    
    temps_att = malloc(sizeof(int) * nb_processus);
    temps_rot = malloc(sizeof(int) * nb_processus);

    temps_att[0] =0;

    for(i=1; i<nb_processus; i++)
    {
        temps_att[i] =0;
        for(j=0; j<i; j++)
            temps_att[i] += processus[j].duree_cycle;
    }
 
    printf("\nProcessus\tTemps de traitement\tTemps d'attent \t Temps de Rotemps_rotion\n");

    for(i=0; i<nb_processus; i++)
    {
        temps_rot[i] = processus[i].duree_cycle+temps_att[i];
        avtemps_att += temps_att[i];
        avtemps_rot += temps_rot[i];
        printf("\n%s\t\t%d\t\t\t%d\t\t%d",processus[i].nom,processus[i].duree_cycle,temps_att[i],temps_rot[i]);
    }
 
    avtemps_att /=i;
    avtemps_rot /=i;

    printf("\n\nMoyenne\t\t\tx\t\t\t%d\t\t%d\n",avtemps_att,avtemps_rot);
    
    free(temps_att);
    free(temps_rot);    
}
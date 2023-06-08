#include "utils.h"


void print_table(Processus *processus, float avtemps_att, float avtemps_rot)
{
    int i;
    float rendement;
    float avg_rendement;

    avg_rendement = 0; 
    printf("\n\n\t\t---------------------------\n\n");

    printf("\nProcessus \t|Temps d'attente \t |Temps de rotation \t |Rendement \n");
    for(i = 0; i < 40; i++) printf("--");

    for(i=0; i<nb_processus; i++)
    {
        rendement = ((float)(processus[i].rot[0] - processus[i].temps_datt[0]) / (float)processus[i].rot[0]);
        avg_rendement += rendement;
        printf("\n%s\t\t|%d\t\t\t |%d\t\t\t |%.2f",processus[i].nom, processus[i].temps_datt[0], processus[i].rot[0], rendement);
    }
    avg_rendement /= nb_processus;
    puts("");

    for(i = 0; i < 40; i++) printf("--");
    printf("\nMoyenne\t\t|%0.2f\t\t\t |%0.2f\t\t\t |%.2f\n", avtemps_att, avtemps_rot, avg_rendement);
    puts("\n");
    
}

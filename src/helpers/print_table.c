#include "utils.h"


void print_table(Processus *processus, float avtemps_att, float avtemps_rot)
{
    int i;

    printf("\nProcessus \t|Temps d'attente \t |Temps de rotation\n");
    for(i = 0; i < 30; i++) printf("--");

    for(i=0; i<nb_processus; i++)
        printf("\n%s\t\t|%d\t\t\t |%d",processus[i].nom, processus[i].temps_datt[0], processus[i].rot[0]);
 
    puts("");
    for(i = 0; i < 30; i++) printf("--");
    printf("\nMoyenne\t\t|%0.2f\t\t\t |%0.2f\n", avtemps_att, avtemps_rot);
    
}

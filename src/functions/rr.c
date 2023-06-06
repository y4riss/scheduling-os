#include "utils.h"

void round_robin(Processus *processus)
{
    int *temps_att, /**temps_rot,*/ quantum, i;
    // int total_execution;
    int compteur =0;
    temps_att = malloc(sizeof(int) * nb_processus);
    // temps_rot = malloc(sizeof(int) * nb_processus);

    printf("Entrez une valeur pour quantum : ");
    scanf("%i",&quantum);

    sort_process(processus);


    for (int i = 0; i < nb_processus; ++i)
    {
        temps_att[i]=0;
        temps_att[i]-=processus[i].date_arrivee;
    }
printf("%i",nb_processus);
    while (compteur < nb_processus)
    {
        for (i = 0; i < nb_processus-1; ++i)
        {
            if (processus[i].duree_cycle >0)
            {
                if (processus[i].duree_cycle > quantum)
                {
                    processus[i].duree_cycle -= quantum;
                    temps_att[i+1] = temps_att[i] + quantum;
                }
                else
                {
                    temps_att[i+1] = temps_att[i] + processus[i].duree_cycle;
                    processus[i].duree_cycle -= quantum;
                }
            }
            printf("--");
            if (processus[i].duree_cycle <= 0)
            {
                compteur+=1;
                printf("%i",compteur);
            }
            printf("--");
        }

        if (processus[0].duree_cycle >0)
        {
            temps_att[0]=temps_att[i]+quantum; 
        }
        printf("/%i/",compteur);
    }

    printf("\nProcessus \t|Temps d'attente");
    for (int i = 0; i < nb_processus; ++i)
    {
        printf("\n%s\t\t|%d",processus[i].nom,temps_att[i]);
    }


}
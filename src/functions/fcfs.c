#include "utils.h"

void draw(Processus *processus,int *temps_att)
{
    int i;
    int j;
    int k;
    int l;
    int x;

    x = 0;

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
        for(j = 0 ; j < temps_att[i]; j++) printf(" ");
        for(k = 0 ; k < processus[i].duree_cycle ; k++) printf("-");
        x+= processus[i].duree_cycle;
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

void fcfs(Processus* processus)
{
    int *temps_att, *temps_rot, avtemps_att=0, avtemps_rot=0, i, j;
    
    temps_att = malloc(sizeof(int) * nb_processus);
    temps_rot = malloc(sizeof(int) * nb_processus);
    sort_process(processus);

    temps_att[0] =0;

    for(i=1; i<nb_processus; i++)
    {
        temps_att[i] =0;
        for(j=0; j<i; j++)
            temps_att[i] += processus[j].duree_cycle;
    }
 
    printf("\nProcessus \t|Temps d'attente \t |Temps de rotation\n");
    for(i = 0; i < 30; i++) printf("--");

    for(i=0; i<nb_processus; i++)
    {
        temps_rot[i] = processus[i].duree_cycle+temps_att[i];
        avtemps_att += temps_att[i];
        avtemps_rot += temps_rot[i];
        printf("\n%s\t\t|%d\t\t\t |%d",processus[i].nom,temps_att[i],temps_rot[i]);
    }
 
    avtemps_att /=i;
    avtemps_rot /=i;

    puts("");
    for(i = 0; i < 30; i++) printf("--");
    printf("\nMoyenne\t\t|%d\t\t\t |%d\n",avtemps_att,avtemps_rot);
    
    draw(processus, temps_att); 
    free(temps_att);
    free(temps_rot);
}
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

    plot_diagram(processus); 
    print_table(processus, avtemps_att, avtemps_rot);
}

void sjf_preemptif(Processus *processus)
{
     int     i;
    int     j;
    int     k;
    int     saved_index;
    int     cycle;
    int     quantum;
    int available;
    int     total_execution;
    float   avtemps_att;
    float   avtemps_rot;
    
    ready_queue queue;
    Processus *p; // tmp to save current process to handle
    Processus tmp;


    quantum = 1;
    avtemps_att = 0;
    avtemps_rot = 0;
    total_execution = 0;
    queue.front = 0;
    queue.tail = 0;

    //determine the first process to arrive
    tmp.date_arrivee = 0x7fffffff;
    tmp.duree_cycle  = 0x7fffffff;
    for( i = 0 ; i < nb_processus ; i++)
    {
        if (processus[i].date_arrivee < tmp.date_arrivee)
        {
            tmp = processus[i];
            k = i;
        }
        else if (processus[i].date_arrivee == tmp.date_arrivee && processus[i].duree_cycle < tmp.duree_cycle)
        {
            tmp = processus[i];
            k = i;
        }
    }
    
    // queue the process into the queue
    queue.processus[queue.tail++] = k;
    p = &processus[k];
    while (queue.tail != queue.front)
    {

        // grab the first item from the queue
        saved_index = queue.processus[queue.front];
        p = &processus[saved_index];
        queue.front++;  // dequeue it

        //update its waiting , burst time , duree_cycle and quantum
        if (p->index == 0)
            p->temps_datt[0] = total_execution -  p->date_arrivee; 
        else
            p->temps_datt[p->index] = total_execution - p->last_total_execution;   // calculate waiting time
        
        cycle = min(p->duree_cycle, quantum);
        total_execution += cycle;
        p->rot[p->index] =  p->temps_datt[p->index]+ cycle;  // burst time ( rotation )
        p->duree_cycle -= cycle;
        if (p->duree_cycle <= 0)
        {
             p->finished = 1;
             p->duree_cycle = 0;
        }

        p->last_total_execution = total_execution;
        avtemps_att +=p->temps_datt[p->index];
        avtemps_rot +=p->rot[p->index];

        //determine the processes to queue

        tmp.date_arrivee = 0x7fffffff;
        tmp.duree_cycle = 0x7fffffff;
        available = 0;
        for(j = 0 ; j < nb_processus ; j++)
        {
            if (processus[j].finished == 0)
            {
                if (processus[j].date_arrivee <= total_execution) // if process is ready
                    {
                        if ((processus[j].duree_cycle < tmp.duree_cycle)
                        || (processus[j].duree_cycle == tmp.duree_cycle && processus[j].date_arrivee < tmp.date_arrivee)) // determine the ordrer
                        {
                            tmp = processus[j];
                            k = j;
                            available = 1;
                        }
                    }
            }
        }
        if (available == 1)
            queue.processus[queue.tail++] = k;


        if (p->finished == 0)
            p->index++;
        else
            p->duree_cycle = p->initial_duree_cycle;
        
    }

    plot_diagram_preemptif(processus, quantum);

    for(i = 0 ; i < nb_processus ; i++)
    {
        for(j = 1 ; j <= processus[i].index ; j++)
        {
            processus[i].temps_datt[0] += processus[i].temps_datt[j];
            processus[i].rot[0] += processus[i].rot[j];
        }
    }
    print_table(processus,avtemps_att/nb_processus, avtemps_rot/nb_processus);
}

void sjf_choice(Processus *processus)
{
    char choice;

    printf("\t\t1 - non preemptif\n");
    printf("\t\t2 - preemptif\n");
   
    while (1) {
        printf("Algorithm[sjf] > ");
        choice = getchar();
        if (choice == '\n' || choice == '\r') continue;
        while(getchar() != '\n'); // To consume the newline character

        if (choice == '1' || choice == '2') {
            break;
        } else {
            printf("Invalid input.\n");
        }
    }
    if (choice == '1') 
    {
        printf("Algorithme[SJF] : Shortest job first non preemptif.\n");
        sjf(processus);
    }
    else 
    {
        printf("Algorithme[SJF]: Shortest job first(sjf) preemptif.\n");
        sjf_preemptif(processus);
    }
}
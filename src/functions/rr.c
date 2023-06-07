#include "utils.h"



void round_robin(Processus *processus)
{
    int     i;
    int     j;
    int     k;
    int     saved_index;
    int     cycle;
    int     quantum;
    int     total_execution;
    float   avtemps_att;
    float   avtemps_rot;
    ready_queue queue;
    Processus *p; // tmp to save current process to handle
    Processus tmp;


    quantum = 3;
    avtemps_att = 0;
    avtemps_rot = 0;
    total_execution = 0;
    queue.front = 0;
    queue.tail = 0;

    //determine the first process to arrive
    tmp.date_arrivee = 0x7fffffff;
    for( i = 0 ; i < nb_processus ; i++)
    {
        if (processus[i].date_arrivee < tmp.date_arrivee)
        {
            tmp = processus[i];
            k = i;
        }
    }
    
    // queue the process into the queue
    queue.processus[queue.tail++] = k;
    p = &processus[k];
    p->queued = 1;
    dump(processus);
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

        printf("%s[%d] ",p->nom,total_execution);
        p->last_total_execution = total_execution;
        avtemps_att +=p->temps_datt[p->index];
        avtemps_rot +=p->rot[p->index];

        printf("%s | rot = %d\n",p->nom, p->rot[p->index]);
        //determine the processes to queue
        for(i = 0 ; i < nb_processus ; i++)
        {
            tmp.date_arrivee = 0x7fffffff;
            for(j = 0 ; j < nb_processus ; j++)
            {
                if (processus[j].queued == 0 && processus[j].date_arrivee <= total_execution) // if process is ready
                {
                    if(processus[j].date_arrivee < tmp.date_arrivee) // determine the ordrer
                    {
                        tmp = processus[j];
                        k = j;
                    }
                }
            }
            if (processus[k].queued == 0)
            {
                queue.processus[queue.tail++] = k;
                processus[k].queued = 1;    
            }
        }

        //check if current process has finished , if not , queue it.
        if (p->finished == 0)
        {
            queue.processus[queue.tail++] = saved_index ;
            p->index++;

        }
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




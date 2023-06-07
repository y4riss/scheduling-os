#include "utils.h"

void round_robin(Processus *processus)
{
    int     i;
    int     j;
    int     k;
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
            tmp = processus[i];
    }
    
    // queue the process into the queue
    queue.processus[queue.tail++] = tmp;
    tmp.queued = 1;
    dump(processus);
    while (queue.tail != queue.front)
    {

        // is the first item of the queue.
        p = &queue.processus[queue.front];
        queue.front++;  // dequeue it

        //update its waiting , burst time , duree_cycle and quantum
        if (p->index == 0)
            p->temps_datt[0] = total_execution -  p->date_arrivee; 
        else
            p->temps_datt[p->index] = total_execution - p->last_total_execution;   // calculate waiting time
        
        cycle = min(p->duree_cycle, quantum);
        p->rot[tmp.index] =  p->temps_datt[p->index]+ cycle;  // burst time ( rotation )
        processus[k].duree_cycle -= quantum;
        if (p->duree_cycle <= 0)
        {
             p->finished = 1;
             p->duree_cycle = 0;
        }
        total_execution += p->duree_cycle;
        printf("%s ",p->nom);
        p->last_total_execution = total_execution;
        avtemps_att +=p->temps_datt[tmp.index];
        avtemps_rot +=p->rot[tmp.index];
        p->index++;

        //determine the processes to queue
        tmp.date_arrivee = 0x7fffffff;
        for(i = 0 ; i < nb_processus ; i++)
        {
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
                queue.processus[queue.tail++] = processus[k];
                processus[k].queued = 1;    
            }
        }

        //check if current process has finished , if not , queue it.
        if (p->finished == 0)
                queue.processus[queue.tail++] = processus[k];
    }

}
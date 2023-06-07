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
    Processus p; // tmp to save current process to handle


    quantum = 3;
    avtemps_att = 0;
    avtemps_rot = 0;
    total_execution = 0;
    queue.front = 0;
    queue.tail = 0;

    //determine the first process to arrive
    p.date_arrivee = 0x7fffffff;
    for( i = 0 ; i < nb_processus ; i++)
    {
        if (processus[i].date_arrivee < p.date_arrivee)
            p = processus[i];
    }
    
    // queue the process into the queue
    queue.processus[queue.tail++] = p;
    p.queued = 1;
    dump(processus);
    while (queue.tail != queue.front)
    {

        // is the first item of the queue.
        p = queue.processus[queue.front].nb;
        queue.front++;  // dequeue it

        //update its waiting , burst time , duree_cycle and quantum
        if (processus[p.nb].index == 0)
            processus[p.nb].temps_datt[0] = total_execution -  processus[p.nb].date_arrivee; 
        else
            processus[p.nb].temps_datt[processus[p.nb].index] = total_execution - processus[p.nb].last_total_execution;   // calculate waiting time
        
        cycle = min(processus[p.nb].duree_cycle, quantum);
        processus[p.nb].rot[p.index] =  processus[p.nb].temps_datt[processus[p.nb].index]+ cycle;  // burst time ( rotation )
        processus[k].duree_cycle -= quantum;
        if (processus[p.nb].duree_cycle <= 0)
        {
             processus[p.nb].finished = 1;
             processus[p.nb].duree_cycle = 0;
        }
        total_execution += processus[p.nb].duree_cycle;
        printf("%s ",processus[p.nb].nom);
        processus[p.nb].last_total_execution = total_execution;
        avtemps_att +=processus[p.nb].temps_datt[p.index];
        avtemps_rot +=processus[p.nb].rot[p.index];
        processus[p.nb].index++;

        //determine the processes to queue
        p.date_arrivee = 0x7fffffff;
        for(i = 0 ; i < nb_processus ; i++)
        {
            for(j = 0 ; j < nb_processus ; j++)
            {
                if (processus[j].queued == 0 && processus[j].date_arrivee <= total_execution) // if process is ready
                {
                    if(processus[j].date_arrivee < p.date_arrivee) // determine the ordrer
                    {
                        p = processus[j];
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
        if (processus[p.nb].finished == 0)
                queue.processus[queue.tail++] = processus[k];
    }

}
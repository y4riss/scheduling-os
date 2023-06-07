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


    quantum = 1;
    avtemps_att = 0;
    avtemps_rot = 0;
    total_execution = 0;
    queue.front = 0;
    queue.tail = 0;

    //determine the first process to arrive
    for( i = 0 ; i < nb_processus ; i++)
    {
        p.date_arrivee = 0x7ffffff;
        if (processus[i].date_arrivee < p.date_arrivee)
        {
            p = processus[i];
            k = i;
        }
    }
    
    // queue the process into the queue
    queue.processus[queue.tail++] = processus[k];

    while (queue.tail != queue.front)
    {

  
        p = queue.processus[queue.front];         //get first item of the queue 

        queue.front++;         //dequeue it

        //update its waiting , burst time , duree_cycle and quantum
        if (processus[k].index == 0)
            processus[k].temps_datt[0] = total_execution -  processus[k].date_arrivee; 
        else
            processus[k].temps_datt[processus[k].index] = total_execution - processus[k].last_total_execution;   // calculate waiting time
        
        cycle = min(processus[k].duree_cycle, quantum);
        processus[k].rot[p.index] =  processus[k].temps_datt[processus[k].index]+ cycle;  // burst time ( rotation )
        processus[k].duree_cycle -= quantum;
        if (processus[k].duree_cycle <= 0) processus[k].finished = 1;
        total_execution += processus[k].duree_cycle;
        processus[k].last_total_execution = total_execution;
        avtemps_att +=processus[k].temps_datt[p.index];
        avtemps_rot +=processus[k].rot[p.index];
        processus[k].index++;

        //loop through available processes to queue

        i = 1;
        for(j = 0 ; j < nb_processus ; j++)
        {
            if (j != k && processus[j].finished == 0 && total_execution >= processus[j].date_arrivee)
            {
                if(queue.tail == queue.front)
                {
                    queue.processus[queue.tail++] = processus[j];
                    if (i == 1) {
                        k = j;
                        i = 0;
                    }
                }
                else
                    {
                        p = queue.processus[queue.tail - 1];
                        if (processus[j].date_arrivee <= p.date_arrivee && strcmp(processus[j].nom,p.nom) != 0)
                        {
                            queue.processus[queue.tail++] = processus[j];
                            if (i == 1) {
                                    k = j;
                                    i = 0;}
                        }
                    }
            }
        }

        //check if current process has finished , if not , queue it.
        if (processus[k].finished == 0)
                queue.processus[queue.tail++] = processus[k];
    }

}
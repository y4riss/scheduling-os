#include "utils.h"



void sjf(Processus* processus)
{
    int *temps_att, *temps_rot, avtemps_att=0, avtemps_rot=0, i, j;

    Processus tmp;
    ready_queue queue;




//A B C

//
    temps_att = malloc(sizeof(int) * nb_processus);
    temps_rot = malloc(sizeof(int) * nb_processus);
    sort_process(processus);

    temps_att[0] =0;
    temps_rot[0] = processus[0].duree_cycle;
    queue.processus[queue.tail++] = processus[0];

    while (queue.tail != 0)
    {
        for(i = 1; i < nb_processus ; i++)
            {
                if (temps_rot[0] > processus[i].date_arrivee) // if process i has arrived , push it in the queue
                {
                    //put the element in the queue in ascending order

                    if (queue.tail == 0) // meaning that the queue is empty 
                        queue.processus[queue.tail++] = processus[i]; // put the process in the queue

                    for(j = queue.front ; j < queue.tail ; j++) // if the queue is not empty , loop through it and put the element in the correct place.
                    // according to their burst time.
                    {
                        if (processus[i].duree_cycle < queue.processus[j].duree_cycle)
                        {
                            // shift all processes by one
                            for(k = queue.tail ; k => j ; k--)
                            {
                                queue.processus[k] = queue.process[k + 1];
                            }
                            queue.processus[j] = processus[i]; // insert the process in j, where all processes are ordered by burst time.
                        }
                    }
                }
            }
    }
   

    dump(queue.processus);

}
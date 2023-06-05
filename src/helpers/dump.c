#include "utils.h"


// helper function to list all of the processes.

void dump(Processus *processus)
{
    for(int i = 0 ; i < nb_processus ; i++)
    {
        printf("%i -- %s\n",i + 1,processus[i].nom);
    }
}
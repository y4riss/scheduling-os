#include "utils.h"

void swap(Processus *a, Processus *b)
{
    Processus tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
void sort_process(Processus* processus) {

    int i;
    int j;
    
    for (i = 0; i < nb_processus - 1; i++) {
        for (j = 0; j < nb_processus - i - 1; j++) {
            if (processus[j].date_arrivee > processus[j + 1].date_arrivee) {
                swap(&processus[j], &processus[j + 1]);
            }
            else if (processus[j].date_arrivee == processus[j + 1].date_arrivee
                    && processus[j].duree_cycle > processus[j + 1].duree_cycle)
            {
                swap(&processus[j],&processus[j + 1]);

            }
        }
    }
}

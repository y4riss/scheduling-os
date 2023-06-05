#include "utils.h"

void sort_process(Processus* processus) {

    int i;
    int j;
    Processus tmp;
    
    for (i = 0; i < nb_processus - 1; i++) {
        for (j = 0; j < nb_processus - i - 1; j++) {
            if (processus[j].date_arrivee > processus[j + 1].date_arrivee) {
                tmp = processus[j];
                processus[j] = processus[j + 1];
                processus[j + 1] = tmp;
            }
        }
    }

}

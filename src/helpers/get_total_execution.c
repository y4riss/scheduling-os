#include "utils.h"

int get_total_execution(Processus *processus)
{
    Processus p;
    p.date_arrivee = 0x7ffffff;
    p.duree_cycle = 0x7ffffff;

    for(int i = 0 ; i < nb_processus ; i++)
    {
 if ( processus[i].date_arrivee <= p.date_arrivee && processus[i].duree_cycle < p.duree_cycle )
        p = processus[i];
    }
    return p.date_arrivee;
}
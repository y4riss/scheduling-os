#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

int nb_processus;

typedef struct {

    char nom[20];
    int date_arrivee;
    int duree_cycle;
    int temps_datt;
    int rot;
    int finished;

} Processus;

typedef struct {

    int front;
    int tail;
    Processus processus[256];

} ready_queue;

Processus *parse_file(const char* filename);
void sort_by_date_arrivee(Processus *);
typedef void (*algorithm_functions)(Processus*);
void plot_diagram(Processus *processus);

void fcfs(Processus*);
void round_robin(Processus*);
void sjf(Processus*);
void menu(algorithm_functions*);
void dump(Processus *p);


#endif

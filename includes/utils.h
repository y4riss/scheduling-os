#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define MAX_QUANTUM 20
#define min(a,b) (a<b?a:b)
#define SPACE 14
int nb_processus;

typedef struct {

    char nom[20];
    int date_arrivee;
    int duree_cycle;
    int initial_duree_cycle;
    int temps_datt[256];
    int rot[256];
    int index; // to save temps datt and rotation index
    int finished;
    int last_total_execution;
    int queued;

} Processus;

typedef struct {

    int front;
    int tail;
    int processus[256]; // array representing the queue , it stores indexes of processes

} ready_queue;

Processus *parse_file(const char* filename);
void sort_by_date_arrivee(Processus *);
typedef void (*algorithm_functions)(Processus*);

void plot_diagram(Processus *processus);
void plot_diagram_preemptif(Processus *processus, int quantum);
void print_table(Processus *processus, float avtemps_att, float avtemps_rot);

void fcfs(Processus*);
void round_robin(Processus *processus);
void menu(algorithm_functions*, int *nb_of_functions);
void sjf_choice(Processus *processus);
void dump(Processus *p);



#endif

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

typedef struct {
    char nom[50];
    int date_arrivee;
    int duree_cycle;
} Processus;

Processus *parse_file(const char* filename);
void menu();

#endif

#include "utils.h"

void menu(algorithm_functions* functions, int *nb_of_functions) {
    

    struct dirent *pDirent; // directory entry structure
    char parent_dir[256];
    DIR *pDir;

    getcwd(parent_dir, sizeof(parent_dir)); //get parent directory (scheduling-os)
    char *path = strcat(parent_dir,"/src/functions");
    pDir = opendir(path);
    if (pDir == NULL) {
        fprintf(stderr,"Cannot open directory '%s'\n", path);
        return;
    }
             
    printf("\n########### MENU ########### \n\n");
    int i = 1;
    while ((pDirent = readdir(pDir)) != NULL) {

    if ((pDirent->d_type == DT_REG))
    {
            char *algorithm = strtok(pDirent->d_name,".");
            switch(*algorithm)
            {
                case 'f' : functions[i] = fcfs;
                break;
                case 'r' : functions[i] = round_robin;
                break;
                case 's' : functions[i] = sjf_choice;
                break;
                default : functions[i] = fcfs;
            }
            printf("\t%d - %s\n", i, algorithm);
            i++;
            
    }}
    *nb_of_functions = i - 1;
    closedir(pDir);
    
}
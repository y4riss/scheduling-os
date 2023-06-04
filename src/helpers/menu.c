#include "utils.h"

void menu() {
    
    struct dirent *pDirent;
    char parent_dir[254];
    DIR *pDir;

    getcwd(parent_dir, sizeof(parent_dir));
    char *path = strcat(parent_dir,"/src/functions");
    pDir = opendir(path);
    if (pDir == NULL) {
        fprintf(stderr,"Cannot open directory '%s'\n", path);
        return;
    }

    
    int i = 1;
    while ((pDirent = readdir(pDir)) != NULL) {

    if ((strcmp(pDirent->d_name, ".") != 0 && strcmp(pDirent->d_name, "..") != 0 ) )
    {
            printf("\t%d - %s\n", i, pDirent->d_name);
            i++;
    }}

    closedir(pDir);

}
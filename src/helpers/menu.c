#include "utils.h"

void menu() {
    
    struct dirent *pDirent; // directory entry structure
    char parent_dir[254];
    DIR *pDir;

    getcwd(parent_dir, sizeof(parent_dir)); //get parent directory (scheduling-os)
    char *path = strcat(parent_dir,"/src/functions");
    pDir = opendir(path);
    if (pDir == NULL) {
        fprintf(stderr,"Cannot open directory '%s'\n", path);
        return;
    }

    
    int i = 1;
    while ((pDirent = readdir(pDir)) != NULL) {

    if ((pDirent->d_type == DT_REG))
    {
            printf("\t%d - %s\n", i, pDirent->d_name);
            i++;
    }}

    closedir(pDir);

}
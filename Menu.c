#include "Menu.h"

void Menu(const char* path) {
    
    struct dirent *pDirent;
    DIR *pDir;

    // Ensure we can open directory.
    
    pDir = opendir(path);
    if (pDir == NULL) {
        printf("Cannot open directory '%s'\n", path);
        return;
    }

    // Process each entry.
    
    int i = 1;
    while ((pDirent = readdir(pDir)) != NULL) {
        if ((strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0 || (*pDirent->d_name) == '.')) 
        {
        } 

        else {
            printf("\t%d - %s\n", i, pDirent->d_name);
            i++;
        }
    }

    closedir(pDir);
}

int main(int argc, char* argv[]) {
    Menu(argv[1]);
    return 0;
}
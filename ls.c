#include <dirent.h>
#include <stdio.h>
#include <string.h>

void ls(const char *path, char *param) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir() error");
        return;
    }
    int count=0;
    if (strcmp(param,"-a")==0){
        while ((entry = readdir(dir)) != NULL) {
        printf("%s  ", entry->d_name);
        count+=1;
        if (count%5==0){
            printf("\n");
        }
    }
    


    printf("\n");
    }

        if (strcmp(param,"")==0){
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_name[0]!='.'){
            printf("%s  ", entry->d_name);
            count+=1;
            if (count%5==0){
                printf("\n");
            }
        }
    }
    
    printf("\n");
    }

    closedir(dir);
}


int main(int argc, char *argv[]) {
    if (argv[1]!=NULL){
        ls(".",argv[1]);
    } else {
        ls(".","");
    }
    return 0;
}

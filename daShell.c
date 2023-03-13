#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 1024

int main(){

    char input[MAX];
    char *args[MAX];   
    


    while (1){
        printf('snails:~$'); 
        int p=fork();
        if (p < 0) { 
            fprintf(stderr, "fork Failed" ); 
            return 1; 

        }
        else if (p > 0) {
              //execvp

        }



    }
}

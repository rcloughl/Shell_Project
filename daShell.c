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
        printf("snails:~$ ");
        fgets(input, MAX, stdin);
        input[strlen(input)-1]='\0';
        char *commands[MAX];
        char *morepipe;
        int cmds=0;
        morepipe=strtok(input,"|"); // This function allows me to break the input up 
        while (morepipe != 0 ){     // and seperate it on the '|', found here https://linux.die.net/man/3/strtok
            commands[cmds]=morepipe;
            morepipe=strtok(0,"|");
            cmds++;
        }     
        



        
        int p=fork();

        if (p < 0) { 
            fprintf(stderr, "fork Failed" ); 
            return 1; 
        }
        else if (p > 0) {
        //execvp();
        }




    }
}

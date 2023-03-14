#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 1024

int main(){

    char input[MAX];
    char *args[MAX];   
    int status;

    while (1){
        printf("snails:~$ ");
        fgets(input, MAX, stdin);
        input[strlen(input)-1]='\0';
        char *commands[MAX];
        char *morepipe;
        int cmds=0;
        morepipe=strtok(input,"|"); // This function allows me to break the input up 
        while (morepipe != 0 ){     // and seperate it on the '|', found here https://linux.die.net/man/3/strtok
            args[cmds]=morepipe;
            morepipe=strtok(0,"|");
            cmds++;
        }     
        args[cmds]=NULL;

        if (strcmp(args[0],"exit")==0){
            exit(0);
        }

        pid_t pid;
        int p[2];
        int pos=0;
        
        for (int i=0; i<cmds; i++){
            pipe(p);
            pid = fork();
            int temp=0;
            char *targs[MAX];
            char *onspace=strtok(args[0]," "); 
            while (onspace != 0 ){     
                targs[temp]=onspace;
                onspace=strtok(0," ");
                temp++;
            }     
            targs[temp]=NULL;
            if (pid < 0) { 
                printf("fork failed"); 
                return 1; 
            }
            else if (pid == 0) {
                dup2(pos,0);
                if (commands[i+1] != NULL) {
                    dup2(p[1], 1);
                }
                close(p[0]);   
                execvp(targs[0],targs);
                printf("couldn't find command %s\n",args[0]);
                return 1;
            }
            else {
                waitpid(pid,&status,0);
                close(p[1]);
                pos=p[0];
            }
        }
    }
    return 0;
}

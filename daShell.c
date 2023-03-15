#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 1024
#define MAXIN 24

int main(){

    char input[MAX];
    char *args[MAXIN][MAX];   
    int status;

    while (1){
        printf("snails:~$ ");
        fgets(input, MAX, stdin);
        input[strlen(input)-1]='\0';
        char *split;
        int tok=0;
        int cmdcounter=0;
        split=strtok(input," ");    // This function allows me to break the input up 
        while (split != NULL ){     // and seperate it on the ' ', found here https://linux.die.net/man/3/strtok
            if (strcmp(split,"|")==0){
                args[cmdcounter][tok]=NULL;
                cmdcounter+=1;
                tok=0;
                split=strtok(NULL, " ");
            }
            else {
                args[cmdcounter][tok]=split;
                split=strtok(NULL," ");
                tok++;
            }
        }     
        args[cmdcounter][tok]=NULL;
        args[cmdcounter+1][0]=NULL;


        if (strcmp(args[0][0],"exit")==0){
            exit(0);
        }

        /*
        int i=0;
        int j=0;
        while (args[i][0]!=NULL){
            printf("start \n");
            while (args[i][j]!=NULL){
                printf("%s\n",args[i][j]);
                j++;
            }
            printf("inc \n");
            i++;
            j=0;
        }
        printf("print\n");
        */

        pid_t pid;
        int p[2];
        int input=0;
        int cmdtrack=0;
        while (args[cmdtrack][0]!=NULL){
            int cmdptr=cmdtrack;
            cmdtrack+=1;
            pipe(p);
            pid=fork();
            if (pid<0){
                printf("failed fork");
                return 1;
            }
            else if (pid==0){
                dup2(input,0);
                if (args[cmdptr+1][0]!=NULL){
                    dup2(p[1],1);
                }
                close(p[0]);
                execvp(args[cmdptr][0],args[cmdptr]);
                printf("couldn't find command");
                return 1;
            }
            else{
                waitpid(pid,&status,0);
                close(p[1]);
                input=p[0];
            }
        }
     /*   
        for (int i=0; args[i]!=NULL; i++){
            pipe(p);
            pid = fork();
            if (pid < 0) { 
                printf("fork failed"); 
                return 1; 
            }
            else if (pid == 0) {
                dup2(input,0);
                if (args[i+1] != NULL) {
                    dup2(p[1], 1);
                }
                close(p[0]);   
                execvp(args[0],args);
                printf("couldn't find command %s\n",args[0]);
                return 1;
            }
            else {
                waitpid(pid,&status,0);
                close(p[1]);
                input=p[0];
            }
        }
        */
    }
    return 0;
}

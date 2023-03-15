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
	char pwd[MAX];
	getcwd(pwd,sizeof(pwd));
    //pwd
        printf("snails:~$ ");
        if (fgets(input, MAX, stdin)==NULL){
            printf("\nGoodbye\n");
            exit(0);
        }
	if (strcmp(input,"\n")==0){
		continue;
	}
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
            printf("\nGoodbye\n");
            exit(0);
        }
        pid_t pid;
        int p[2];
        int input=0;
        int cmdtrack=0;
        while (args[cmdtrack][0]!=NULL){
            int cmdptr=cmdtrack;
            cmdtrack+=1;
            if (strcmp(args[cmdptr][0],"cd")==0){
                chdir(args[cmdptr][1]);
                continue;
            }
/*
            int tempcount=0;
            split=strtok(args[cmdptr],"<");
            if (split!=NULL){
                
            }
*/
            pipe(p);
            pid=fork();
            if (pid<0){
                printf("failed fork\n");
                return 1;
            }
            else if (pid==0){
                dup2(input,0);
                if (args[cmdptr+1][0]!=NULL){
                    dup2(p[1],1);
                }
                close(p[0]);
                execvp(args[cmdptr][0],args[cmdptr]);
                printf("couldn't find command\n");
                return 1;
            }
            else{
                waitpid(pid,&status,0);
                close(p[1]);
                input=p[0];
            }
        }
    }
    return 0;
}

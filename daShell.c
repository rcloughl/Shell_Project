#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX 1024
#define MAXIN 24

int main(){

    char input[MAX];
    char *args[MAXIN][MAX];   
    int status;

    while (1){
    int bg[MAXIN];
    int arr[]={0,0,0,0,0,0};
	char pwd[MAX];
	getcwd(pwd,sizeof(pwd));
        printf("snails:~%s$ ", pwd);
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
            if (strcmp(split,"&")==0){
                bg[cmdcounter]=1;
                split=strtok(NULL," ");
            } else if (strcmp(split,"<")==0){
                split=strtok(NULL," ");
            } else if (0==strcmp(split,">")){
                arr[cmdcounter]=1;
                args[cmdcounter][tok]=split;
                split=strtok(NULL," ");
                tok+=1;
            } else {
                if (strcmp(split,"|")==0){
                    args[cmdcounter][tok]=NULL;
                    cmdcounter+=1;
                    tok=0;
                    arr[cmdcounter]=0;
                    split=strtok(NULL, " ");
                }
                else {
                    args[cmdcounter][tok]=split;
                    split=strtok(NULL," ");
                    tok++;
                }
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
            pipe(p);
            pid=fork();
            if (pid<0){
                printf("failed fork\n");
                return 1;
            }
            else if (pid==0){
                if (arr[cmdptr]==1){
                    int i=0; 
                    char *cmd[MAXIN];
                    char *fn[MAXIN];
                    
                    while (strcmp(args[cmdptr][i],">")!=0){
                        cmd[i]=args[cmdptr][i];
                        i+=1;
                    }
                    i+=1;
                    int j=0;
                    while (args[cmdptr][i]!=NULL){
                        fn[j]=args[cmdptr][i];
                        i+=1;
                        j+=1;
                    }
                    if (fork()==0){
                        close(1);
                        int of=open(fn[0],O_CREAT|O_WRONLY, 0644);
                        dup2(of,1);
                        execvp(cmd[0],cmd);
                        printf("couldn't find command\n");
                        return 1;
                    }
                    else{
                        waitpid(pid,&status,0);
                    }



                    return 1;
                }
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
                if (bg[cmdptr]==1){
                    close(p[1]);
                    input=p[0];
                }
                else {
                    waitpid(pid,&status,0);
                    close(p[1]);
                    input=p[0];
                    printf("\n");
                }
            }
        }
    }
    return 0;
}

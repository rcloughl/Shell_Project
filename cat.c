#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *f;
    int ch;
    if (argv[1]==NULL){
        printf("You must add a filename!\n");
        return 1;
    }  
    f=fopen(argv[1],"r");
    if(f!=NULL){
        while ((ch=fgetc(f))!=EOF){
            putchar(ch);
        }
        fclose(f);
        printf("\n");
        return 0;
    }
    else{
        printf("Error: %s not found\n",argv[1]);
        return 1;
    }

}
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
void main(){
    pid_t pid, Hijo_pid, pid2, Hijo2_pid;
    pid = fork();

    if (pid==-1){
        printf("No se ha podido crear el proceso hijo");
        exit(-1);

    }
    if (pid==0){
        pid2=fork();

        switch (pid2){
            case -1:
                printf("No se ha podido crear el proceso hijo");
                exit(-1);
                break;
            case 0:
                printf("\t\tSoy el proceso NIETO %d; Mi padre es = %d \n", getpid(), getppid());
                break;
            default:
                Hijo2_pid=wait(NULL);
                printf("\tSoy el proceso HIJO %d, Mi padre es: %d.\n", getpid(), getppid());
                printf("\tMi hijo: %d terminó.\n", Hijo2_pid);

        }
    }
        else {
            Hijo2_pid= wait(NULL);
            printf("Soy el proceso abuelo: %d, MI HIJO: %d terminó.\n", getpid(), pid);


        }
        exit(0);


    }

    





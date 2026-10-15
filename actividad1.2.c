#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
int main() {

    int fd[2]; //Extremos de la tubería
    pid_t pid; //identificador del proceso
    char mensajePadre[]="Buenos dias padre.";
    char buffer[20]; //Se guarda el mensaje recibido

    pipe(fd); //Creo pipe
    pid=fork(); //creo proceso

    switch(pid){

        case -1: //Error al crear el hijo
            printf("No se ha podido crear el hijo.");
            exit(-1);

        case 0: //EL hijo envia el mensaje al padre;
            close(fd[0]);
            write(fd[1], mensajePadre, strlen(mensajePadre));
            printf("\tEl HIJO envía algo al pipe.\n");
            break;
        
       default: //El padre recibe mensaje de hijo
            close(fd[1]);
            wait(NULL); //Espera a que hijo acabe
            read(fd[0], buffer, sizeof(buffer));
            printf("El PADRE recibe algo del pipe: %s\n", buffer);
            break;



    }
    return 0;


}
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main() {
    char cadena[]="Hola papi....";
    char quienSoy[15];
    int fd[2];
    char buffer[30];
    int salida;
    pid_t pid;
    pipe(fd);
    pid=fork();

    switch(pid){

        case -1:
            printf("NO SE HA PODIDO CREAR HIJO...");
            salida=-1;
            break;
        case 0:
            strcpy(quienSoy, "Soy el HIJO");
            printf("EL HIJO escribe en el pipe...\n");
            write(fd[1], cadena, strlen(cadena));
            salida=1;
            break;
            

        default: 
            strcpy(quienSoy, "Soy el PADRE");
            wait(NULL);
            printf("El PADRE lee del pipe...\n");
            read(fd[0], buffer,strlen(cadena));
            printf("\tMensaje leido: %s\n", buffer);
            salida=0;
            break;

    }
    printf("\nFIN DE PROGRAMA: º%s\n", quienSoy);
    return salida;
}

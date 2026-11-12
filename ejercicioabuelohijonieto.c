#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(void){
    //fd1: me comunico del abuelo hacia el hijo
    //fd2: me comunico del hijo hacia el abuelo.
    int fd1[2], fd2[2];
    pid_t pidhijo, pidnieto;

    char saludoAbuelo[]= "Saludos del Abuelo.";
    char saludoPadre[]="Saludos del Padre.";
    char saludoHijo[]= "Saludos del Hijo";
    char saludoNieto[]="Saludos del Nieto";

    //Almacenamos mensajes
    char buffer[80];

    //Comprobamos si las tuberias se crean correctamente
    if (pipe(fd1)==-1 || pipe(fd2)==-1){
        printf("Error al crear las tuberias");
        exit(-1);  
    }

    //El abuelo crea al hijo
    pidhijo = fork();

    if(pidhijo < 0){
        printf("Error al crear el hijo");
        exit(-1);

    }

    //Hijo esta creado
    if(pidhijo==0){
        //fd3: para que el hijo le hable al nieto, fd4: para que el nieto le responda al hijol resp
        int fd3[2], fd4[2];
        //Creamos tuberias para hablar con el nieto
        pipe(fd3);
        pipe(fd4);

        if (pipe(fd3)==-1 || pipe(fd4)==-1){
            printf("Error al crear las tuberias de nieto");
            exit(-1);
        }
        
        close(fd1[1]); //El hijo lee lo que manda el abuelo

        //Hijo crea el nieto
        pidnieto=fork();

        if (pidnieto==0){

            close(fd1[0]); //El nieto no lee del abuelo
            close(fd3[1]); //Nieto lee de fd3 (viene del hijo)
            close(fd4[0]); //Nieto escribe en fd4 (va hacia el hijo)

            //El nieto lee el mensaje recibido de su padre
            read(fd3[0], buffer, sizeof(buffer));
            printf("\t\tNIETO recibió de su padre: %s\n", buffer);
            //El nieto responde a su padre
            printf("Nieto envia respuesta a su padre...\n");
            write(fd4[1], saludoNieto, strlen(saludoNieto) + 1);

            //Cerramos los extremos que ha utilizado y finalizamos.
            close(fd3[0]);
            close(fd4[1]);
            exit(0);

        }
        else {
            close(fd3[0]); //El hijo escribe en fd3 hacia el nieto por fd3[1];
            close(fd4[1]); //El hijo lee de fd4 desde el nieto por fd4[0];

            //hijo lee el mensaje que le mando el abuelo por fd1[0];
            read(fd1[0], buffer, sizeof(buffer));
            printf("\tHijo recibió del abuelo: %s\n", buffer);
            //Lo ha leído, lo cierra.
            close(fd1[0]);

            //El hijo envia un mensaje de su nieto a traves de fd3
            printf("\tHijo enviando mensaje al nieto...\n");
            write(fd3[1], saludoPadre, strlen(saludoPadre) + 1);
            //Como lo ha enviado, lo cierra
            close(fd3[1]);

            //El hijo lee la respuesta que le mando el nieto por fd4
            read(fd4[0], buffer, sizeof(buffer));
            printf("Hijo recibió del nieto: %s\n", buffer);
            //Como ya lo ha leido, lo cierra.
            close(fd4[0]);

            //Hijo responde a abuelo usando fd2
            close(fd2[0]);
            printf("Hijo envia respuesta a abuelo\n");
            write(fd2[1], saludoHijo, strlen(saludoHijo) + 1);
            //Como ya lo ha escrito, lo cierra
            close(fd2[1]);

            //Hijo espera a que nieto finalice
            wait(NULL);
            exit(0);
        }

    
    } else {
        //Volvemos al proceso abuelo, ya que hijo no se creó
            //El abuelo solo escribe hacia el hijo
            close(fd1[0]);
            //El abuelo solo lee desde el hijo
            close(fd2[1]);

            //Abuelo envia mensaje por fd1 al hijo
            printf("Abuelo enviando mensaje al hijo...\n");
            write(fd1[1], saludoAbuelo, strlen(saludoAbuelo) + 1);
            //Como ya lo ha escrito, lo cierra.
            close(fd1[1]);
            //El abuelo espera a que acabe
            wait(NULL);
            
            //El abuelo lee el mensaje del hijo
            read(fd2[0], buffer, sizeof(buffer));
            printf("Abuelo lee la respuesta del hijo: %s\n", buffer);
            //Cuando ya lo ha leido, se cierra el canal.
            close(fd2[0]);

            exit(0);
    }
    return 0;
}
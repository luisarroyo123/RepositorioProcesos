#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void main(void){

    char saludo[]= "Un saludo!!!\n";
    char buffer[10];
    int fd, bytesleidos;

    fd=open("texto.txt", 1);

    if (fd==-1){
        printf("Error al abrir el fichero...\n");
        exit(-1);
    }
    printf("Escribo el saludo...\n");
    write(fd, saludo, strlen(saludo));
    close(fd);

    fd=open("texto.txt",0);
    printf("Contenido del Fichero: \n");

    bytesleidos=read(fd,buffer,1);
    while(bytesleidos!=0){
        printf("%1c", buffer[0]);
        bytesleidos=read(fd,buffer,1);
    }
    close(fd);


}
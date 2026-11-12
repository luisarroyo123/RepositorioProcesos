#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int salida=0;
    int fp;
    char mensaje="Este mensaje se escribio desde pipe escribe";
    const char *nombreArchivo="FIFO2";
    FILE *archivo=fopen(nombreArchivo,"r");

    if(archivo==NULL){
        printf("la pipe '%s' no existe, voy a crearla.\n", nombreArchivo);

        if(mkfifo("FIFO2", S_IFIFO | 0666) == -1){
            salida=-1;
        }
        else {
            printf("la pipe '%s' se ha creado correctamente.\n", nombreArchivo);
        }
    }
    else {
        printf("La pipe '%s' ya existe.\n", nombreArchivo);
        fclose(archivo);


    }
    if(salida==0){
        fp=open(nombreArchivo,1);

        if(fp==-1){
            printf("Error al arbir la pipe: '%s'.\n", nombreArchivo);
            salida=-1;
        }
        else {
            printf("Mando datos a la pipe...");
            write(fp, mensaje, strlen(mensaje));
            write(fp, mensaje, strlen(mensaje));
        }
    }
    return salida;

    



}
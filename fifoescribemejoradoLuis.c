#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){

    int fp;
    char mensaje[]="un saludo.\n";
    const char *nombreA="FIFO2";
    fp=open(nombreA,1);
    
    int salida=0;

    if (fp==-1){
        printf("Error al abrir la pipe");
        salida=-1;
    }
    else {
        
        printf("Mando datos a la pipe...\n");
        write(fp, (const void *)mensaje, strlen(mensaje));
        close(fp);
    }
    return salida;



}
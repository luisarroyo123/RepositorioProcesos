#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(void){
    int fp;
    int p, bytesleidos;
    char saludo[]="Un saludo!!!\n", buffer[10];
    int salida=0;


    p=mkfifo("FIFO2", S_IFIFO | 0666);

    if (p==-1){
        printf("Ha ocurrido un error...");
        salida=-1;
    }

    while(true){

        fp = open("FIFO2",0);
        bytesleidos=read(fp,buffer,1);

        while(bytesleidos!=0){
            printf("%1c", buffer[0]);
            bytesleidos=read(fp,buffer,1);
        }
        close(fp);

    }
    return salida;
}
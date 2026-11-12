#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){
    int fp;
    int p, bytesleidos, salida=0;
    char mensaje="Un saluddo...\n",
         buffer[10];
        
    
    p=mkfifo("FIFO2", S_IFIFO | 0666);

    if (p==-1){
        printf("Error al crear la pipe");
        salida=-1;
    }
    else {
        
        while(true){

            fp=open("FIFO2",0);
            bytesleidos=read(fp,buffer,1);
            printf("Vamos a sacar la info de FIFO2");

            while(bytesleidos!=0){

                printf("%1c", buffer[0]);
                bytesleidos=read(fp, buffer, 1);

            }
            close(fp);


        }
        return salida;
    }


}
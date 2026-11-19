#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void gestion_padre (int senal){
    printf("Padre recibe señal...%d\n", senal);
    
}

void gestion_hijo(int senal){
    printf("Hijo recibe señal...%d\n", senal);
 
}

int main(){
    int pid_padre, pid_hijo;
    int salida=0;
    pid_padre=getpid();
    pid_hijo=fork();
    

    if(pid_hijo==-1){
        printf("Error al crear el hijo.");
        fflush(stdout);
        salida=-1;
    }
    else if (pid_hijo==0){

                signal(SIGUSR1, gestion_hijo);

                while(true){
                sleep(1);
                if(kill(pid_padre, SIGUSR1)==-1){
                    salida=-1;
                    
                }
                pause();
                }
    }
    else {
                signal (SIGUSR1, gestion_padre);

                while(true){
                pause();
                sleep(1);
                if(kill(pid_hijo, SIGUSR1)==-1){
                    salida=-1;
                    
                }
                
                }
        
            }
            return salida;
    } 
    
        
    

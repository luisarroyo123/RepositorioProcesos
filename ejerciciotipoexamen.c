
/* Elaborar un programa en C con uso de procesos creados con fork()
que aplique el uso de barreras en la sincronizacion de procesos
utilizando pipes

Participante: Luis Arroyo
Fecha: 22/10/2026
 */ 

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>


//Funcion para que el hijo llame al factorial
double calculaFactorial(int n){
    double result=1;

    for (int i=1; i<=n; i++){
        result= result*i;
    }
    return result;
}

int main() {

    int fd[2]; //Extremos de la tubería
    pid_t pid; //identificador del proceso
    double x, N, n;

    //creo pipe
    pipe(fd); 

    //Solicita el valor de X
    printf("Introduce el valor de X:");
    scanf("%lf", &x);

    //Solicita el valor de N mientras que se cumpla la condición
    do {
        printf("Introduce el valor de N: 5 < N <=10:");
        scanf("%lf", &N);

    }
    while(N<=5 || N>10);

    //Creamos la pipe o tuberia
    if (pipe(fd)==-1){

        printf("Error al crear la tuberia");
        exit(-1);
    }

    //Creamos el proceso hijo
    pid=fork();


    switch(pid){

        case -1:
            printf("Error al crear el proceso hijo");
            exit(-1);
            break;
        
        case 0:
            close(fd[0]); //Cerramos la posibilidad de lectura del p. hijo

            for (n=0; n<=N; n++){
            double fact = calculaFactorial(n);
            //El hijo muestra el factorial calculado
            printf("Hijo %d calcula Factorial de (%f!) = %f\n", getpid(), n, fact);
            //Enviamos el factorial al p.padre
            fflush(stdout);
            write(fd[1], &fact, sizeof(fact));

        }
        close(fd[1]);
        exit(0);
        break;

        default:
            close(fd[1]); //Cerramos la escritura del p.padre

            double suma=0;

            for (n=0; n<=N; n++){

            double factorial_hijo;
            //El padre esta leyendo el factorial que le está mandando el hijo
            read(fd[0], &factorial_hijo, sizeof(factorial_hijo));

            //vamos a calcular x elevado a n
            double xElevadoN= pow(x,n);


            //Calculamos el cociente
            double cociente = xElevadoN/factorial_hijo;

            suma= suma+cociente;
            printf("Padre n = %f, Cociente=%.6f, Suma parcial=%.6f\n", n, cociente, suma);
        }
        close (fd[0]);
        wait(NULL); //Esperamos a que el hijo termine
        printf("El resultado de E elevando a %f es: %.6f", x, suma);
        break;
    }

    return 0;
}
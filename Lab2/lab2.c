// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <math.h>
// user-defined header files

#include "mypcm.h"


// function prototypes
void run(asignal * inputsignal);


int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);

    //call any other function here

    free(inputsignal);
    return 0;
}

void run(asignal * inputsignal){

    int input[6] ;
    for (int i = 0 ; i < 6 ; i++){
        scanf("%d",&input[i]);
    }

    asignal signal = *inputsignal;
    signal.A = input[0];
    signal.omega = input[1];
    signal.sigma = input[2];
    signal.duration = input[3];
    int interval = input[4];
    int encoderbits = input[5];
    int levels = pow(2,encoderbits);
    int a = (input[3] / input[4]) + 1;

    float* samples = (float*) malloc(sizeof(float) * a);
    int* pcmpulses = (int*) malloc (sizeof(int) * (a +1));
    int* dsignal = (int*) malloc(sizeof(int) * (a));
    for (int k = 0 ; k < a ; k++){
        pcmpulses[k] = 0;
    }
    pcmpulses[a] = -1;
    sampler (samples , interval , signal);
    quantizer(samples ,pcmpulses ,levels , signal.A );
    encoder(pcmpulses , dsignal ,encoderbits );
    int numDigits;

    for (int o = 0 ; o < a ; o ++){
        numDigits = floor(log10(abs(dsignal[o]))) + 1;
        if (dsignal[o] == 0 ){numDigits = 1;}
        if (numDigits < encoderbits){
            printf("%0*d" , (encoderbits) ,dsignal[o] ); 
        }
        else{
            printf("%i",dsignal[o]);
        }

    }
    printf("\n");

}



// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
//Add any necessary headers here
#include <math.h>

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
float analog_signal_generator(asignal signal, int t)
{
    return ( signal.A *sin(signal.omega*t + signal.sigma));
}

void sampler(float *samples, int interval, asignal signal)
{
    float t = 0;
    int i = 0;
    while(t <= signal.duration)
    {
        samples[i++] = analog_signal_generator(signal, t);
        t += interval;
    }

}

int dectobin(int decimal ) {
    int binary = 0;
    int base = 1;

    while (decimal > 0) {
        binary += (decimal % 2) * base;
        decimal = decimal / 2;
        base *= 10;
    }
    return binary;
}

void quantizer(float *samples, int *pcmpulses, int levels , float A )
{
    int i = 0;
    while (pcmpulses[i] != -1){
        pcmpulses[i++] =  ( ((samples[i] + A) / (2*A)) * levels);
    }

}


void encoder(int *pcmpulses, int *dsignal, int encoderbits )
{
    int i = 0;
    while (pcmpulses[i] != -1){
        dsignal[i] = dectobin(pcmpulses[i]);
        i++;
    }
}

#include "intrinsics.h"
#include "msp430fr2355.h"
#include <msp430.h>
#include <stdbool.h>
#include "math.h"

char celcius;
int thousands;
int hundreds;
int tens;
int ones;

void init_difficulty(void){
    P1SEL1 |= BIT0;
    P1SEL0 |= BIT0;

    PM5CTL0 &= ~LOCKLPM5;

    ADCCTL0 &= ~ADCSHT;
    ADCCTL0 |= ADCSHT_2;
    ADCCTL0 |= ADCON;

    ADCCTL1 |= ADCSSEL_2;
    ADCCTL1 |= ADCSHP;

    ADCCTL2 &= ~ADCRES;
    ADCCTL2 |= ADCRES_2;

    ADCMCTL0 |= ADCINCH_5;

    ADCIE |= ADCIE0;
}

long int get_diff(int ADC_Value){
    double volts = ((double)ADC_Value / 4096) * 3.3;

    double time = volts * 5555;

    return (long int)time;
}
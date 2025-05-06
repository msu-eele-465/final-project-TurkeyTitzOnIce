#include "intrinsics.h"
#include "msp430fr2355.h"
#include <msp430.h>
#include <stdbool.h>
#include "math.h"

void init_difficulty(void){
    PM5CTL0 &= ~LOCKLPM5;           // Unlock GPIO

    // Set P1.1 to analog mode (A0)
    P1SEL0 |= BIT2;
    P1SEL1 |= BIT2;

    // ADC config
    ADCCTL0 = ADCSHT_2 | ADCON;     // 16-cycle sample, ADC on
    ADCCTL1 = ADCSSEL_2 | ADCSHP;   // SMCLK, pulse sample mode
    ADCCTL2 = ADCRES_2;             // 12-bit resolution
    ADCMCTL0 = ADCINCH_2;           // A0 = P1.1 input

    ADCIE |= ADCIE0;                // Enable interrupt (optional)
}


long get_diff(int ADC_Value) {
    int bucket = (ADC_Value * 7) / 4096;

    switch (bucket) {
        case 0: return 2500;
        case 1: return 5000;
        case 2: return 7500;
        case 3: return 10000;
        case 4: return 12500;
        case 5: return 15000;
        case 6: return 20000;
        default: return 10000;  // safety fallback
    }
}


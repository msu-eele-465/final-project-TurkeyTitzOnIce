#include "intrinsics.h"
#include <msp430.h>
#include <stdbool.h>

timer_init(){
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mdoe to activate
    
    TB1CTL |= TBSSEL__ACLK | ID__1 | MC__UP | TBCLR;

    TB1CCR0 = 32769;    // CCR0=32769

    // Setup Timer Compare IRQ
    TB1CCTL1 &= ~CCIFG;   // Clear CCR1 Flag
    TB1CCTL1 |= CCIE;     // Enable TB0 CCR1 Overflow IRQ

    __enable_interrupt();
}
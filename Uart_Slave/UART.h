#include "msp430fr2355.h"
void uart_init(void){
    UCA1CTLW0 |= UCSWRST;

    UCA1CTLW0 |= UCSSEL__ACLK;

    UCA1BRW = 3;
    UCA1MCTLW |= 0x9200;

    P4SEL1 &= ~BIT3;
    P4SEL0 |= BIT3;

    P4SEL1 &= ~BIT2;
    P4SEL0 |= BIT2;

    UCA1CTLW0 &= ~UCSWRST;

    UCA1IFG &= ~UCTXIFG;

    UCA1IE |= UCRXIE;       //turn on recieve interrupt, only turn on transmit interrupt when we are ready to transmit

    _enable_interrupt();
}
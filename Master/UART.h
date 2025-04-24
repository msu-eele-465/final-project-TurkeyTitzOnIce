#include "msp430fr2355.h"
void uart_init(void){
    UCA1CTLW0 |= UCSWRST;

    UCA1CTLW0 |= UCSSEL__ACLK;

    UCA1BRW = 3;
    UCA1MCTLW |= 0x9200;

    P4SEL1 &= ~BIT3;
    P4SEL0 |= BIT3;

    UCA1CTLW0 &= ~UCSWRST;
}
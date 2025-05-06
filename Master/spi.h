#include "msp430fr2355.h"
#include <msp430.h>

void init_spi(void){
    UCA0CTLW0 |= UCSWRST;

    UCA0CTLW0 |= UCSSEL__SMCLK;
    UCA0BRW = 10;

    UCA0CTLW0 |= UCSYNC;
    UCA0CTLW0 |= UCMST;

    P1SEL1 &= ~BIT5;
    P1SEL0 |= BIT5;

    P1SEL1 &= ~BIT7;
    P1SEL0 |= BIT7;

    P1SEL1 &= ~BIT6;
    P1SEL0 |= BIT6;

    UCA0CTLW0 &= ~UCSWRST;

    PM5CTL0 &= ~LOCKLPM5;

}
#include <msp430.h>
#include "heartbeat.h"
#include "msp430fr2310.h"
#include "intrinsics.h"
#include <stdbool.h>
#include <stdint.h>



//Globals

uint8_t val = 0b00000000;



int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    //LED Bar inits

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    P1DIR |= BIT3;
    P1OUT &= ~BIT3;

    P1DIR |= BIT4;
    P1OUT &= ~BIT4;

    P1DIR |= BIT5;
    P1OUT &= ~BIT5;

    P1DIR |= BIT6;
    P1OUT &= ~BIT6;

    P1DIR |= BIT7;
    P1OUT &= ~BIT7;

    P2DIR |= BIT6;
    P2OUT &= ~BIT6;

    P2DIR |= BIT7;
    P2OUT &= ~BIT7;

    HeartBeat_init();

    PM5CTL0 &= ~LOCKLPM5;
    __enable_interrupt();

    // --- SPI Slave Setup ---
    UCB0CTLW0 |= UCSWRST;                  // Hold in reset

    UCB0CTLW0 = UCSYNC | UCMSB | UCMODE_0;
    UCB0BRW = 10;                          // Doesn't really matter in slave

    // Configure SPI Pins
    P1SEL0 |= BIT1 | BIT2;
    P1SEL1 &= ~(BIT1 | BIT2);

    UCB0IE |= UCRXIE;                      // Enable RX interrupt

    UCB0CTLW0 &= ~UCSWRST;                 // Release from reset
    // -------------------------------------

    while(1) {
        if(val & ( 1 << 7)){
            P1OUT |= BIT0;
        }else{
            P1OUT &= ~BIT0;
        }

        if(val & ( 1 << 6)){
            P1OUT |= BIT3;
        }else{
            P1OUT &= ~BIT3;
        }

        if(val & ( 1 << 5)){
            P1OUT |= BIT4;
        }else{
            P1OUT &= ~BIT4;
        }

        if(val & ( 1 << 4)){
            P1OUT |= BIT5;
        }else{
            P1OUT &= ~BIT5;
        }

        if(val & ( 1 << 3)){
            P1OUT |= BIT6;
        }else{
            P1OUT &= ~BIT6;
        }

        if(val & ( 1 << 2)){
            P1OUT |= BIT7;
        }else{
            P1OUT &= ~BIT7;
        }

        if(val & ( 1 << 1)){
            P2OUT |= BIT6;
        }else{
            P2OUT &= ~BIT6;
        }

        if(val & ( 1 << 0)){
            P2OUT |= BIT7;
        }else{
            P2OUT &= ~BIT7;
        }

    }
}


//---------------ISRs----------------------

//Heartbeat ISR
#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    P2OUT ^= BIT0;
}

//SPI Rx ISR
#pragma vector = EUSCI_B0_VECTOR
__interrupt void ISR_B0_RX(void){
    val = UCB0RXBUF;
    UCB0IFG &= ~UCRXIFG;
}
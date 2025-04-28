#include <driverlib.h>
#include "hex.h"
#include "intrinsics.h"
#include "UART.h"
#include "heartbeat.h"

//UART variables
    volatile char message[] = "0";
    int position;
    int i, j;
    unsigned int messageSize = 1;

int main(void) {
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    HeartBeat_init();
    hex_init();
    uart_init();

    message[0] = '0';

    while(1)
    {
    }
}


//------------Functions-------------
void tx(void){
    position = 0;
    UCA1IE |= UCTXCPTIE;
    UCA1IFG &= ~UCTXCPTIFG;
    UCA1TXBUF = message[position];
}



//--------------ISRS----------------


//heartbeat
#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    P6OUT ^= BIT6;

    static int toggle;
    if(toggle){
        message[0] = '1';
        toggle = 0;
    }else{
        message[0] = '0';
        toggle = 1;
    }

    tx();
}



//UART
#pragma vector = EUSCI_A1_VECTOR
__interrupt void ISR_EUSCI_A1(void){
    if(UCA1IFG & UCTXIFG){
        position++;

        if(position < messageSize){
            UCA1TXBUF = message[position];
        }else{
            UCA1IE &= ~UCTXCPTIE;  // All done sending, disable interrupt
        }

        UCA1IFG &= ~UCTXCPTIFG;  // Clear TX complete flag
    }

    if(UCA1IFG & UCRXIFG){
        // Handle receive if needed
    }
}

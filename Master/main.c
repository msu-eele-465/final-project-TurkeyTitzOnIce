#include <driverlib.h>
#include "hex.h"
#include "intrinsics.h"
#include "UART.h"
#include "heartbeat.h"
#include "locale.h"

//UART variables
    volatile char message[] = "1234";
    int position;
    int i, j;
    unsigned int messageSize = 4;

int main(void) {
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    HeartBeat_init();
    hex_init();
    uart_init();

    while(1)
    {
    }
}


//------------Functions-------------
void tx(void){
    position = 0;
    UCA1IE |= UCTXIE;
    UCA1IFG &= ~UCTXIFG;
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
        message[1] = '2';
        message[2] = '3';
        message[3] = '4';
        toggle = 0;
    }else{
        message[0] = '5';
        message[1] = '6';
        message[2] = '7';
        message[3] = '8';
        toggle = 1;
    }

    tx();
}



//UART
#pragma vector = EUSCI_A1_VECTOR
__interrupt void ISR_EUSCI_A1(void){
    if(UCA1IFG & UCTXIFG){
        position++;
        if(position <= messageSize - 1){
            UCA1TXBUF = message[position];
        }else{
            UCA1IE &= ~UCTXIE;  // All done sending, disable interrupt
            UCA1IFG &= ~UCTXIFG;
        }

        UCA1IFG &= ~UCTXCPTIFG;  // Clear TX complete flag
    }

    if(UCA1IFG & UCRXIFG){
        // Handle receive if needed
    }
}

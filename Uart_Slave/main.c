#include <driverlib.h>
#include "hex.h"
#include "intrinsics.h"
#include "UART.h"

//UART variables
    char message [] = "Hello World ";
    int position;
    int i, j;

int main(void) {
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    hex_init();
    uart_init();

    while(1)
    {
        for(position = 0; position < sizeof(message); position++){
            UCA1TXBUF = message[position];
            _delay_cycles(1000);
        }
        _delay_cycles(100000);
    }
}


#pragma vector = //instert interrupt flag here
__interrupt void ISR_name(void){
    position = 0;
    UCA1IE |= UCTXCPTIE;
    UCA1IFG &= ~UCTXCPTIFG;
    UCA1TXBUF = message[position];

    //clear flag

}

#pragma vector = EUSCI_A1_VECTOR
__interrupt void ISR_EUSCI_A1(void){
    if(UCA1IFG & UCTXIFG){
        if(position == sizeof(message)){
            UCA1IE &= ~UCTXCPTIE;
        }else {
            position++;
            UCA1TXBUF = message[position];
        }

        UCA1IFG &= ~UCTXCPTIFG;
    }

    if(UCA1IFG & UCRXIFG){
        //value = UCA1RXBUF

        //Recieve clears on its own
    }
}

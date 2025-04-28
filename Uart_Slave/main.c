#include <driverlib.h>
#include "hex.h"
#include "UART.h"
#include "heartbeat.h"

//UART variables
    char message [] = "0";
    int position;
    int i, j;
    char recieved[] = " ";

int main(void) {
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    hex_init();
    uart_init();
    HeartBeat_init();

    while(1)
    {
        if(recieved == "0"){
            P6OUT |= BIT6;
        }else if(recieved == "1"){
            P6OUT &= ~BIT6;
        }else{
        }
    }
}

//----------Functions-------------
void tx(void){
    position = 0;
    UCA1IE |= UCTXCPTIE;
    UCA1IFG &= ~UCTXCPTIFG;
    UCA1TXBUF = message[position];
}



//-----------ISRs-----------------


//Heartbeat
#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    //P6OUT ^= BIT6;
}



//UART
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
        recieved[0] = UCA1RXBUF;

        //Recieve clears on its own
    }
}

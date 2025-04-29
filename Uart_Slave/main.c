#include <driverlib.h>
#include "hex.h"
#include "UART.h"
#include "heartbeat.h"

//UART variables
    char message [] = "0";
    int position;
    int i, j;
    char recieved[] = "    ";

int main(void) {
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    hex_init();
    uart_init();
    HeartBeat_init();

    while(1)
    {
        P3OUT = recieved[0];
        P5OUT = recieved[1] << 1;
        P6OUT = recieved[2];
        P2OUT = recieved[3];
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
    P6OUT ^= BIT6;
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
        static int count; 
        recieved[count] = UCA1RXBUF;
        count++;
        if(count == 4){
            count = 0;
        }
        UCA1IFG &= ~UCRXIFG;
        //Recieve clears on its own
    }
}

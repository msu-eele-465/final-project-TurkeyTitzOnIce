#include <driverlib.h>
#include "hex.h"
#include "intrinsics.h"
#include "UART.h"
#include "heartbeat.h"
#include "locale.h"
#include "Keypad.h"

//UART variables
    volatile char message[] = "1234";
    int position;
    int i, j;
    unsigned int messageSize = 4;
    char recieved[] = "    ";

    //Keypad Variables
    unsigned int typed;

//------------Functions-------------
void tx(void){
    position = 0;
    UCA1IE |= UCTXIE;
    UCA1IFG &= ~UCTXIFG;
    UCA1TXBUF = message[position];
}

int main(void) {
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    HeartBeat_init();
    hex_init();
    uart_init();

    while(1)
    {
        P1OUT = recieved[0] << 4;
        __delay_cycles(10);
        P5OUT = recieved[1] << 1;
        __delay_cycles(10);
        P6OUT = recieved[2] | (P6OUT & 0b01000000);
        __delay_cycles(10);
        P2OUT = recieved[3];
        __delay_cycles(10);
    

    typed = _read_keypad_char();
        if(typed != 'E'){
            static unsigned int count;
            message[count] = typed;
            count++;
            while(_read_keypad_char() == typed){}  //Wait for the button to be released
            if(count ==4){
                count = 0;
                tx();
            }
        }
    }
}



//--------------ISRS----------------


//heartbeat
#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    P6OUT ^= BIT6;
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

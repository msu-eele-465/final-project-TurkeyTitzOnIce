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

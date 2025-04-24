#include <driverlib.h>
#include "hex.h"



int main(void) {
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    hex_init();

    P3OUT = 2;

    P5OUT = 4 << 1;

    while(1)
    {
        
    }

    return 0;
}

#include <driverlib.h>
#include "hex.h"


int main(void) {
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    hex_init();

    while(1)
    {
        
    }
}

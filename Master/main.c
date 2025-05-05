#include <driverlib.h>
#include <msp430.h>
#include <stdbool.h>
#include "hex.h"
#include "intrinsics.h"
#include "UART.h"
#include "heartbeat.h"
#include "locale.h"
#include "Keypad.h"
#include <string.h>  
#include "timer.h"


//UART variables
    char message[] = "????";
    int position;
    int i, j;
    unsigned int messageSize = 4;
    char recieved[] = "    ";

//Keypad Variables
    unsigned int typed;
    
//ADC Vars
    unsigned int ADC_Value;
    long int time_var;
    
//Logic Variables and init

    int turn = 1;
    unsigned int myScore = 0;
    unsigned int theirScore = 0;
    unsigned int guess;
    char fullGuess[] = "    ";
    bool displayed = false;
    bool slaveDisplayed = false;
    char theirInput[] = "    ";
    char myInput[] = "    ";


//------------Functions-------------
void tx(void){
    position = 0;
    UCA1IE |= UCTXIE;
    UCA1IFG &= ~UCTXIFG;
    UCA1TXBUF = message[position];
}

int check_guess(char ans[], char guess[]){
    if(strcmp(ans, guess) == 0){
        return 1;
    }else{
        return 0;
    }
}

void clear_display(void){
    P1OUT = 15 << 4;
    P5OUT = 15 << 1;
    P6OUT = 15 | (P6OUT & 0b01000000);
    P2OUT = 15;
}

void slave_display(void){
    slaveDisplayed = true;
}

void get_input_master(void){
    strcpy(message,"    ");
    while(message[3] == ' '){
        typed = _read_keypad_char();
        if(typed != 'E' & typed != '#'){
            static unsigned int count;
            message[count] = typed;
            count++;
            while(_read_keypad_char() == typed){}  //Wait for the button to be released
            if(count ==4){
                count = 0;
            }
        }
    }
}

void get_input_slave(void){
    strcpy(recieved,"    ");
    while(recieved[3] == ' '){}
    strcpy(theirInput,recieved);
}

void delay_time(void){
    if(time_var <= 2500){
        __delay_cycles(2500);
    }else if(time_var > 2500 & time_var <= 5000){
        __delay_cycles(5000);
    }else if(time_var > 5000 & time_var <= 7500){
        __delay_cycles(7500);
    }else if(time_var > 7500 & time_var <= 10000){
        __delay_cycles(10000);
    }else if(time_var > 10000 & time_var <= 12500){
        __delay_cycles(12500);
    }else if(time_var > 12500 & time_var <= 17500){
        __delay_cycles(15000);
    }else if(time_var > 17500){
        __delay_cycles(20000);
    }else{
        __delay_cycles(10000);
    }
}

void display_code(void){
    P1OUT = recieved[0] << 4;
    P5OUT = recieved[1] << 1;
    P6OUT = recieved[2] | (P6OUT & 0b01000000);
    P2OUT = recieved[3];
    delay_time();
    clear_display();
}

int main(void) {
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    HeartBeat_init();
    hex_init();
    uart_init();
    init_difficulty();

    ADCCTL0 |= ADCENC | ADCSC;

    P4DIR |= BIT7;              //init indicator LED Master
    P4OUT &= ~BIT7;

    P4DIR |= BIT6;              //init indicator LED Slave
    P4OUT &= ~BIT6; 

    clear_display();
    tx();
    while(_read_keypad_char() != '#'){}         //Wait for Pound so signify start of game
    time_var = get_diff(ADC_Value);
    ADCIE &= ~ADCIE0;                           //Disable ADC IFG

    while(1)
    {
    
        if(turn == 1){
            P4OUT |= BIT7;                          //Turn On LED to signify turn
            get_input_master();
            strcpy(myInput, message);
            tx();
            delay_time();
            strcpy(message, "????");
            tx();
            P4OUT &= ~BIT7;
            turn = 2;
        }else if(turn == 2){
            P4OUT |= BIT6;
            get_input_slave();
            if(check_guess(myInput, theirInput)){
                theirScore++;
                strcpy(message, ";;;;");
                tx();
                __delay_cycles(3000000);
                strcpy(message, "????");
                tx();
            }else{
                strcpy(message, "....");
                tx();
                __delay_cycles(3000000);
                strcpy(message, "????");
                tx();
            }
            P4OUT &= ~BIT6;
            turn = 3;
        }else if(turn == 3){
            P4OUT |= BIT6;
            get_input_slave();
            display_code();
            turn = 4;
            P4OUT &= ~BIT6;
        }else if(turn == 4){
            P4OUT |= BIT7;
            get_input_master();
            if(check_guess(theirInput, message)){
                myScore++;
                P1OUT = 11 << 4;
                P5OUT = 11 << 1;
                P6OUT = 11 | (P6OUT & 0b01000000);
                P2OUT = 11;
                __delay_cycles(3000000);
                clear_display();
            }else{
                P1OUT = 14 << 4;
                P5OUT = 14 << 1;
                P6OUT = 14 | (P6OUT & 0b01000000);
                P2OUT = 14;
                __delay_cycles(3000000);
                clear_display();
            }
            turn = 1;
            P4OUT &= ~BIT7;
        }else{}
    }
}



//--------------ISRS----------------


//heartbeat
#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void){
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


//ADC ISR
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
    ADC_Value = ADCMEM0;
    ADCCTL0 &= ~ADCENC;
}
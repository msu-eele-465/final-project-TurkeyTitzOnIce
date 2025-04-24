void hex_init(void){


    //HEX Display 1
    P3DIR |= BIT0;
    P3OUT |= BIT0;

    P3DIR |= BIT1;
    P3OUT &= ~BIT1;

    P3DIR |= BIT2;
    P3OUT |= BIT2;

    P3DIR |= BIT3;
    P3OUT &= ~BIT3;

    //HEX Display 2
    P5DIR |= BIT1;
    P5OUT |= BIT1;

    P5DIR |= BIT2;
    P5OUT &= ~BIT2;

    P5DIR |= BIT3;
    P5OUT |= BIT3;

    P5DIR |= BIT4;
    P5OUT &= ~BIT4;

    //HEX Display 3
    P6DIR |= BIT0;
    P6OUT |= BIT0;

    P6DIR |= BIT1;
    P6OUT &= ~BIT1;

    P6DIR |= BIT2;
    P6OUT |= BIT2;

    P6DIR |= BIT3;
    P6OUT &= ~BIT3;

   //HEX Display 2
    P2DIR |= BIT0;
    P2OUT |= BIT0;

    P2DIR |= BIT1;
    P2OUT &= ~BIT1;

    P2DIR |= BIT2;
    P2OUT |= BIT2;

    P2DIR |= BIT3;
    P2OUT &= ~BIT3;

    PM5CTL0 &= ~LOCKLPM5;
}
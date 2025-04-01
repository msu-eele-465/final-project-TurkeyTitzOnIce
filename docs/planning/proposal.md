# Final project proposal

- [Aids] I have reviewed the project guidelines.
- [Aids] I will be working alone on this project.
- [Aids] No significant portion of this project will be (or has been) used in other course work.

## Embedded System Description

**Total System**
This Embeded system will integrate two MSP430FR355 microcontrollers with each other communicating inputs each has to the other with UART. The Master will also communicate with a MSP430FR311 through SPI to update an LED bar. The purpose of the system is to play a matching game between two keypad inputs and keep track of the score on the LED bar.


**MSP430FR355 #1**

Output 1. UART connection to MSP430FR355 #2 to transmit data. This will transmit a collection of different pieces of data depending on the state of the game.

Input 1. UART connection to MSP430FR355 #2 to recieve data. This will recieve a collection of different pieces of data depending on the state of the game.

Output 2. SPI connection to MSP430FR311 to transmit data. This will be transmitting the score of the game to be displayed on the LED Bar.

Input2. SPI connection to MSP430FR311 to recieve acknowledges to ensure the communication is working correctly.

Output 3. HEX Display Circuit. This circuit will consist of a 4bit-7segment display decoder and will be driven by the MSP.

Input 3. Keypad. The Keypad will be used to gather data from a human input which is what powers the game.

Output 4. RGB LED. The RGB LED will be used to display the status of the game and the system.


**MSP430FR350 #2**

Output 1. UART connection to MSP430FR355 #1 to transmit data. This will transmit a collection of different pieces of data depending on the state of the game.

Input 1. UART connection to MSP430FR355 #1 to recieve data. This will recieve a collection of different pieces of data depending on the state of the game.

Output 2. HEX Display Circuit. This circuit will consist of a 4bit-7segment display decoder and will be driven by the MSP.

Input 2. Keypad. The Keypad will be used to gather data from a human input which is what powers the game.

Output 3. RGB LED. The RGB LED will be used to display the status of the game and the system.


**MSP430FR311**

Output 1. SPI connection to MSP430FR355 #1 to transmit data. This will transmit acknowledges to ensure proper communication with the MSP.

Input 1. SPI connection to MSP430FR355 #1 to recieve data. This will recieve a byte of data related to the "score" of the game to be displayed.

Output 2. LED Bar. This will be to display the score of the game for the users to see while playing.


## Hardware Setup

The UART and SPI connections are bi-directional and every other connection is uni-directional. The Hex Display Circuit is composed of both a HEX display and a 4bit-7segment decoder. 

![Picture](Proposal.drawio.png)


## Software overview

This is a very high level flowshart that does not include all of the necessary functions and interrupts due to them not being developed yet, rather it shows the general flow of what the code in the three microcontrollers will be doing throughout the runtime of the system. 

![Picture](flow.drawio.png)


## Testing Procedure

The testing procedure will be as follows:

**Step 1**

Develope the code for the MSP430FR355 #1 to establish that the keypad provides the desired input, the RGB LED works as intended, and that the board is able to interface with and AD2 in UART.

**Step 2**

Adjust the previous code for the MSP430FR355 #2 to develope the UART connection between the two and ensure the functionality of the two boards and their communication.

**Step 3**

Develope the code for the MSP430FR311 and the MSP430FR355 #1 to establish a SPI connection and establish the LED Bar for displaying the Score of the game.


## Prescaler

Desired Prescaler level: 

- [x] 100%
- [ ] 95% 
- [ ] 90% 
- [ ] 85% 
- [ ] 80% 
- [ ] 75% 

### Prescalar requirements 

**Outline how you meet the requirements for your desired prescalar level**

**The inputs to the system will be:**
1.  Keypads
2.  UART Inputs
3.  SPI Inputs
4.  Difficulty Knob

**The outputs of the system will be:**
1.  RGB LED
2.  LED Bar
3.  UART Outputs
4.  SPI Outputs
5.  HEX Display Circuits 

**The project objective is**

To create a game that two people can play with one another. One player will input a code that will be displayed on the others hex displays for an amount of time determined by the difficutly knob. The other player will then try to type in what the code was and if they get it correct they will get a point. The points will be displayed on the LED Bar and the game will end when one player gets 3 points.

**The new hardware or software modules are:**
1. LED Hex Display - utilizing a 4bit - 7 segment display decoder.
2. SPI communication - Using SPI even though its something we have never learned.


The Master will be responsible for:

Controlling the entire game - transmitting keypad 1 inputs and keeping track of score and sending that to the scoreboard slave.

The Slave(s) will be responsible for:

Keypad 2 slave - Being the controller for the second player of the game

Scoreboard slave - showing off the score on the LED Bar.



### Argument for Desired Prescaler

Verbal.

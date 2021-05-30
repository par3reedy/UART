//Patrick Reedy; May 14, 2021

#ifndef UART_H_
#define UART_H_

#define TX              BIT3        //Pin 3 corresponds to transmit for UART
#define RX              BIT2        //Pin 2 corresponds to receive for UART
#define UART            P1          //Port 1 is used for all UART

//ESC Commands
#define ESC             0x1B        //ESC command prefix
#define BLINK           "[5m"       //Blink for next command
#define DOWN3           "[3B"       //Move cursor down 3 rowss
#define DOWN1           "[1B"       //Move cursor down 1 row
#define RIGHT5          "[5C"       //Move cursor right 6 cols
#define LEFT15          "[15D"      //Move cursor left 15 cols
#define RESCUR          "[H"        //Reset the cursor to top left of terminal window
#define ATTOFF          "[0m"       //Turn off all attributes
#define RED             "[31m"      //Turn the text color to RED
#define GREEN           "[32m"      //Turn the text color to GREEN
#define WHITE           "[37m"      //Turn the text color to WHITE
#define BLUE            "[34m"      //Turn the text color to BLUE

#endif /* UART_H_ */

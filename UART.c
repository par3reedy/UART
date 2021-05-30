//Patrick Reedy; May 14, 2021

/*--------------------------------------------------------------------------------------------------------------------------------------
*  Library Definitions
--------------------------------------------------------------------------------------------------------------------------------------*/
#include "msp.h"
#include "UART.h"

/*--------------------------------------------------------------------------------------------------------------------------------------
*  Function Definitions
--------------------------------------------------------------------------------------------------------------------------------------*/

//Function to intialize the UART functionality of the EUSCIA0 communication protocol.
void UART_init(void){
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;             //Enable software reset

    EUSCI_A0->CTLW0 = (EUSCI_A_CTLW0_SWRST              //Enable software reset
                     | EUSCI_A_CTLW0_SSEL__SMCLK);      //Set UART to SMCLK default 3MHz

    EUSCI_A0->BRW = 1;                                  //Set BRW to 1 to fix clock erroring
    EUSCI_A0->MCTLW = (EUSCI_A_MCTLW_OS16);             //Oversample enabled
    EUSCI_A0->MCTLW |= (10 << EUSCI_A_MCTLW_BRF_OFS);   //BRF = 10 to fix clock erroring
    EUSCI_A0->MCTLW |= (0 << EUSCI_A_MCTLW_BRS_OFS);    //BRS = 0 to fix clock erroring

    UART->SEL0 |= (TX | RX);                            //Set UART port transmit and receive SEL0 to 1 for UART usage
    UART->SEL1 &= ~(TX | RX);                           //Set UART port transmit and receive SEL1 to 0 for UART usage

    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;            //Clear software reset
}

//Function to print a single character through the UART to the Terminal screen
void UART_print(char cha){
    while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));        //Wait until the transmit buffer is empty
    EUSCI_A0->TXBUF = cha;                              //Character is sent to the buffer
}

//Function to print a string of characters through the UART to the Terminal screen
void UART_print_string(char string[]){
    uint32_t i = 0;                                     //Initialize counting variable to traverse the string
    for(i=0;string[i]!='\0';i++){                       //Run through the string until the string terminates
        UART_print(string[i]);                          //Print the character associated with the position in the string
    }
}

//Function to send an ESC code through the UART to the Terminal
void UART_esc_code(char string[]){
    UART_print(ESC);                                    //Print the ESC character code
    UART_print_string(string);                          //Print the string associated with
}

//Patrick Reedy; May 14, 2021

/*--------------------------------------------------------------------------------------------------------------------------------------
*  Library Definitions
--------------------------------------------------------------------------------------------------------------------------------------*/
#include "msp.h"
#include "DCO.h"
#include "UART.h"

/*--------------------------------------------------------------------------------------------------------------------------------------
*  Function Definitions
--------------------------------------------------------------------------------------------------------------------------------------*/
void UART_init(void);
void UART_print(uint8_t cha);
void set_DCO(uint32_t freq);
void UART_print_string(char string[]);
void UART_esc_code(char string[]);

/*--------------------------------------------------------------------------------------------------------------------------------------
*  Global Variables
--------------------------------------------------------------------------------------------------------------------------------------*/
volatile uint32_t receive = 0;

/*--------------------------------------------------------------------------------------------------------------------------------------
*  Main
--------------------------------------------------------------------------------------------------------------------------------------*/
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		    //Stop watchdog timer
	set_DCO(FREQ_3_MHZ);                                //Set DCO to 3MHz then SMCLK to 3MHz
	UART_init();                                        //Initialize the UART
	EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;                //Clear the receive interrupt flag to allow interrupts to occur
	EUSCI_A0->IE |= EUSCI_A_IE_RXIE;                    //Enable interrupts on the receive flag
	NVIC->ISER[0] = (1 << EUSCIA0_IRQn);                //Enable NVIC on the EUSCIA0
	__enable_irq();                                     //Enable global interrupts

	UART_esc_code(DOWN3);                               //Move cursor down 3
	UART_esc_code(RIGHT5);                              //Move cursor right 5
	UART_print_string("All good students read the");    //Print string onto terminal screen
	UART_esc_code(DOWN1);                               //Move cursor down 1
	UART_esc_code(LEFT15);                              //Move cursor left 15
	UART_esc_code(BLINK);                               //BLINK the next text written
	UART_print_string("TRM");
	UART_esc_code(RESCUR);                              //Reset the cursor to top left of terminal
	UART_esc_code(ATTOFF);                              //Turn all attributes off (blink)
	UART_print_string("Input: ");
	while(1);                                           //Run forever while waiting for interrupts from terminal
}

//EUSCIA0 UART Interrupt Handler
void EUSCIA0_IRQHandler(void){
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG)  {           //Check for receive interrupt
        EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;            //Clear interrupt flag to be able to interrupt again
        while (!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));   //Wait for transmit buffer to be empty before sending more data
        receive = EUSCI_A0->RXBUF;                      //Save value from receive buffer (keyboard input from terminal)
        if (receive == 'R') {                           //Check if capital R is pressed
            UART_esc_code(RED);                         //Change the color using ESC code for change text color to RED
        }
        else if (receive == 'G') {
            UART_esc_code(GREEN);
        }
        else if (receive == 'W') {
            UART_esc_code(WHITE);
        }
        else if (receive == 'B') {
            UART_esc_code(BLUE);
        }
        else {
            EUSCI_A0->TXBUF = receive;                  //If R, G, W, B are not pressed send the data back to the MSP43P401R (echo)
        }
    }

}

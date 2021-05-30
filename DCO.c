//Patrick Reedy; May 14, 2021

/*--------------------------------------------------------------------------------------------------------------------------------------
*  Library Definitions
--------------------------------------------------------------------------------------------------------------------------------------*/
#include "msp.h"
#include "DCO.h"
#include <math.h>

/*--------------------------------------------------------------------------------------------------------------------------------------
*  Function Definitions
--------------------------------------------------------------------------------------------------------------------------------------*/

//Function to set DCOCLK and set other clocks depending on DCO
void set_DCO(uint32_t freq){
    CS->KEY = CS_KEY_VAL;                                                   //Unlock the CS registers
    CS->CTL0 = 0;                                                           //Clear the CTL0 register
    CS->CTL0 = freq;                                                        //Set DCO to desired Frequency
    CS->CTL1 = 0;                                                           //Clear register for new values of the clocks
    CS->CTL1 = (CS_CTL1_SELS__DCOCLK                                        //SMCLK and HSMCLK receieve DCO
              | CS_CTL1_DIVS__1                                             //Divide DCO by 1 or pass DCO
              | CS_CTL1_SELM__DCOCLK                                        //Set MCLK (MCU clock) to DCO
              | CS_CTL1_DIVM__1);
    CS->KEY = 0;                                                            //Lock the CS registers
}

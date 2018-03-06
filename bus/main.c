#include <msp430.h> 
#include "Driver_SPI.h"
#include "Driver_Motor_IR.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    P1OUT = 0x00;                        			// Init ouput to null
   	  P1DIR = BIT0;                        			// P1.0 output
   	  P1DIR &= ~(BIT1 + BIT3 + BIT5 + BIT7);		// P1.1, P1.3, P1.5, P1.7 inputs
   	  P1SEL |= BIT5 + BIT6 + BIT7;					// P1.5, P1.6, P1.7 sel
   	  P1DIR |= BIT6;								// P1.6 output
   	  SPI_Init();							// Initialize SPI connection
   	  Motor_IR_Init();						// Set pwm for ir motor
   	while(1){
   		  TACCR1 = Motor_Set_Deg(0);
   	  }
}
#pragma vector=USI_VECTOR
__interrupt void universal_serial_interface(void)
{
	SPI_Receive_Data();

	// send check begin
	SPI_Send_Data('C');

	// check begin
	TACCR1 = Motor_Set_Deg(0); // set to 0 deg
	__delay_cycles(500000);
	TACCR1 = Motor_Set_Deg(45);  // set to 45 deg
	__delay_cycles(500000);
	TACCR1 = Motor_Set_Deg(90);
	__delay_cycles(500000);
	TACCR1 = Motor_Set_Deg(135); // set to 135 deg
	__delay_cycles(500000);
	TACCR1 = Motor_Set_Deg(180); // set to 180 deg
	__delay_cycles(500000);

	USICNT = 8;                    // re-load counter*/
}

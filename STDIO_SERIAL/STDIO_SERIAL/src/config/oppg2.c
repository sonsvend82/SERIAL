// INCLUDE-files
#include <board.h>
#include <sysclk.h>
#include <stdio_serial.h>
#include <gpio.h>
#include <conf_usart_serial.h>
#include <Egen.h>

int main(void)
{
	init();
	U8 tfFlag = 1; // True/false "boolean"
	const U8 PW[8] = {'1','2','3','4','5','6','7','8'}; // Hardkodet passord
	U8 inputpw[8];
	
	while(true)
	{
		if (usart_rx_is_complete(USART_SERIAL_C0)) // Leser tegn dersom det ligger klare på inport
		{
			for (U8 i=0; i<8; i++) // Leser 8 tegn og lagrer i inputpw[]
			{
				scanf("%c",&inputpw[i]);
				printf("*");
			}
			for (U8 i=0; i<8; i++) // Sjekker om inputpw[] == PW[] og setter "boolean" til false dersom ikke
			{
				if (PW[i] != inputpw[i])
				tfFlag = 0;
			}
			if (tfFlag == 1) // Dersom passord ok
			{
				printf("\n\rPWD-OK\n\r");
				ioport_set_pin_low(LED0);
				for (U8 i=0; i<3; i++) // ca. 3sek med 'åpent' før det lukkes og systemet restarter
				{
					for (volatile U32 j=500000; j>0; j--)
					{
					}
				}
				ioport_set_pin_high(LED0);
			}
			else // Når passord er feil ("boolean" != 1)
			{
				printf("\n\rERROR\n\r");
				for (U8 i=0; i<20; i++)
				{
					for (volatile U32 j=350000; j>0; j--)
					{
					}
					ioport_toggle_pin(LED0);
					ioport_toggle_pin(LED1);
					ioport_toggle_pin(LED2);
					ioport_toggle_pin(LED3);
					ioport_toggle_pin(LED4);
					ioport_toggle_pin(LED5);
					ioport_toggle_pin(LED6);
					ioport_toggle_pin(LED7);
				}
			}
			tfFlag = 1;
		}
	}
}

// Function that initialize clock, board and serial port.
void init(void){
	
	const usart_serial_options_t usart_serial_options =
	{
		.baudrate     = USART_SERIAL_BAUDRATE,
		.charlength   = USART_SERIAL_CHAR_LENGTH,
		.paritytype   = USART_SERIAL_PARITY,
		.stopbits     = USART_SERIAL_STOP_BIT
	};

	sysclk_init();
	//Initialize the board.  The board-specific conf_board.h file contains
	//the configuration of the board initialization.
	board_init();
	// Initialize Serial Interface using Stdio Library
	stdio_serial_init(USART_SERIAL_C0, &usart_serial_options);
	
}



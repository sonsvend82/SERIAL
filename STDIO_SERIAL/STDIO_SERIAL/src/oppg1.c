/*	
	Filnavn:	oppg1.c
	Versjon:	1
	Kommentar:	Leser tegn fra serielport og skriver til serielport
	Forfatter:	Sondre Svendsen
	Historikk:	Når Hvem Hva 
			4/28/2013 SS Oprettet
*/
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
	U8 ch = '*';
	U8 Name[6] = {'S','o','n','d','r','e'};
	volatile U8 hz=0;
	
	while(true)
	{
		if (usart_rx_is_complete(USART_SERIAL_C0)) // Leser et tegn dersom det ligger et klart på inport
		{
			scanf("%c",&ch);
			switch(ch) // Gjør forskjellige ting avhengig av lest tegn
			{
				case 'a': // Skriver ut a x40 + A x40 med blinkende lys.
					for (volatile U8 j=1; j<=40; j++)
					{
						for (volatile U32 i=50000; i>0; i--)
						{
						}
						hz++;
						printf("a");
						if (hz%10==0)
						{
							ioport_toggle_pin(LED0);
						}
					}
					for (volatile U8 j=1; j<=40; j++)
					{
						for (volatile U32 i=50000; i>0; i--)
						{
						}
						hz++;
						printf("A");
						if (hz%10==0)
						{
							ioport_toggle_pin(LED0);
						}
					}					
					break;

				case 'X': // Skriver ut navn fra tabell Name[]
					for(int8_t i = 0; i < 6; ++i)
					{
						printf("%c",Name[i]);
					}
					printf("\n\r");
					break;
			}
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



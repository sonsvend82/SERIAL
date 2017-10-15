/*	
	Filnavn:	oppg3.c
	Versjon:	1
	Kommentar:	Skriver klokke/dato til serielport
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
	U16 Year=2013;
	U8 Month=12;
	U8 Date=31;
	U8 Hour=23;
	U8 Minute=58;
	U8 Second=0;
	
	while(true)
	{
		DelaySec(1);
		Second++;
			
		if(Second==60) // 60 sek i 1min
		{
			Minute++;
			Second=0;
		}
		if(Minute==60) // 60 min i 1 time
		{
			Hour++;
			Minute=0;
		}
		if (Hour==24) // 24timer i 1 dag
		{
			Date++;
			Hour=0;
		}

		// Kalenderåret
		if(Month==1 && Date==32 || Month==2 && Date==29 || Month==3 && Date==32 || Month==4 && Date==31 || Month==5 && Date==32 || Month==6 && Date==31 || Month==7 && Date==32 
			|| Month==8 && Date==32 || Month==9 && Date==31 || Month==10 && Date==32 || Month==11 && Date==31 || Month==12 && Date==32)
		{
			Month++;
			Date=1;
		}

		// 13 måned = +1 år, -12 måned
		if(Month==13)
		{
			Year++;
			Month=1;
		}
		
		// Utdata formattering YYYY/MM/DD HH:MM:SS
		printf("%d", Year);
		if (Month < 10)
		{
			printf("/0%d", Month);
		}
		else
		{
			printf("/%d", Month);
		}			
		if (Date<10)
		{
			printf("/0%d", Date);
		}
		else
		{
			printf("/%d", Date);
		}			
		if (Hour<10)
		{
			printf(" 0%d", Hour);
		}
		else
		{
			printf(" %d", Hour);
		}
		if (Minute<10)
		{
			printf(":0%d", Minute);
		}
		else
		{
			printf(":%d", Minute);
		}
		if (Second<10)
		{
			printf(":0%d", Second);
		}
		else
		{
			printf(":%d", Second);
		}			
		printf("\n\r");
	}
}

// Ca. 1 sek pauseløkke
void DelaySec(U8 Sec)
{
	for (U8 j=Sec;j>0;j--)
	{
		for (volatile U32 i=700000;i>0;i--);
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



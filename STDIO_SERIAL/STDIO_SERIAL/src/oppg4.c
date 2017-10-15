/*	
	Filnavn:	oppg4.c
	Versjon:	1
	Kommentar:	Skriver klokke/dato til serielport, leser tegn fra serielport og forander klokke/dato
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
	U8 ch='*';
	
	while(true)
	{
		DelaySec(1);
		Second++;
		
		if (usart_rx_is_complete(USART_SERIAL_C0)) // Dersom det ligger et tegn klar til å leses gjøres dette
		{
			scanf("%c",&ch);
		}
					
		switch(ch) // Avhengig av hvilket teng som leses gjøres forskjellige ting
		{
			case 'A':
				{
					Year++;
					ch='*'; // Skifter variabel tilbake til utgangspunkt etter forandring.
					break;
				}
			case 'Z':
				{
					Year--;
					ch='*';	
					break;
				}
			case 'S':
				{
					Month++;
					ch='*';
					break;
				}
			case 'X':
				{
					Month--;
					ch='*';
					break;
				}
			case 'D':
				{
					Date++;
					ch='*';
					break;
				}
			case 'C':
				{
					Date--;
					ch='*';
					break;	
				}
			case 'F':
				{
					Hour++;
					ch='*';
					break;
				}
			case 'V':
				{
					Hour--;
					ch='*';
					break;
				}
			case 'G':
				{
					Minute++;
					ch='*';
					break;
				}
			case 'B':
				{
					Minute--;
					ch='*';
					break;
				}
			case 'H':
				{
					Second=0;
					ch='*';
					break;
				}
		}					
			
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
		else if(Minute==255) //Dersom det trekkes fra 1 min fra 00 min blir det 255
		{
			Hour--;
			Minute=59;
		}
		if (Hour==24) // 24timer i 1 dag
		{
			Date++;
			Hour=0;
		}
		else if(Hour==255) // Trekke fra 1 time fra 00 timer blir 255
		{
			Date--;
			Hour=23;
		}
		
		// Kalenderåret
		if(Month==1 && Date==32 || Month==2 && Date==29 || Month==3 && Date==32 || Month==4 && Date==31 || Month==5 && Date==32 || Month==6 && Date==31 || Month==7 && Date==32 
			|| Month==8 && Date==32 || Month==9 && Date==31 || Month==10 && Date==32 || Month==11 && Date==31 || Month==12 && Date==32)
		{
			Month++;
			Date=1;
		}
		
		// Trekke fra dager per måned.
		else if(Month==1 && Date==0)
		{
			Month=12;
			Date=31;
			Year--;
		}
		else if(Month==2 && Date==0)
		{
			Month=1;
			Date=31;
		}
		else if(Month==3 && Date==0)
		{
			Month=2;
			Date=28;
		}
		else if(Month==4 && Date==0)
		{
			Month=3;
			Date=31;
		}
		else if(Month==5 && Date==0)
		{
			Month=4;
			Date=30;
		}
		else if(Month==6 && Date==0)
		{
			Month=5;
			Date=31;
		}
		else if(Month==7 && Date==0)
		{
			Month=6;
			Date=30;
		}
		else if(Month==8 && Date==0)
		{
			Month=1;
			Date=31;
		}
		else if(Month==9 && Date==0)
		{
			Month=8;
			Date=31;
		}
		else if(Month==10 && Date==0)
		{
			Month=9;
			Date=30;
		}
		else if(Month==11 && Date==0)
		{
			Month=10;
			Date=31;
		}
		else if(Month==12 && Date==0)
		{
			Month=11;
			Date=30;
		}
		
		// 0 måned = -1 år, +12 måned
		if(Month==0)
		{
			Year--;
			Month=12;
		}
		// 13 måned = +1 år, -12 måned
		else if(Month==13)
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



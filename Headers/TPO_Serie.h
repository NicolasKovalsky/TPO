#include <stdio.h>                     	// printf() and getchar()
#include <stdlib.h>
#include <ctype.h>                     	// tolower() and toint()


//-----------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F02x
//-----------------------------------------------------------------------------

sfr16 DP       = 0x82;                 // data pointer
sfr16 RCAP3    = 0xCA;                 // Timer3 reload value
sfr16 TMR3     = 0xCC;                 // Timer3 counter
sfr16 ADC0     = 0xbe;                 // ADC0 data
sfr16 ADC0GT   = 0xc4;                 // ADC0 greater than window
sfr16 ADC0LT   = 0xc6;                 // ADC0 less than window
sfr16 RCAP2    = 0xca;                 // Timer2 capture/reload
//sfr16 T2       = 0xcc;                 // Timer2
sfr16 RCAP4    = 0xCA;                 // Timer4 capture/reload
//sfr16 T4       = 0xCC;                 // Timer4
sfr16 DAC0     = 0xd2;                 // DAC0 data
sfr16 DAC1     = 0xd2;                 // DAC1 data

#define		DIRECCION_DE_CHECKSUM_1			0x00FF		//posicion de memoria donde se guardan los checksum, 
														//tienen que estar antes de 0x1000 por que ahi esta el codigo

#define		DIRECCION_DE_CHECKSUM_2			0x00FE
#define		DIRECCION_DE_GRABACION			0x00FA
//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
#define TRUE         1
#define FALSE        0

#define ERROR		1
#define OK			0

#define SYSCLK       			11059200          	// SYSCLK frequency in Hz
#define BAUDRATE     			9600            	// Baud rate of UART in bps
#define	CODIGO_PARA_PROGRAMAR	0x49
#define	DIR_COMIENZO_PROGRAMA	0x0100				//Ubicacion del codigo del programa principal

#define	t_2500us_H		0xfd
#define	t_2500us_L		0x1f

void SYSCLK_Init (void);
void PORT_Init (void);
void UART0_Init (void);


//void Prender_Leds(unsigned char);
void print_menu(void);
void Sacar_Caracter_x_Puerto_Serie(unsigned char );
unsigned char Tomar_Caracter_del_Puerto_Serie();
void Sacar_Cadena_x_Puerto_Serie(unsigned char *);
void Inicializacion_Timer(void);


#define TX_BUFFERSIZE	15
#define RX_BUFFERSIZE	15

unsigned char PushTx(unsigned char);
unsigned char PopTx(unsigned char *);
unsigned char PushRx(unsigned char);
unsigned char PopRx(unsigned char *);
void StartTx(void);





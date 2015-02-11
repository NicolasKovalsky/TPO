
#include <Headers/TPO_Serie.h>
#include <Headers/TPO_PS2.h>
#include <C8051F020.H>

unsigned char	Puerto_Serie = 0;
void inicializacionTPO (void){
	WDTCN = 0xde;                       // disable watchdog timer
	WDTCN = 0xad;
	
	EA = 0;                             // disable interrupts (this statement
										// is needed because the device is not
										// neccesarily in a reset state prior 
										// to executing this code) 
		
	PORT_Init ();                       // initialize crossbar and GPIO
	SYSCLK_Init ();                     // initialize oscillator


	Inicializacion_Timer();

	UART0_Init ();                      // initialize UART0
	initial_interrupt();
	EA=1;

}								// end main 
void Inicializacion_Timer(void)
{
//------------------ TIMER 0 -----------------------------------
// Timer 0:	
//						  SYSCLK
//			Cuenta =    ___________
//			     		(65536-Tn)
//
//			Cuenta = tiempo que quiero contar. ej 2500 Hz
//
//			SYSCLK = Xtal
//--------------------------------------------------------------
	TMOD = 0x21;					// Configuro el modo 1 de funcionamiento para el timer 0
	CKCON = 0x10;				   	// Configuro el divisor del clock

	TH0 = t_2500us_H ;	
	TL0 = t_2500us_L ;
	
	TR0 = 1;						// Es un bit de TCON, Habilito el timer 0 para muestrar en tiempo
	TF0 = 0;
	ET0 = 1;
	
	
}

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// SYSCLK_Init
//-----------------------------------------------------------------------------
//
// This routine initializes the system clock to use an 22.1184MHz crystal
// as its clock source.
//
void SYSCLK_Init(void)
{
	unsigned int i;						// Variable local
	
	OSCXCN = 0x67;						// Configuro el registro de control del oscilador 
										// 01100111
										// Habilito el oscilador para funcionar con cristal (22.1184MHz)
										// Configuro el rango de trabajo del oscilador
	
	for (i=0; i < 256; i++);			// Demora "Cuidado esta demora (bloqueante) se puede hacer porque 
										// estoy en la inicializacion y no bloqueo ningun otro proceso!!!!
										// Hay que hacer esta demora para que se estabilice el oscilador

	while (!(OSCXCN & 0x80));			// Espero hasta que se estabilice (Cuidado es bloqueante!!)

	OSCICN = 0x88;						// Configuro el oscilador interno
										// 10001000
										// Configuro el micro para utilizar el oscilador externo

	while (!(OSCXCN & 0x80));			// Espero hasta que se estabilice (Cuidado es bloqueante!!)

	OSCICN = 0x08;						// Configuro el oscilador interno
										// 00001000
										// Configuro el micro para utilizar el oscilador externo
}
//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------
//
// Configure the Crossbar and GPIO ports
//
//------------------------------------------------------------------------------------
// PORT_Init
//------------------------------------------------------------------------------------
void PORT_Init(void)
{
									//										76543210
	XBR0 = 0x45;					// Enable UART0 y el  					00000110
	XBR1 = 0x1E;					// Enable /INT0 E /INT1	   				00010100
	XBR2 = 0x44;					// Enable crossbar, UART1				01000100
									// and weak pull-ups globally enable
	
////  Port Output Mode Register (Open Drain or Push Pull)
	P0MDOUT = 0x0f;      			  
	P1MDOUT = 0xF0;      
	P2MDOUT = 0x56;      
	P3MDOUT = 0x00;      
	P1=0xAF;
	P74OUT = 0xFB;	
	P5 = 0x0f;				// Configuro el puerto 5 como push-pull	el 
									// nibble alto y open-drain el nibble bajo
}


//-----------------------------------------------------------------------------
// UART0_Init
//-----------------------------------------------------------------------------
//
// Configure the UART0 using Timer1, for <baudrate> and 8-N-1.
//
void UART0_Init (void)
{
	TR1 = 0;						// Timer 1 y 0 apagados
	TMOD = 0x21;						// Timer 1 control por TR1, timer auto reload
	CKCON = 0x10;						// T1CLK = SYSCLK

//#ifdef F120
	TH1 = -(SYSCLK/BAUDRATE/16);		// set Timer1 reload value for baudrate
//#else
//   	TH1 = -(SYSCLK/BAUDRATE/32);		// set Timer1 reload value for baudrate
//#endif

	TR1 = 1;                        	// start Timer1



	SCON0 = 0x50;                     	// SCON0: mode 1, 8-bit UART, enable RX

	PCON = 0x80;

	TI0    = 0;
	TR0=1;                         // Indicate TX0 ready
	ES0=1;
}





void Sacar_Caracter_x_Puerto_Serie(unsigned char Caracter)
{
	PushTx(Caracter);

}

void Sacar_Cadena_x_Puerto_Serie(unsigned char *Buffer)
{
	unsigned char i;																			 
	
	for(i = 0 ; Buffer[i] != 0 ; i++)
	{				
		PushTx(Buffer[i]);	
	}
}	





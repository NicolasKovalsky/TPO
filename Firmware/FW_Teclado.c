#include <Headers/TPO_General.h>
#include <Headers/TPO_Teclado.h>

extern bit Request_Time_Elapsed;
extern bit ShowTime_Elapsed;

unsigned int espera_pantalla;
unsigned int espera_request;
extern unsigned char tecla;


sbit A = P1^3;

	
void Timer_Tick(void) interrupt 1	
{

	TR0 = 0;
	TH0 = t_2500us_H;
	TL0 = t_2500us_L + TL0;
	TR0 = 1;

	ReboteTecla();
	if(espera_pantalla)
	{
		espera_pantalla--;
		if(!espera_pantalla)
			ShowTime_Elapsed=1; 
	}
	if(espera_request)
	{
		espera_request--;
		if(!espera_request)
			Request_Time_Elapsed=1; 
	}
 
 }

void ReboteTecla( void )
{
	static unsigned char CodigoAnterior = NO_KEY ;
	static unsigned char EstadosEstables = 0 ;
	unsigned char CodigoActual ;
	  
	CodigoActual = LecturaTecla4x2( );				
	
	if( CodigoActual == NO_KEY ) {  //!< No se pulso tecla o rebote
		CodigoAnterior = NO_KEY ;
		EstadosEstables = 0 ;
		return ;
	}

	if( EstadosEstables == 0 )	{  //!< Primera vez
		CodigoAnterior = CodigoActual ;
		EstadosEstables = 1 ;
		return ;
	}

	if( EstadosEstables == CANTIDADdErEBOTES )	{  	//!< Acepto la tecla
		EstadosEstables = CANTIDADdErEBOTES + 1;	//!< Hará que no vuelva a entrar hasta que suelten la tecla
		tecla = CodigoAnterior ;	
		return ;
	}
	
	if( EstadosEstables > CANTIDADdErEBOTES )		//!< La tecla sigue pulsada
		return ;

	if( CodigoActual == CodigoAnterior )
		EstadosEstables ++ ;
	else
		EstadosEstables = 0 ;	
	return ;
}

	
unsigned char  LecturaTecla4x2 ( void ) 
{
	P5=0xFF;
	
	
	P5&= 0x7F;
	

	if (C0 == ON)
		return 1;
	if (C1==ON)
		return 2;
	if (C2==ON)
		return 3;
	P5=0xFF  ;
	P5&= 0xBF;
	if (C0 == ON)
		return 4;
	if (C1==ON)
		return 5;
	if (C2==ON)
		return 6;
	P5=0xFF;
	P5&= 0xDF;
	
	if (C0 == ON)
		return 7;
	if (C1==ON)
		return 8;
	if (C2==ON)
		return 9;
	P5=0xFF;
	P5&=0xEF;
	if (C0 == ON)
		return 10;
	if (C1==ON)
		return 11;
	if (C2==ON)
		return 12;
	

	return NO_KEY;
}



#include <C8051F020.H>
#include "Headers/TPO_Serie.h"

extern char f_startTx;


void StartTx(void)
{
	TI0=1;	
}

void Serial (void) interrupt 4
{
	unsigned char aux;
	if (TI0)							//Si se interrumpi� por transmisi�n
	{
		TI0 = 0;						//Borro flag de transmisi�n serie
		if(PopTx(&aux))
			SBUF0 = aux;
		else
			f_startTx = 0;

	}
	if (RI0)						   //Si se interrumpi� por recepci�n.
	{
		RI0 = 0;					   //Borro flag de recepci�n serie
		PushRx(SBUF0);
	}
}
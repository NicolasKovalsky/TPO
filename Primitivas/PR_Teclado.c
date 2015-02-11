
#include <Headers/TPO_General.h>
#include <Headers/TPO_Teclado.h>

extern unsigned char tecla;	//!< buffer de teclado


unsigned char Teclado (void)
{
	unsigned char Tecla;
	
	Tecla = tecla;
	tecla = NO_KEY;

	return Tecla;
}

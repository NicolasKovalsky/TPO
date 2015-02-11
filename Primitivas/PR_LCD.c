#include <C8051F020.H>
#include "Headers/TPO_LCD.h"


void wrt_string(unsigned char *string)
{
	TR0=0;
	busy();
	while(*string)
		wrt_data(*string++);
	TR0=1;
	busy();
	busy();
	busy();
}


void LcdMoveCursor(unsigned char x, unsigned char y)

{                                                                                                
	unsigned char comando=DDRA_LINEA1;
	switch(x)
	{
		case 1:
		{
			comando=DDRA_LINEA1+y-1;
		}break;
		case 2:
		{
			comando=DDRA_LINEA2+y-1;
		}break;
		case 3:
		{
			comando=DDRA_LINEA3+y-1;
		}break;
		case 4:
		{
			comando=DDRA_LINEA4+y-1;
		}break;
		default:break;
	}
		wrt_cmd(comando);

} 
#include <Headers/TPO_Scancodes.h>
#include <Headers/TPO_General.h>
#include <Headers/TPO_PS2.h>
#include <Headers/TPO_LCD.h>


sbit Data = P1^2;


extern unsigned char NroClienteRecibido;
extern unsigned int Key_Data;    //Data pin
extern unsigned int bc;        //bit count

unsigned char contador =0;
unsigned int a =0;
unsigned char b =0;
unsigned int g = 0;
unsigned int p = 0;
unsigned int q = 0;
unsigned int j=0;
extern xdata unsigned char ID_Cliente[9];
extern xdata unsigned char buffer_datos[tam_buffer];
extern unsigned char flag_receive;
void int_EX0(void) interrupt 0     //INT1 P3_2 (Clock)
{                                        //Data come with Clock from Device to MCU together
	//-------------------------------------
  if(NroClienteRecibido == 0 && flag_receive == 0)
	{
		if(Data == 1)
		Key_Data = (Key_Data >> 1) | 0x8000;
	else
		Key_Data = (Key_Data >> 1) | 0x0000;

	bc += 1;
	if( bc == 11)
	{
		Key_Data = Key_Data >> 6;
		buffer_datos[j]= Key_Data;  // recibo todos los datos del lector y los guardo en un ID_Cliente							
		bc = 0;
		Key_Data = 0x0000;    
				j++;
		}

	
		if(buffer_datos[j-1]==0x5A && buffer_datos[j-2]==0xF0)
		{
				j=0;										// ponga j=0 porq sino cuando quiero hacer una segunda lectura entra directo al 
				flag_receive = 1;				// if como si hubiese recibido todo
		}
	}

}

void initial_interrupt(void){

	PX0 = 1;    //interrupt EX0 is first
	EX0 = 1;    //enable INT0
	IT0 = 1;    //negative enable
	EA = 1;        //Interrupt enable

}
void guardar_y_convertir() // ahora cree la funcion guardar para que la interrupt no sea tan larga..
{
			if(flag_receive)
			{
				p=0;
				if(buffer_datos[0]==0xFF) p=3;
				if(buffer_datos[p+24]== 0x5A && buffer_datos[p+26]== 0x5A)
				{
					q=p;
					for(p=0; p < 8 ; p++)
					{
						ID_Cliente[p]=buffer_datos[(3*p)+q];    //guardo los datos importantes(filtro el F0 y la repeticion de la tecla)
								for(a = 0; unshifted[a][0]!=ID_Cliente[p] && unshifted[a][0]; a++);
								if (unshifted[a][0] == ID_Cliente[p]) 
								{
									if(ID_Cliente[p]==0x16||ID_Cliente[p]==0x1e||ID_Cliente[p]==0x26||ID_Cliente[p]==0x25||ID_Cliente[p]==0x2e // verificacion que ya no sirve pero la dejo por paja, era para verificar que esos
									||ID_Cliente[p]==0x36||ID_Cliente[p]==0x3d||ID_Cliente[p]==0x3e||ID_Cliente[p]==0x46||ID_Cliente[p]==0x45) // codigos correspondan con un numero
									{
									ID_Cliente[p]=unshifted[a][1];
									}
								}
						}
					ID_Cliente[p]= '\0';
					NroClienteRecibido = 1;
					}
					else
					{
						//wrt_cmd(LCD_CLEAR);
						LcdMoveCursor(2,1);
						wrt_string("Codigo invalido");
					}
					flag_receive=0;				
					for(p=0; p < tam_buffer; p++)
					{
					buffer_datos[p] = 0x00;         // limpio el ID_Cliente de datos
					}
			}
}





void fantasma_escritor (char flag){
	static char cursor=1;
	if (flag){
		if (NroClienteRecibido == 1)
		{
					LcdMoveCursor(2, cursor);
					wrt_string(ID_Cliente);
				for(g=0; g < 8 ; g++)	// tengo por condicion g < 8 porq trabajo con el ID_Cliente ¨limpio¨
					{		
									
					ID_Cliente[g] = 0x00; //a medida que muestro voy limpiando el ID_Cliente
					}
			NroClienteRecibido = 0;
				//ahora mando el cursor de nuevo al comienzo para cuando haga una segunda lectura se escriba arriba de la primera
			}
	}
}


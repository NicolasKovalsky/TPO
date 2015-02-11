#include <Headers/TPO_General.h>
#include <Headers/TPO_Teclado.h>
#include <Headers/TPO_Serie.h>
#include <Headers/TPO_LCD.h>


unsigned char tecla = NO_KEY ;	//!< ID_Cliente de teclado

extern unsigned char PUERTO_SERIE;
unsigned char input [10];
unsigned int numero=1;
unsigned int k;
unsigned char key;
unsigned char dato;
unsigned char flag = 0;
unsigned char estado=0;
unsigned int indice=0;
unsigned char flagdisplays = 1;
extern unsigned char dataready;
unsigned char NroClienteRecibido;
unsigned int Key_Data;    //Data pin
unsigned int bc=0;        //bit count
xdata char ID_Cliente[9];  
xdata char buffer_datos[tam_buffer];
xdata char buffer_envio [15];
xdata char Serial_Data[16];
xdata char Comando_Buff[16];
//xdata char flagcomandorecibido=0;
xdata char Datos_Recibidos=0;
xdata char i;
xdata char h;
unsigned char flag_receive;
extern unsigned int espera_pantalla;
extern unsigned int espera_request;
bit Request_Time_Elapsed;
bit ShowTime_Elapsed;
xdata char cantidad[5];
xdata char hay_cant;


void main (void)
{
		
	InicializacionTPO();
	//Inicializar	( );
	lcd_init();
	Clear_LCD();
	LcdMoveCursor(1,1);
	wrt_string("Ingrese Cod. Op:");
	flag=1;
	flagdisplays=0;
	Reset_Comando();
	
	
	while( 1 )
	{
		
		
		maqTeclado();
		guardar_y_convertir();
		maqserie();	
		MaquinaAplicacion();
		fantasma_escritor(flag);
		
	}

}


void MaquinaAplicacion (void){
xdata unsigned int aux=0;
aux=comando();
switch (estado){
	case ESPERANDO_COMANDO:
		
		if(NroClienteRecibido && aux==GET_SALDO) {
			Request_Saldo();
			estado = ESPERANDO_SALDO;
		}
		if(aux==GET_PRODUCTO) {
			Request_Producto();
			estado = ESPERANDO_DATOS_PRODUCTO;
		}
		if(NroClienteRecibido && aux==CARGA_SALDO) {
			Request_Carga();
			estado = ESPERANDO_RESULTADO_CARGA;
		}
		if(abortar()){
		   Reset_Comando();
		}
		if(Datos_Recibidos|| Serial_Data[0]!=0x00){
				Reset_SerialData();
		}
		
		
	break;
	case ESPERANDO_SALDO:
		if(Datos_Recibidos){
			Mostrar_Saldo();
			estado = MOSTRANDO_SALDO;
		}
		if(Request_Time_Elapsed){
		Request_Time_Elapsed=0;
		Reset_Comando();
		estado=ESPERANDO_COMANDO;
		}
	break;
	case ESPERANDO_RESULTADO_CARGA:
		if(Datos_Recibidos){
			Mostrar_Resultado_Carga();
			estado = MOSTRANDO_RESULTADO_CARGA;
		}
		if(Request_Time_Elapsed){
		Request_Time_Elapsed=0;
		Reset_Comando();
		estado=ESPERANDO_COMANDO;
		}
	break;
	case ESPERANDO_DATOS_PRODUCTO:
	   if(Request_Time_Elapsed){
		Request_Time_Elapsed=0;
		Reset_Comando();
		estado=ESPERANDO_COMANDO;
		}
	   if(Datos_Recibidos){
			Mostrar_Datos_Producto();
			estado = MOSTRANDO_DATOS_PRODUCTO;
			Request_Time_Elapsed=0;
		}
		
	break;
	case  MOSTRANDO_SALDO:
		if(ShowTime_Elapsed){
		ShowTime_Elapsed=0;
		Reset_Comando();
		estado=ESPERANDO_COMANDO;
		}
	break;
	case  MOSTRANDO_RESULTADO_CARGA:
		if(ShowTime_Elapsed){
		ShowTime_Elapsed=0;
		Reset_Comando();
		estado=ESPERANDO_COMANDO;
		}
	break;
	case  MOSTRANDO_DATOS_PRODUCTO:
		if(ShowTime_Elapsed){
		ShowTime_Elapsed=0;
		Reset_Comando();
		estado=ESPERANDO_COMANDO;
		}
		if(NroClienteRecibido) {
			Request_Transaccion();
			estado = ESPERANDO_RESULTADO_TRANSACCION;
			ShowTime_Elapsed=0;
		}
	break;
	case ESPERANDO_RESULTADO_TRANSACCION:
	   if(Request_Time_Elapsed){
	   Request_Time_Elapsed=0;
		Reset_Comando();
		estado=ESPERANDO_COMANDO;
		}
	   if(Datos_Recibidos){
			Mostrar_Resultado_Transaccion();
			estado = MOSTRANDO_RESULTADO_TRANSACCION;
		}
		
	break;
	case  MOSTRANDO_RESULTADO_TRANSACCION:
		if(ShowTime_Elapsed){
		ShowTime_Elapsed=0;
		Reset_Comando();
		estado=ESPERANDO_COMANDO;
		}
	break;
	}
}

void maqTeclado(void){
	key=Teclado();
		switch (key)
		{
			case T1:
				 Comando_Buff[indice] = '1';
					Comando_Buff[indice+1] = 0x00;
					indice++;
					LcdMoveCursor(2,1);
					wrt_string(Comando_Buff);
				break;
			case T2:
				 Comando_Buff[indice] = '2';
			Comando_Buff[indice+1] = 0x00;		
			indice++;
			LcdMoveCursor(2,1);
					wrt_string(Comando_Buff);
				break;
			case T3:
				Comando_Buff[indice] = '3';
			Comando_Buff[indice+1] = 0x00;
					indice++;
					LcdMoveCursor(2,1);
					wrt_string(Comando_Buff);
				//Sacar_Caracter_x_Puerto_Serie('$');
			break;
			case T4:
				Comando_Buff[indice] = '4';
			Comando_Buff[indice+1] = 0x00;
					indice++;
					LcdMoveCursor(2,1);
					wrt_string(Comando_Buff);
					
				break;
			case T5:
				Comando_Buff[indice] = '5';
			Comando_Buff[indice+1] = 0x00;
					indice++;
					LcdMoveCursor(2,1);
					wrt_string(Comando_Buff);
			break;
			case T6:
				Comando_Buff[indice] = '6';
			Comando_Buff[indice+1] = 0x00;
					indice++;
					LcdMoveCursor(2,1);
					wrt_string(Comando_Buff);
				break;
			case T7:
				Comando_Buff[indice] = '7';
			Comando_Buff[indice+1] = 0x00;
					indice++;
					LcdMoveCursor(2,1);
		wrt_string(Comando_Buff);
				break;
			case T8:
				Comando_Buff[indice] = '8';
			Comando_Buff[indice+1] = 0x00;
					indice++;
					LcdMoveCursor(2,1);
					wrt_string(Comando_Buff);
				break;
			case T9:
				Comando_Buff[indice] = '9';
			Comando_Buff[indice+1] = '\0';
					indice++;
					LcdMoveCursor(2,1);
		wrt_string(Comando_Buff);
				break;
			case T10:
				Comando_Buff[indice] = '*';
			Comando_Buff[indice+1] = 0x00;
					indice++;
					LcdMoveCursor(2,1);
		wrt_string(Comando_Buff);
				break;
			case T11:
				Comando_Buff[indice] = '0';
			Comando_Buff[indice+1] = 0x00;
					indice++;
					LcdMoveCursor(2,1);
					wrt_string(Comando_Buff);
				break;
			case T12:
				Comando_Buff[indice] = '#';
			Comando_Buff[indice+1] = 0x00;
					indice++;
					LcdMoveCursor(2,1);
					wrt_string(Comando_Buff);
				break;
		}
}		

void maqserie(void){
	static xdata int i;
	static xdata int a=0;
	i=0;
	if(Serial_Data[0]==0x00)
		a=0;
	if(dataready==1) {
		PopRx(&Serial_Data[a]);
		if(a!=15){
			a++;
		}else{
			Datos_Recibidos=1;
		}
}

	while(Serial_Data[i]){
		if (Serial_Data[i]=='#'){
			Datos_Recibidos=1;
			a=0;
			Serial_Data[i+1]='\0';
		}	
	  i++;
	}
}

int abortar (void)
{
	int g=0;
	for	(g=0;g<14;g++)
	{
		if(Comando_Buff[g]=='*' && Comando_Buff[g+1]=='*')
		return(1);
	}
	return(0);
}

int comandorecibido (void){
	xdata char i;
	for (i=0;Comando_Buff[i]!=0x00;i++);
	if (Comando_Buff[i-1]=='#'&&(i-1)!=0)
		return 1;
	return 0;	
}

int comando(void)
{		
	if (Comando_Buff[0]=='*'&& comandorecibido())
	{
		return CARGA_SALDO;
	}
	else if (Comando_Buff[0]==0x00)
	{
		return GET_SALDO;
	}
	else if (comandorecibido())
	{
		return GET_PRODUCTO;
	}
	return 0;
}

void Reset_Comando(void){
	xdata char i;
	for (i=0;i<16;i++){
		Comando_Buff[i]=0x00;
	}
	indice = 0;
	Reset_SerialData();
	Clear_LCD();
	LcdMoveCursor(1,1);
	wrt_string("Ingrese Cod. Op:");
}

void Reset_SerialData (void){
	for (i=0;i<16;i++){
		Serial_Data	[i]=0x00;	 
	}
	Datos_Recibidos=0;
}

void Request_Carga (void)
{
	Clear_LCD();
	LcdMoveCursor(1,1);
	wrt_string("Espere carga...");
	Sacar_Caracter_x_Puerto_Serie('d');
	Sacar_Cadena_x_Puerto_Serie(ID_Cliente);
	for(h=1;Comando_Buff[h]!='#';h++){
			Sacar_Caracter_x_Puerto_Serie(Comando_Buff[h]);
	}
	Sacar_Caracter_x_Puerto_Serie('#');	
	espera_request=TIMER_2SEG;
	Request_Time_Elapsed=0;
}

void Request_Transaccion(void){
	Clear_LCD();
	LcdMoveCursor(1,1);
	wrt_string("Espere trans...");
	Reset_SerialData();
	Sacar_Caracter_x_Puerto_Serie('c');
	for (k=0; Comando_Buff[k]!='$';k++ );
	Sacar_Cadena_x_Puerto_Serie(ID_Cliente);
	k++;
	while(Comando_Buff[k]!='#'){
	Sacar_Caracter_x_Puerto_Serie(Comando_Buff[k]);
	k++;
	}
	Sacar_Caracter_x_Puerto_Serie('#');
	espera_request=TIMER_2SEG;
	Request_Time_Elapsed = 0;
}		

void Request_Producto(void){
	Clear_LCD();
	LcdMoveCursor(1,1);
	wrt_string("Espere prod...");
	Sacar_Caracter_x_Puerto_Serie('b');
	h=0;
	hay_cant=0;
	while(Comando_Buff[h]){
		if (Comando_Buff[h]=='*' && h!=0){
			hay_cant=1;
		}
		h++;
	}
	if(hay_cant){
		for(h=0;Comando_Buff[h]!='*';h++){
			Sacar_Caracter_x_Puerto_Serie(Comando_Buff[h]);
		}
		Sacar_Caracter_x_Puerto_Serie(',');
		Sacar_Caracter_x_Puerto_Serie(Comando_Buff[h+1]);
		Sacar_Caracter_x_Puerto_Serie(Comando_Buff[h+2]);
		Sacar_Cadena_x_Puerto_Serie("#");
	}else{
		Sacar_Caracter_x_Puerto_Serie('1');
		Sacar_Caracter_x_Puerto_Serie(',');
		Sacar_Caracter_x_Puerto_Serie(Comando_Buff[0]);
		Sacar_Caracter_x_Puerto_Serie(Comando_Buff[1]);
		Sacar_Cadena_x_Puerto_Serie("#");
	}
	espera_request=TIMER_2SEG;
	Request_Time_Elapsed  =0;
}

void Request_Saldo(void){
	Clear_LCD();
	LcdMoveCursor(1,1);
	wrt_string("Espere saldo...");	
	Sacar_Caracter_x_Puerto_Serie('a');
	Sacar_Cadena_x_Puerto_Serie(ID_Cliente);
	Sacar_Caracter_x_Puerto_Serie('#');
	espera_request=TIMER_2SEG;
	Request_Time_Elapsed =0;
}	

void Mostrar_Saldo(void){
	Clear_LCD();
	LcdMoveCursor(1,1);
	wrt_string(Serial_Data);
	espera_pantalla=TIMER_2SEG;
	ShowTime_Elapsed=0; 
}
void Mostrar_Resultado_Carga(void){
	Clear_LCD();
	LcdMoveCursor(1,1);
	wrt_string(Serial_Data);
	espera_pantalla=TIMER_2SEG;
	ShowTime_Elapsed=0;
}
void Mostrar_Datos_Producto(void){
	Clear_LCD();
	LcdMoveCursor(1,1);
	wrt_string(Serial_Data);
	espera_pantalla=TIMER_2SEG;
	ShowTime_Elapsed=0;
}
void Mostrar_Resultado_Transaccion(void){
	Clear_LCD();
	LcdMoveCursor(1,1);
	wrt_string(Serial_Data);
	espera_pantalla=TIMER_2SEG;
	ShowTime_Elapsed=0;
}
						
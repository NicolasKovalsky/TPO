
#include <c8051f020.h>

/**	
 *	\brief Constantes simbolicas
*/
#define	t_2500us_H		0xfd
#define	t_2500us_L		0x1f

#ifndef __DRIVERS_FW__
#define __DRIVERS_FW__


#define BaudsH  0xFF            /* Velocidad del Puerto Serie    */
#define BaudsL  0xDC            /* 9600bps con Xtal 11.0592MHz   */

#define BAUDRATE     			9600            	// Baud rate of UART in bps
#define PUERTO_0		0

#define SYSCLK       			11059200          	// SYSCLK frequency in Hz

#define TMOD_INICIAL	
#define RECARGA_T1		-(SYSCLK/BAUDRATE/16);		 //Para 9600 baudios a fxtal = 11.0592MHz

void InicializacionSerie(void);
void StartTx(void);
void Inicializacion_Timer(void)	 ;

#endif 	/*__DRIVERS_FW__*/

#define ACTPIN(puerto, pin) ((puerto)|=(0x01<<(pin)))
#define PASPIN(puerto, pin) ((puerto)&=~(0x01<<(pin)))

#define DDRA_LINEA1 0x80    //1000 0000
#define DDRA_LINEA2 0xC0    //1100 0000
#define DDRA_LINEA3 0x94    //1001 0100
#define DDRA_LINEA4 0xD4    //1101 0100
#define CARGARSALDO 1
#define OPERACIONPRODUCTO 2
#define ESPERANDORESPUESTA 3
#define DATORECIBIDO 4
#define VERSALDO 5
/**	
 *	\brief Prototipos de Drivers
*/
void Inicializar( void ) ;
void SYSCLK_Init( void ) ;
void PORT_Init( void ) ;
void UART0_Init (void);
void Apagar_Todo(void);
void Sacar_Caracter_x_Puerto_Serie(unsigned char);
unsigned char Tomar_Caracter_del_Puerto_Serie();
void Sacar_Cadena_x_Puerto_Serie(unsigned char *);
void LcdMoveCursor(unsigned char , unsigned char );
void wrt_data(unsigned char );
void fantasma_escritor (char );
void InicializacionTPO (void);
void guardar_y_convertir();
void maqTeclado(void);
//void MaqOperacion (void);
void maqserie(void);

//APLICACION!!!
void MaquinaAplicacion (void);
void Mostrar_Resultado_Transaccion(void);
void Mostrar_Datos_Producto(void) ;
void Mostrar_Resultado_Carga(void);
void Mostrar_Saldo(void);
void Request_Saldo(void);
void Request_Producto(void);
void Request_Transaccion(void);
void Request_Carga (void);
void Reset_Comando(void);
void Reset_SerialData(void);
int comando(void);
int comandorecibido (void);
int abortar (void);

#define ESPERANDO_COMANDO					0
#define ESPERANDO_SALDO						1
#define ESPERANDO_RESULTADO_CARGA			2
#define ESPERANDO_DATOS_PRODUCTO			3
#define MOSTRANDO_SALDO						4
#define MOSTRANDO_RESULTADO_CARGA			5
#define MOSTRANDO_DATOS_PRODUCTO			6
#define ESPERANDO_RESULTADO_TRANSACCION		7
#define MOSTRANDO_RESULTADO_TRANSACCION		8

#define GET_SALDO 1	
#define GET_PRODUCTO 2
#define CARGA_SALDO	3	   


#define tam_buffer 30
#define TIMER_2SEG 5000
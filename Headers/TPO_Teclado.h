
/**	
 *	\brief Constantes simbolicas para hardware
*/
#define		NO_KEY				0xff
#define		CANTIDADdErEBOTES	4
/**	
 *	\brief Declaraciones de hardware
*/

	//sbit Fi0	= P5^7;
	//sbit Fi1	= P5^6;
	//sbit Fi2	= P5^5;
	//sbit Fi3	= P5^4;
	#define C0	((P5>>3)&0x01)
	#define C1	((P5>>2)&0x01)
	#define C2 ((P5>>1)&0x01)
  /*
	sbit Fi0	= P1^0;
	sbit Fi1	= P1^1;
	sbit Fi2	= P1^2;
	sbit Fi3	= P1^3;
	sbit C0	= P1^4;
	sbit C1	= P1^5;
	*/
	#define ON 0

/**	
 *	\brief Prototipos de Primitivas
*/
unsigned char Teclado ( void );

/**	
 *	\brief Prototipos de Drivers
*/
unsigned char  LecturaTecla4x1 ( void ); 
unsigned char  LecturaTecla4x2 ( void );
 void ReboteTecla( void );
#define CHANGEBIT(port,bit) (port^=(0x01<<bit))

#define T1 1
#define T2 2
#define T3 3
#define T4 4
#define T5 5
#define T6 6
#define T7 7
#define T8 8
#define T9 9
#define T10 10
#define T11 11
#define T12 12


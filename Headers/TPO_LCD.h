#define _LCDCMD_H

#define LCD_PORT P6

#define DDRA_LINEA1 0x80    //1000 0000
#define DDRA_LINEA2 0xC0    //1100 0000
#define DDRA_LINEA3 0x94    //1001 0100
#define DDRA_LINEA4 0xD4    //1101 0100

#define setbitp(puerto,pin,activo) puerto=(activo==ACTIVO_ALTO) ? puerto|(1<<pin) : puerto&~(1<<pin)
#define clrbitp(puerto,pin,activo) puerto=(activo==ACTIVO_BAJO) ? puerto|(1<<pin) : puerto&~(1<<pin)
#define ifpinp(puerto,pin,estado) (((puerto<<pin)&0x01)==estado) ? ON : OFF

#define ACTIVO_ALTO 1
#define ACTIVO_BAJO 0

#define _LCD_H

void lcd_init(void);		// Initialize LCD
void busy(void);			// Check Busy
void wrt_cmd(unsigned char);		// Sending Command
void wrt_data(unsigned char);		// Sending single character
void wrt_string(unsigned char*);	// Sending String
void wrt_value(unsigned char);		// Sending 8-bit Decimal value
void LcdWriteCmd(unsigned char cmd);
void waitUntilDone();
void LcdClear (void);
bit isLcdBusy(void);
void Clear_LCD(void);


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	LCD Command MACROS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define LCD_CLEAR 0x01
#define RETURN_HOME 0x02
#define DEC_CURSOR 0x04
#define INC_CURSOR 0x06
#define DISP_OFF_CUR_OFF 0x08
#define DISP_OFF_CUR_ON 0x0A
#define DISP_ON_CUR_OFF 0x0C
#define DISP_ON_CUR_BLINK 0xE
#define SHIFT_CUR_LEFT 0x10
#define SHIFT_CUR_RIGHT 0x14
#define SHIFT_DISP_LEFT 0x18
#define SHIFT_DISP_RIGHT 0x1C








#include <Headers/TPO_LCD.h>
#include <c8051f020.h>

/*
 * LCD commands.
 */


// return cursor and LCD to home position:
const unsigned char LCD_HOME = (1 << 1);

// set cursor move direction:
const unsigned char LCD_MOVEDIR = (1 << 2);
// shift display when byte written to display
const unsigned char LCD_MOVEDIR_SHIFT = (1 << 0);
// increment the cursor after each byte written:
const unsigned char LCD_MOVEDIR_ID = (1 << 1);

// Enable display/cursor:
const unsigned char LCD_DISPEN = (1 << 3);
// turn cursor blink on:
const unsigned char LCD_DISPEN_BLINK = (1 << 0);
// turn cursor on:
const unsigned char LCD_DISPEN_CURSOR = (1 << 1);
// turn display on:
const unsigned char LCD_DISPEN_DISP = (1 << 2);

// move cursor/shift display:
const unsigned char LCD_MCSD = (1 << 4);
// direction of shift (right if set):
const unsigned char LCD_MCSD_RL = (1 << 2);
// turn on display shift:
const unsigned char LCD_MCSD_SC = (1 << 3);

// set interface length:
const unsigned char LCD_SETIFLEN = (1 << 5);
// set character font 5x10 (1) or 5x7 (0)
const unsigned char LCD_SETIFLEN_F = (1 << 2);
// set # of display lines 1 if 0, 2 if 1:
const unsigned char LCD_SETIFLEN_N = (1 << 3);
// set interface length 8 bits if 1, 4 bits if 0
const unsigned char LCD_SETIFLEN_DL = (1 << 4);

// move cursor into CGRAM:
const unsigned char LCD_MOVERAM = (1 << 6);

// Move cursor to display:
const unsigned char LCD_MOVEDISPLAY = (1 << 7);


#define LCD_E  6
//sbit LCD_RW = P0^7;
#define LCD_RS 7
sbit BUSYY = P2^7;

/*
 * Write a command to the LCD.
 */
void wrt_cmd(unsigned char val)
{
	busy();
	LCD_PORT=val;
	clrbitp(P4,7,ACTIVO_ALTO); //rs=0;
	clrbitp(P7,6,ACTIVO_ALTO);//rw=0;
	setbitp(P4,6,ACTIVO_ALTO);//en=1;
	clrbitp(P4,6,ACTIVO_ALTO);//en=0;
	busy();
	busy();
	busy();
	busy();
	busy();
}

void Clear_LCD(void){
	busy();
	busy();
	busy();
	busy();
	wrt_cmd(LCD_CLEAR);
	busy();
	busy();
	busy();
	busy();
	busy();
	busy();
	busy();
	busy();
	busy();
	busy();
	busy();
	busy();
}

void wrt_data(unsigned char ch)
{
	busy();
	LCD_PORT = ch;
	setbitp(P4,7,ACTIVO_ALTO);//rs=1;
	clrbitp(P7,6,ACTIVO_ALTO);//rw=0;
	setbitp(P4,6,ACTIVO_ALTO);//en=1;
	clrbitp(P4,6,ACTIVO_ALTO);//en=0;
}

void busy()
{
	unsigned char i,j;
	for(i=0;i<50;i++)        //A simple loop for delay
		for(j=0;j<255;j++);
}

void lcd_init(void)
{
	wrt_cmd(0X38);
	clrbitp(P4,7,ACTIVO_ALTO);//rs=0;
	clrbitp(P7,6,ACTIVO_ALTO);//rw=0;
	setbitp(P4,6,ACTIVO_ALTO);//en=1;
	clrbitp(P4,6,ACTIVO_ALTO);//en=0;
	busy();
	busy();
	busy();
	busy();
	wrt_cmd(0X0C);
	clrbitp(P4,7,ACTIVO_ALTO);//rs=0;
	clrbitp(P7,6,ACTIVO_ALTO);//rw=0;
	setbitp(P4,6,ACTIVO_ALTO);//en=1;
	clrbitp(P4,6,ACTIVO_ALTO);//en=0;
	busy();
	busy();
	busy();
	busy();
	wrt_cmd(0X01);
	clrbitp(P4,7,ACTIVO_ALTO);//rs=0;
	clrbitp(P7,6,ACTIVO_ALTO);//rw=0;
	setbitp(P4,6,ACTIVO_ALTO);//en=1;
	clrbitp(P4,6,ACTIVO_ALTO);//en=0;
	busy();
	busy();
	busy();
	busy();
	wrt_cmd(0X06);
	clrbitp(P4,7,ACTIVO_ALTO);//rs=0;
	clrbitp(P7,6,ACTIVO_ALTO);//rw=0;
	setbitp(P4,6,ACTIVO_ALTO);//en=1;
	clrbitp(P4,6,ACTIVO_ALTO);//en=0;
	busy();
	busy();
	busy();
	busy();
}

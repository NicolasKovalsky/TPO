#include "Headers/TPO_Serie.h"


xdata unsigned char BufferTx[TX_BUFFERSIZE];
xdata unsigned char BufferRx[RX_BUFFERSIZE];
xdata unsigned char indiceRx_in = 0,indiceRx_out = 0;
xdata unsigned char indiceTx_in = 0,indiceTx_out = 0;
xdata unsigned char bufferTx_full = 0, bufferTx_empty = 0, bufferRx_full = 0, bufferRx_empty = 0;

unsigned char dataready=0;
unsigned char f_startTx = 0;

unsigned char PushTx(unsigned char dato)
{
	if(bufferTx_full)
		return 0;	//Buffer lleno
	BufferTx[indiceTx_in] = dato;
	indiceTx_in++;
	if(indiceTx_in == TX_BUFFERSIZE)
		indiceTx_in = 0;
	if(indiceTx_in == indiceTx_out)
		bufferTx_full = 1;
	bufferTx_empty = 0;
	if(!f_startTx)		//si no esta transmitiendo ya, empiezo a transmitir
	{
		f_startTx = 1;
		StartTx();
	}
	return 1;		//elemento agregado a la cola de Tx
}

unsigned char PopTx(unsigned char *dato)
{
	if(bufferTx_empty)
		return 0;	//Buffer vacio
	*dato = BufferTx[indiceTx_out];
	indiceTx_out++;
	if(indiceTx_out == TX_BUFFERSIZE)
		indiceTx_out = 0;
	if(indiceTx_out == indiceTx_in)
		bufferTx_empty = 1;
	return 1;		//elemento sacado de la cola de Rx
}

unsigned char PushRx(unsigned char dato)
{
	if(bufferRx_full)
		return 0;	//Buffer lleno
	BufferRx[indiceRx_in] = dato;
	indiceRx_in++;
	if(indiceRx_in == RX_BUFFERSIZE)
		indiceRx_in = 0;
	if(indiceRx_in == indiceRx_out)
		bufferRx_full = 1;
	bufferRx_empty = 0;
	dataready = 1;	//hay datos por leer
	return 1;		//elemento agregado a la cola de Rx
}

unsigned char PopRx(unsigned char *dato)
{
	if(bufferRx_empty)
		return 0;	//Buffer vacio
	*dato = BufferRx[indiceRx_out];
	indiceRx_out++;
	if(indiceRx_out == RX_BUFFERSIZE)
		indiceRx_out = 0;
	if(indiceRx_out == indiceRx_in)
	{
		bufferRx_empty = 1;
		dataready = 0;	//no hay datos por leer
	}
	return 1;		//elemento sacado de la cola de Rx
}
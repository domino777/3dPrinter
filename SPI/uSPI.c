/*
 * uSPI.c
 *
 * Created: 28/09/2013 16:26:53
 *  Author: winShit
 */ 

#include <asf.h>
#include "uSPI.h";

void initSPI()
{
	PORTC_DIR = 0xB0;			// set SS - CLK - MOSI as output
	PR.PRPC		&= ~PR_SPI_bm;	//	enabling periferial clk
	SPIC_CTRL = 0b01010011;		//	START SPI - CLK2X off | SPI enable | DORD - msb 1st | MASTER true | MODE 0x00 | PRESCALER clk/16
	SPIC_STATUS = 0x00;
}

void highSpeedSPI()
{
	SPIC_CTRL = 0b11010000;		// PRESCALER clk/4
}

unsigned int sendSPI (unsigned char *data)
{
	SPIC_DATA = data;
	while ( !(SPIC_STATUS & 0x80) );
	return SPIC_DATA;
}

unsigned int receiveSPI()
{
	unsigned int data;
	SPIC_DATA = 0xFF;
	while ( !(SPIC_STATUS & 0x80) );
	return SPIC_DATA;
}

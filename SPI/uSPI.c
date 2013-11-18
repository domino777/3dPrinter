/*
 *	uSPI.c
 *
 *  "Copyright 2013 Mauro Ghedin"
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  or any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *
 *       @author         : Mauro Ghedin
 *       @contact        : domyno88 at gmail dot com
 *       @version        : 0.1
 *
 */
 
#include <avr/io.h>
#include "uSPI.h"

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

/*
 *	uBorad.h
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
 
#define LCD_BCKLGHT_PIN_bm		0x10

#define CCP_UNLOCK_bm		0xD8
#define CCP_UNLOCKED_bm		0x01

#ifndef BOARD_H_
#define BOARD_H_

#include <avr/io.h>

void board_clearing()
{
	
// All ports are cleared
	PORTA_OUT	= 0x00;		
	PORTB_OUT	= 0x00;
	PORTC_OUT	= 0x00;
	PORTD_OUT	= 0x00;
	PORTE_OUT	= 0x00;	
	PORTF_OUT	= 0x00;
	PORTR_OUT	= 0x00;
	
//All direction are set like input
	PORTA_DIR	= 0x00;
	PORTB_DIR	= 0x00;
	PORTC_DIR	= 0x00;
	PORTD_DIR	= 0x00;
	PORTE_DIR	= 0x00|LCD_BCKLGHT_PIN_bm;
	PORTF_DIR	= 0x00;
	PORTR_DIR	= 0x00;
}


void cpu_reset()
{
	CCP			= 0x9D;						//Unlock Restricted register
	RST_CTRL	= 0x01;									//Board reset
	while(CCP & 0x02);						//Wait re-locking restricted register
	while((RST_CTRL&0x01));							//Wait for board reset
}

#endif /* BOARD_H_ */

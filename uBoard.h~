/*
 * board.h
 *
 * Created: 29/10/2012 20:30:35
 *  Author: domyno
 */ 

#define LCD_BCKLGHT_PIN_bm		0x10

#define CCP_UNLOCK_bm		0xD8
#define CCP_UNLOCKED_bm		0x01

#ifndef BOARD_H_
#define BOARD_H_


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
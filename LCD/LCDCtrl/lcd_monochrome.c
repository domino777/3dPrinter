/*
 * lcd_monochrome.c
 *
 * Created: 28/09/2013 16:38:09
 *  Author: winShit
 */ 

#include "lcd_monochrome.h"
#include <avr/delay.h>
#include <avr/io.h>
//#include <asf.h>

#define false	0
#define true	1
void lcd_usart_spi_port_init()
{
	
	// TXD pin port initialization
	PORTD_OUT		|= LCD_TXD_PIN_bm;  // TXD pin set 1
	PORTD_DIR		|= LCD_TXD_PIN_bm;	// TXD pin is set like output
	// CS pin port initialization
	PORTF_OUT		|= LCD_CS_PIN_bm;	// CS  pin set 1
	PORTF_DIR		|= LCD_CS_PIN_bm;	// CS  pin set like output
	// A0 pin port initialization
	PORTD_OUT		|= LCD_A0_PIN_bm;;	// A0  pin set 1
	PORTD_DIR		|= LCD_A0_PIN_bm;	// A0  pin set like output
	// Hardware display reset pin port initialization
	PORTA_OUT		|= LCD_RESET_PIN_bm; // LCD reset disabled
	PORTA_DIR		|= LCD_RESET_PIN_bm; // LCD rest pin port set like output
	
	// ENABLING USART PORT CLK GENERATION
	PR.PRPD		&= ~PR_USART0_bm;
	
	// CLK port pin declaration and inverted logic
	PORTD_PIN1CTRL	|=	PORT_INVEN_bm;	//INVEN pin - CLK pin set inverted
	PORTD_OUT		|=	LCD_SCK_PIN_bm;	// CLK pin set 1
	PORTD_DIR		|=	LCD_SCK_PIN_bm;	// CLK pin set like output
	
	// USART module is set for SPI communication and for send LSB fisrt
	USARTD0_CTRLC	= USART_CMODE_gm|USART_LSB_FISRT_bm;

	// Boud rate set to 2Mbps
	USARTD0_BAUDCTRLB	= 0x00;
	USARTD0_BAUDCTRLA	= 0x00;

	// TX enable
	USARTD0_CTRLB		= USART_TXEN_bm | 0x04;
}

void lcd_send_cmd(char _data)
{
	PORTF_OUT	&= ~LCD_CS_PIN_bm;						//CS Selected
	PORTD_OUT	&= ~LCD_A0_PIN_bm;						//A0 command transmit selection

	while((USARTD0_STATUS&USART_DREIF_bm) == false);	//Wait for data write enable
	USARTD0_DATA = _data;
	
	while((USARTD0_STATUS&USART_TXCIF_bm) == false);	//Wait for data write completed
	USARTD0_STATUS	|= USART_TXCIF_bm;					//Clearing TX done flag
	PORTF_OUT		|=  LCD_CS_PIN_bm;						//CS De-Selected
}

void lcd_send_data(char _data)
{
	PORTF_OUT	&= ~LCD_CS_PIN_bm;						//CS Selected
	PORTD_OUT	|= LCD_A0_PIN_bm;						//A0 data transmit selection

	while((USARTD0_STATUS&USART_DREIF_bm) == false);	//Wait for data write enable
	USARTD0_DATA = _data;
	
	while((USARTD0_STATUS&USART_TXCIF_bm) == false);	//Wait for data write completed
	USARTD0_STATUS	|= USART_TXCIF_bm;					//Clearing TX done flag
	PORTF_OUT		|=  LCD_CS_PIN_bm;					//CS De-Selected
}


void lcd_hard_rest()
{
	PORTA_OUT	&= ~LCD_RESET_PIN_bm;	//LCD hard reset selected
	_delay_ms(100);
	PORTA_OUT	|=  LCD_RESET_PIN_bm;	//LCD hard reset disabled
	_delay_ms(100);
}

void lcd_init()
{
	lcd_send_cmd(ST7565R_CMD_ADC_NORMAL);					//ADC select - RAM address SEG - Normal
	lcd_send_cmd(ST7565R_CMD_DISPLAY_NORMAL);
	lcd_send_cmd(ST7565R_CMD_REVERSE_SCAN_DIRECTION);		//Common output - Normal direction
	lcd_send_cmd(ST7565R_CMD_LCD_BIAS_1_DIV_6_DUTY33);		//LCD bias set to 1/7 --- (0xA3 is for 1/9)
	lcd_send_cmd(ST7565R_CMD_POWER_CTRL_ALL_ON);			//Power control -- all ON
	lcd_send_cmd(ST7565R_CMD_BOOSTER_RATIO_SET);
	lcd_send_cmd(ST7565R_CMD_BOOSTER_RATIO_2X_3X_4X);
	lcd_send_cmd(ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_1);		//Resistor ratio set to 3
	lcd_send_cmd(ST7565R_CMD_ELECTRONIC_VOLUME_MODE_SET);	//Electronic volume set EN
	lcd_send_cmd(ST7565R_DISPLAY_CONTRAST_MIN);				//Electronic volume set to 2F
	lcd_send_cmd(ST7565R_CMD_DISPLAY_ON);					//Display ON
	
	
}

void lcd_select_column(char _page)
{
	lcd_send_cmd(ST7565R_CMD_COLUMN_ADDRESS_SET_MSB| (_page >> 4));
	lcd_send_cmd(ST7565R_CMD_COLUMN_ADDRESS_SET_LSB| (0x0F & _page));
}

void lcd_select_page(char _page)
{
	lcd_send_cmd(ST7565R_CMD_PAGE_ADDRESS_SET|_page);
}

void lcd_cleaning()
{
	for (int i = 0; i < 4; i++)
	{
		lcd_select_page(i);
		for (int y = 0; y < 128; y ++)
		{
			lcd_select_column(y);
			lcd_send_data(0x00);
		}
	}
}

void lcd_back_light(char flag)
{
	if (flag)
	PORTE_OUT |= LCD_BCKLGHT_PIN_bm;	//LCD Back light ON
	else
	PORTE_OUT &= ~LCD_BCKLGHT_PIN_bm;	//LCD Back light OFF
}

/*
 * lcd_monochrome.h
 *
 * Created: 29/10/2012 20:37:25
 *  Author: domyno
 */ 

#ifndef LCD_MONOCHROME_H_
#define LCD_MONOCHROME_H_

#define LCD_TXD_PIN_bm			0x08
#define LCD_CS_PIN_bm			0x08
#define LCD_A0_PIN_bm			0x01
#define LCD_RESET_PIN_bm		0x08
#define LCD_SCK_PIN_bm			0x02
#define LCD_BCKLGHT_PIN_bm		0x10

#define ST7565R_CMD_ADC_NORMAL                     0xA0
#define ST7565R_CMD_DISPLAY_NORMAL                 0xA6
#define ST7565R_CMD_REVERSE_SCAN_DIRECTION         0xC8
#define ST7565R_CMD_LCD_BIAS_1_DIV_6_DUTY33        0xA2
#define ST7565R_CMD_POWER_CTRL_ALL_ON              0x2F
#define ST7565R_CMD_BOOSTER_RATIO_SET              0xF8
#define ST7565R_CMD_BOOSTER_RATIO_2X_3X_4X         0x00
#define ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_1       0x21
#define ST7565R_CMD_ELECTRONIC_VOLUME_MODE_SET     0x81
#define ST7565R_DISPLAY_CONTRAST_MIN			   0x1E
#define ST7565R_CMD_DISPLAY_ON                     0xAF
#define ST7565R_CMD_DISPLAY_ALL_POINTS_ON          0xA5
#define ST7565R_CMD_RESET						   0xE2
#define ST7565R_DISPLAY_CONTRAST_MAX			   0x28
#define ST7565R_CMD_DISPLAY_ALL_POINTS_OFF		   0xA4
#define ST7565R_CMD_PAGE_ADDRESS_SET			   0xB0
#define ST7565R_CMD_COLUMN_ADDRESS_SET_MSB	       0x10
#define ST7565R_CMD_COLUMN_ADDRESS_SET_LSB         0x00


#define USART_LSB_FISRT_bm		0x02
#define PORT_INVEN_bm			0x40

#include <asf.h>

void lcd_usart_spi_port_init();
void lcd_send_cmd(Byte _data);
void lcd_send_data(Byte _data);
void lcd_hard_rest();
void lcd_init();
void lcd_select_column(Byte _page);
void lcd_select_page(Byte _page);
void lcd_cleaning();
void lcd_back_light(Bool flag);

#endif /* LCD_MONOCHROME_H_ */
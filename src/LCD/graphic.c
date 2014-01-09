/*
 *	graphic.c
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
#include "graphic.h"
#include "LCDCtrl/lcd_monochrome.h"

#include "general_bmp.h"

#include <avr/io.h>
#include <avr/delay.h>

void write_txt(char *_text, int _x_pos, int _y_pos, char invert)
{
	int _char_width	= 6;
	int _char_dec	= 0;
	int i = 0;
	lcd_select_page(_y_pos);
	lcd_select_column(_x_pos * _char_width);
	do
	{
		_char_dec = (*_text - 32) * 6;
		for(int _b_ch = 0; _b_ch < _char_width; _b_ch++)
		{
			char data	= glyph_8x6[_char_dec + _b_ch];
			if (invert)
				 data	= data ^ 0xFF;
			lcd_send_data(data);
		}
		i++;
	} while ((*(++_text) != 0x00 ) && i < 21);
}

void write_txt_append(char *_text, int _y_pos)
{
	int _char_width	= 6;
	int _char_dec	= 0;
	
	lcd_select_page(_y_pos);

	do
	{
		_char_dec = (*_text - 32) * 6;
		for(int _b_ch = 0; _b_ch < _char_width; _b_ch++)
		{
			lcd_send_data(glyph_8x6[_char_dec + _b_ch]);
		}
	} while ((*(++_text)));
	
}
void write_txt_fs(char *_text)
{
	int _char_width = 25;
	int _char_star_pointer =  0;
	int page		= 0;
	int	coll		= 0;
	
	lcd_select_column(0);
	
	do
	{
		_char_star_pointer = (*_text - 48) * _char_width * 4;
		page =	0;
		lcd_select_page(0);
		for(int _b = 0; _b < (_char_width * 4); _b++)
		{
			if(_b == (_char_width * (page + 1)))
			{
				page++;
				lcd_select_column(coll);
				lcd_select_page(page);
			}
			lcd_send_data(glyph_32x25[_b + _char_star_pointer]);
		}

		coll += _char_width;
	} while (*(++_text));
}

void write_waste(int _text, int _x_pos, int _y_pos)
{
	lcd_select_page(_y_pos);
	lcd_select_column(_x_pos);
	lcd_send_data(_text);
}

void clear_line(int _x_pos, int _y_pos)
{
	lcd_select_column(_x_pos);
	lcd_select_page(_y_pos);
	for (int _pos = _x_pos; _pos < 128; _pos++)
	lcd_send_data(0x00);
}

void write_logo_fs(char *_bmp)
{
	int page = 0;
	lcd_select_column(0);
	lcd_select_page(page);
	for(int _b = 0; _b < 512; _b++)
	{
		if(_b == 128 || _b == 256 || _b == 384)
		{
			page++;
			lcd_select_column(0);
			lcd_select_page(page);
		}
		lcd_send_data(_bmp[_b]);
	}
}


void write_animation_bmp(char *_bmp, int _bmp_h, int _bmp_w, int _x_pos, int _y_pos, int _frame_no, int _frame_dly)
{
	int _bmp_page = _bmp_h/8;								// LCD Maximum Row for bmp
	
	for (int _frame_p = 0; _frame_p < _frame_no; _frame_p++)	// Frame selection
	{
		for (int _y_bmp = 0; _y_bmp < _bmp_page; _y_bmp++)		// Row selection
		{
			lcd_select_page(_y_bmp);
			lcd_select_column(_x_pos);
			for(int _x_bmp = 0; _x_bmp < _bmp_w; _x_bmp++)		// column selection
			{
				lcd_send_data(_bmp[_x_bmp + (_y_bmp * _bmp_w) + (_frame_p * _bmp_page * _bmp_h)]);
			}
		}
		_delay_ms(200);
	}
	
}

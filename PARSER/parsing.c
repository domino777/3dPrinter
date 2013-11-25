/*
 *	parsing.c
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

#include "parsing.h"

#define NULL	0
#define true	1
#define false	0
void char8_to_string(unsigned int _value, char *_str)
{
	char	_f_digit	= false;
	char	_char_p		= 0;
	unsigned int		_div		= 10000;
	unsigned int		_value_aux	= 0;
	unsigned int		_q_result	= 0;
	
	_value_aux	=	_value;
	
	do
	{
		_q_result	= _value_aux / _div;
		if(_q_result >= 1 || _f_digit || _div == 1)
		{
			_value_aux		= _value_aux - (_q_result * _div);
			_f_digit	=	true;
			_str[_char_p]	=	_q_result + 0x30;
			_char_p++;
		}
		_div = _div / 10;
	} while (_div > 0);
	_str[_char_p] = 0x00;
}

void long_to_string(unsigned long _value, char *_str)
{
	char	_f_digit	= false;
	char	_char_p		= 0;
	unsigned long		_div		= 10000000000;
	unsigned long		_value_aux	= 0;
	unsigned long		_q_result	= 0;
	
	_value_aux	=	_value;
	
	if ( _value != 0 )
		do
		{
			_q_result	= (unsigned long)( _value_aux / _div );
			if(_q_result >= 1 || _f_digit || _div == 1)
			{
				_value_aux		= _value_aux - (_q_result * _div);
				_f_digit	=	true;
				_str[_char_p]	=	(char)( _q_result + 0x30 );
				_char_p++;
			}
			_div = _div / 10;
		} while (_div > 0);
	else
		_str[0]	= 0x30;
		
	_str[_char_p + 1]	=	0x00;
}

void float_to_string(float _value, char *_str)
{
	char	_f_digit	= false;
	char	_char_p		= 0;
	float		_div		= 1000000;
	float		_value_aux	= 0;
	float		_q_result	= 0;
	
	_value_aux	=	_value;
	
	do
	{
		_q_result	= _value_aux / _div;
		if(_q_result >= 1 || _f_digit || _div == 1)
		{
			_value_aux		= _value_aux - (_q_result * _div);
			_f_digit	=	true;
			_str[_char_p]	=	_q_result + 0x30;
			_str[_char_p + 1]	=	0x00;
			_char_p++;
		}
		_div = _div / 10;
	} while (_div > 0);
}

int string_to_int(char *str)
{
	int valOut = 0;
	int invert = 0;
	for( int i = 0; str[i] != NULL; i++) {
		if ( str[i] == 0x2D ) 
			invert = 1;
		else {
			valOut	*= 10;
			valOut	+= ( str[i] - 48 );		//	convert ascii to numeric value
		}		
	}	
	
	valOut = invert == 0 ? valOut : ( valOut ^ 0xFFFF ) + 1;
	return valOut;
}

long string_to_long(char *str)
{
	long valOut = 0;
	int invert = 0;
	for( int i = 0; str[i] != NULL; i++) {
		if ( str[i] == 0x2D )
		invert = 1;
		else {
			valOut	*= 10;
			valOut	+= ( str[i] - 48 );		//	convert ascii to numeric value
		}
	}
	
	valOut = invert == 0 ? valOut : ( valOut ^ 0xFFFFFFFF ) + 1;
	return valOut;
}

float string_to_float(char *str) {
	float valOut = 0.0;
	float invert = 1.0;
	int pDec = 0;
	
	int i = 0;
	for( i = 0; str[i] != NULL; i++) {
		if ( str[i] == '-' )
			invert = -1.0;
		else if ( str[i] == '.' || str[i] == ',')
			pDec = i;
		else {
			valOut	*= 10.0;
			valOut	= valOut + ((float)( str[i] - 48 ));		//	convert ascii to numeric value
		}
	}
	
	float pDecPos = 1.0;
	for( int j = 0; j < ( i - pDec - 1) && pDec != 0; j++ )
		pDecPos	*=	10.0;
	
	return ( valOut	/ pDecPos * invert );
}

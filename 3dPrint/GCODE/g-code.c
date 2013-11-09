/*
 *  g-code.c
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
 *
 *
 *		G-CODE PARSER HEADER FILE
 *
 */ 

#include "g-code.h"
#include "PARSER/parsing.h"
#include "STRING/string_hdl.h"
#include "LCD/graphic.h"

#define ASCII_RANGE	( ( str[i] >= 48 && str[i] <= 57 ) || ( str[i] >= 65 && str[i] <= 90 ) || ( str[i] >= 97 && str[i] <= 122 ) || str[i] == 32 || str[i] == 44 || str[i] == 46 || str[i] == 45 )

GCODE_PARSED gCode_parsing(char* str) {
	
	char strVal[6] = {0, 0};
		
	GCODE_PARSED gParsed;
	gParsed.cmdType		=	NULL;	//	initialized to 0
	gParsed.valX		=	NULL_f;
	gParsed.valY		=	NULL_f;
	gParsed.valZ		=	NULL_f;
	gParsed.valE		=	NULL_f;
	gParsed.valF		=	NULL_f;
	
	int xtraPar = 0;
	
	for ( int i = 0; str[i] != NULL && ASCII_RANGE; i++) {
		switch( str[i] ) {
			
			case 'M':
			case 'G':
				strVal[0] = 0x00;
				gParsed.cmdType	=	str[i];
				i++;			
				for( i = i; str[i] != ' ' && str[i] != NULL && ASCII_RANGE; i++)
					charToStrConcat( strVal, str[i] );
				gParsed.cmdVal = string_to_int( strVal );
			break;
			
			case 'X':
				strVal[0] = 0x00;
				i++;
				for( i = i; str[i] != ' ' && str[i] != NULL && ASCII_RANGE; i++)
					charToStrConcat( strVal, str[i] );
				gParsed.valX = string_to_float ( strVal );
			break;
			
			case 'Y':
				strVal[0] = 0x00;
				i++;
				for( i = i; str[i] != ' ' && str[i] != NULL && ASCII_RANGE; i++)
					charToStrConcat( strVal, str[i] );
				gParsed.valY = string_to_float ( strVal );
			break;
			
			case 'Z':
				strVal[0] = 0x00;
				i++;
				for( i = i; str[i] != ' ' && str[i] != NULL && ASCII_RANGE; i++)
					charToStrConcat( strVal, str[i] );
				gParsed.valZ = string_to_float ( strVal );
			break;
			
			case 'E':
				strVal[0] = 0x00;
				i++;
				for( i = i; str[i] != ' ' && str[i] != NULL && ASCII_RANGE; i++)
					charToStrConcat( strVal, str[i] );
				gParsed.valE = string_to_float ( strVal );
			break;

			case 'F':
				strVal[0] = 0x00;
				i++;
				for( i = i; str[i] != ' ' && str[i] != NULL && ASCII_RANGE; i++)
					charToStrConcat( strVal, str[i] );
				gParsed.valF = string_to_float ( strVal );
			break;

			case 'P':
			case 'T':
			case 'R':
				strVal[0] = 0x00;
				gParsed.cmdExtr[xtraPar] = str[i];
				i++;
				for( i = i; str[i] != ' ' && str[i] != NULL && ASCII_RANGE; i++)
					charToStrConcat( strVal, str[i] );
				gParsed.valExtr[xtraPar] = string_to_float( strVal );
				xtraPar++;
				if (xtraPar > 4) { return gParsed; }
			break;
		}
	}
	return gParsed;
}
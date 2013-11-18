/*
 *	string_hdl.c
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

#define NULL 0

void NULL_char(char *_str, int _len)
{
	for (int i = 0; i < _len; i++)
	_str[i]		= NULL;
}

void string_builder(char *_str_in, char *_str_out)
{
	while(*(_str_out++));
	*(--_str_out);
	do
	{
		*_str_out	= *_str_in;
		*(++_str_out);
	} while (*(++_str_in));
}

int stringcmp(char *str1, char *str2)
{
	while ( *(++str1) && *(++str2))
		if (*str1 != *str2 )
			return 1;
			
	if ( ( *str1 == NULL && *str2 != NULL ) || ( *str1 != NULL && *str2 == NULL ) )
		return 1;
		
	return 0;
}

void stringConcat(char *str1, char *str2)
{
	int i = 0, j;
	
	while(str1[i] != NULL)
		i++;
	
	for ( j = i; str2[j - i] != NULL; j++){
		str1[j] = str2[j - i];
		str1[j + 1] = 0x00;
	}	
}

void charToStrConcat(char *str1, char char1)
{
	int i = 0;
	
	while(str1[i] != NULL)
		i++;
	
	str1[i] = char1;
	str1[i + 1] = 0x00;
}

/*
 * string_hdl.c
 *
 * Created: 29/09/2013 15:49:40
 *  Author: winShit
 */ 

#include <asf.h>

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
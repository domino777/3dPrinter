/*
 * parsing.h
 *
 * Created: 02/11/2012 12:46:05
 *  Author: domyno
 */ 


#ifndef PARSING_H_
#define PARSING_H_

//#include <asf.h>

void	byte8_to_string(unsigned int _value, char *_str);
void	long_to_string (unsigned long _value, char *str);
void	float_to_string (float _value, char *str);
long	string_to_long(char *str);
int		string_to_int(char *str);
float	string_to_float(char *str);

#endif /* PARSING_H_ */
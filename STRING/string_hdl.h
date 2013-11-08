/*
 * string_hdl.h
 *
 * Created: 20/11/2012 19:00:30
 *  Author: domyno
 */ 


#ifndef STRING_HDL_H_
#define STRING_HDL_H_

void	NULL_char(char *_str, int _len);
void	string_builder(char *_str_in, char *_str_out);
int		stringcmp( char *str1, char *str2);
void	stringConcat( char *str1, char *str2);
void   charToStrConcat( char *str1, char char1);

#endif /* STRING_HDL_H_ */
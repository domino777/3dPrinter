/*
 * graphic.h
 *
 * Created: 30/10/2012 21:02:11
 *  Author: domyno
 */ 


#ifndef GRAPHIC_H_
#define GRAPHIC_H_

void write_txt(char *_text, int _x_pos, int _y_pos, char invert);
void write_txt_append(char *_text, int _y_pos);
void write_txt_fs(char *_text);
void write_waste(int _text, int _x_pos, int _y_pos);
void clear_line(int _x_pos, int _y_pos);
void write_logo_fs(char *_bmp);
void write_animation_bmp(char *_bmp, int _bmp_h, int _bmp_w, int _x_pos, int _y_pos, int _frame_no, int _frame_dly);

#endif /* GRAPHIC_H_ */
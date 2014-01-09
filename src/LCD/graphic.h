/*
 *	graphic.h
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

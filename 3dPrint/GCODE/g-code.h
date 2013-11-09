/*
 *  g-code.h
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

typedef struct {
	char cmdType;				//	G-Code command type - char is stored - "M" or "G" cmd
	int cmdVal;
	float valX;
	float valY;
	float valZ;
	float valF;
	float valE;
	char cmdExtr[4];			//	Extra argument of cmdType, like G4 P2000 - 'P' is the extra argument
	float valExtr[4];			//	Extra argument of cmdTyoe, like G4 P2000 - '2000' is the value
} GCODE_PARSED;

#define NULL_f		0.0
#define NULL		0

GCODE_PARSED	gCode_parsing(char* str);

#ifndef G-CODE_H_
#define G-CODE_H_





#endif /* G-CODE_H_ */
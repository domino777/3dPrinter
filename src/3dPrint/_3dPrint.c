	/*
 *	3dPrint.c
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

#include "_3dPrint.h"
#include "3dPrint/GCODE/g-code.h"
#include "3dPrint/AXYZE/axesCtrl.h"

//	DEFINE SECTION

#define	_RETRACT_EXTR_MM	10.0					//	Length of plastic wire to retract from extruder

char printFromString( char* strCmd ) {

//	Parsing the string command to G-Code var type
//	strCmd must be G-Code string

	GCODE_PARSED gCodeVar;
	AXES		 spAxes;

//	Parsing G-Code		
	gCodeVar	= gCode_parsing( strCmd );	
	
//	Saving parameter to local temp structured variables
	spAxes.axeX	=	gCodeVar.valX;
	spAxes.axeY	=	gCodeVar.valY;
	spAxes.axeZ	=	gCodeVar.valZ;
	spAxes.axeE	=	gCodeVar.valE;

	
	if ( gCodeVar.cmdType == 'G' )					//	Action G command
		if ( gCodeVar.cmdVal == 1 )					//	Movement command
			axesWorkStart( &absAxeAxtualPos, &spAxes, &gCodeVar.valF, ( gCodeVar.valE == 0.0 ) );
		
	if ( gCodeVar.cmdType == 'M' ) {				//	Action M command
		if ( gCodeVar.cmdVal == 103 )				//	Retract extruder code
			extruderFwdRev ( 1, _RETRACT_EXTR_MM );
		else if ( gCodeVar.cmdVal == 101 )			//	Restore retracted wire
			extruderFwdRev ( 0, _RETRACT_EXTR_MM );
	}

	return 0x01;									//	command string completed
}

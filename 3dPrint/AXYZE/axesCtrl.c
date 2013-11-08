/*
 *  axesCtrl.h
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

#include "axesCtrl.h"
#include "tmr.h"
#include <math.h>
#include <asf.h>

unsigned long	axeXcounter = 0, axeYcounter = 0, axeZcounter = 0, axeEcounter = 0;

char axesWorkStart( AXES* absAXES, AXES* spAXES, float* exeSpeed, float* prevExeSpeed, char holdExtruder ) {
	//	Total length of movement
	//	            _________________________________
	//	lenght =  \/( (x1 - x2 )^2 + ( y1 - y2 )^2 );
	
	float deltaX, deltaY, deltaZ, deltaE;
	deltaX	=	absAXES->axeX - spAXES->axeX;
	deltaY	=	absAXES->axeY - spAXES->axeY;
	deltaZ	=	absAXES->axeZ - spAXES->axeZ;
	deltaE	=	absAXES->axeE - spAXES->axeE;
	
	float printLen		= (float)sqrt( ( deltaX * deltaX ) + ( deltaY * deltaY ) );		//	computing total print length
	float printTime		= printLen / *exeSpeed;										//	print time at given speed
	
	//	calculating axes speed interpolation mm/min / 60 -- mm/s
	float axeXspeed		= fabs(deltaX) / printTime / 60.0;
	float axeYspeed		= fabs(deltaY) / printTime / 60.0;
	float axeZspeed		= fabs(deltaZ) / printTime / 60.0;
	float axeEspeed		= fabs(deltaE) / printTime / 60.0;
	
	//	convert mm/s to step/s
	axeXspeed			= axeXspeed / STEP_MM;
	axeYspeed			= axeXspeed / STEP_MM;
	axeZspeed			= axeXspeed / STEP_MM;
	axeEspeed			= axeXspeed / STEP_MM;
	
	unsigned long axeXms = 0, axeYms = 0, axeZms = 0, axeEms = 0;
	//	computing t per step ( * 1000 000 covert s to us )
	if ( axeXspeed > 0.0 )
		axeXms		= (long)(( 1000000 / axeXspeed ) );
	if ( axeYspeed > 0.0 )
		axeYms		= (long)(( 1.0 / axeYspeed * 1000.0 ) + 0.5 );
	if ( axeZspeed > 0.0 )
		axeZms		= (long)(( 1.0 / axeZspeed * 1000.0 ) + 0.5 );
	if ( axeEspeed > 0.0 )
		axeEms		= (long)(( 1.0 / axeEspeed * 1000.0 ) + 0.5 );
		
	//	hold extruder
	if ( holdExtruder )
		axeEspeed	=	0.0;
	
	char axeXend = 0;
	char axeYend = 0;
	char axeZend = 0;
	char axeEend = 0;
	
	//	Timer configuration
	TCC0_CTRLA		= 0x02;											//	Set clock prescaled CLK/2
	TCC0_CTRLB		= 0x00;
	TCC0_CTRLFSET	= 0x00;											//	up counter
	unsigned int timerTotal	= 0;
	
	//	Start movement of the 3 axes
	while ( !axeEend || !axeYend || !axeZend || !axeEend ) {
		
		TCC0_CTRLFSET = 0x08;										//	Reset timer counter
		unsigned int cycle = (unsigned int)( timerTotal * 0.0625 );		//	Computing cpuCycle
	
		axeXend		= axeXCtr( absAXES, &spAXES->axeX, &axeXms, &cycle );
		
		timerTotal = TCC0_CNT;
	}	
		
	return 0;
}


char axeXCtr( AXES* absAXES, float* spAXE, unsigned long* msStep, unsigned int* cpuCycle ){
	
	int step[4] = {0x00, 0x80, 0xC0, 0x40};
	
	if ( *cpuCycle == 0 )
		return 0;
		
	char tmrEnd = delay_us( 1, msStep, &axeXcounter, *cpuCycle );
	if ( !tmrEnd )
		return 0;
		
//	Run on FWD ( incremental movement )
	if ( absAXES->axeX  < *spAXE - TOLL_MM ) {
			axeXcStep++;
			absAXES->axeX	+=	STEP_MM;
			if ( axeXcStep > 4 )
				axeXcStep = 0;
		}
//	Run on REV ( decremental movement )
	else if ( absAXES->axeX  > *spAXE + TOLL_MM ) {
		axeXcStep--;
		absAXES->axeX	-=	STEP_MM;
		if ( axeXcStep < 0 )
			axeXcStep = 0;
	}
	
	PORTA_OUT |= step[axeXcStep];

//	Reset counter
	axeXcounter = 0;
	
//	Movement completed
	if ( absAXES->axeX > *spAXE - TOLL_MM && absAXES->axeX < *spAXE + TOLL_MM )
		return 1;
}

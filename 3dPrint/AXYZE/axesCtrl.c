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
 *       @version        : 0.2
 *       
 */ 

#include "axesCtrl.h"
#include "tmr.h"
#include <math.h>
#include <avr/io.h>
#include <avr/delay.h>

//	GLOBAL VARIBLES 
unsigned long	axeXcounter = 0, axeYcounter = 0, axeZcounter = 0, axeEcounter = 0;

int stepX[4]	= {0x00, 0x40, 0xC0, 0x80};
int stepY[4]	= {0x00, 0x10, 0x30, 0x20};
int stepZ[4]	= {0x00, 0x80, 0xC0, 0x40};
int stepE[4]	= {0x00, 0x80, 0xC0, 0x40};

char axesWorkStart( AXES* absAXES, AXES* spAXES, float* exeSpeed, char holdExtruder ) {
	//	Total length of movement
	//	            _________________________________
	//	lenght =  \/( (x1 - x2 )^2 + ( y1 - y2 )^2 );
	
	float deltaX, deltaY, deltaZ, deltaE;
	deltaX	=	absAXES->axeX - spAXES->axeX;
	deltaY	=	absAXES->axeY - spAXES->axeY;
	deltaZ	=	absAXES->axeZ - spAXES->axeZ;
	//deltaE	=	absAXES->axeE - spAXES->axeE;
	
	float printLen		= (float)sqrt( ( deltaX * deltaX ) + ( deltaY * deltaY ) );					//	computing total print length
	spAXES->axeE		= printLen;																	//	print SP of extruded is the total print length of interpolated axes
	float printTime		= printLen / *exeSpeed;														//	print time at given speed	
	
	//	calculating axes speed interpolation mm/min / 60 -- mm/s
	float axeXspeed		= fabs(deltaX) / printTime / 60.0;
	float axeYspeed		= fabs(deltaY) / printTime / 60.0;
	float axeZspeed		= fabs(deltaZ) / printTime / 60.0;
	float axeEspeed		= *exeSpeed / 60.0;

	//	convert mm/s to step/s
	axeXspeed			= axeXspeed / STEP_MM;
	axeYspeed			= axeYspeed / STEP_MM;
	axeZspeed			= axeZspeed / STEP_MM;
	axeEspeed			= axeEspeed / STEP_MM;
	
	unsigned long axeXms = 0.0, axeYms = 0.0, axeZms = 0.0, axeEms = 0.0;
	//	computing t per step ( * 1000 000 covert s to us )
	if ( axeXspeed > 0.0 )
		axeXms		= (long)(( 1000000 / axeXspeed ) );
	if ( axeYspeed > 0.0 )
		axeYms		= (long)(( 1000000 / axeYspeed ) );
	if ( axeZspeed > 0.0 )
		axeZms		= (long)(( 1000000 / axeZspeed ) );
	if ( axeEspeed > 0.0 )
		axeEms		= (long)(( 1000000 / axeEspeed ) );
	
	//	absolute extruder axex will be always cleared
	absAXES->axeE	= 0.0;																			//	extruder will print from zero length to total print length of interpolated axes sp
	
	//	hold extruder
	if ( holdExtruder ) {
		spAXES->axeE	= 0.0;
		axeEspeed		= 0;
	}
	
	char axeXend = 0;
	char axeYend = 0;
	char axeZend = 0;
	char axeEend = 0;
	
	axeXcounter = 0;
	axeYcounter = 0;
	axeZcounter = 0;
		
	//	Timer configuration
	TCC0_CTRLA		= 0x02;																			//	Set clock prescaled CLK/2
	TCC0_CTRLB		= 0x00;	
	TCC0_CTRLFSET	= 0x00;																			//	up counter
	unsigned int timerTotal	= 0;
	
	//	Start movement of the 3 axes
	while ( axeXend == 0 || axeYend == 0 || axeZend == 0 /*|| !axeEend */) {
		
		TCC0_CTRLFSET = 0x08;																		//	Reset timer counter
		unsigned int cycle = (unsigned int)( timerTotal * 0.0625 );									//	Computing cpuCycle
	
		axeXend		= axeXCtr( absAXES, &spAXES->axeX, &axeXms, &cycle );
		axeYend		= axeYCtr( absAXES, &spAXES->axeY, &axeYms, &cycle );
		axeZend		= axeZCtr( absAXES, &spAXES->axeZ, &axeYms, &cycle );
		axeEend		= axeZCtr( absAXES, &spAXES->axeE, &axeEms, &cycle );
		
		timerTotal = TCC0_CNT;																		//	Save timer counter
	}	
		
	return 0;
}


char axeXCtr( AXES* absAXES, float* spAXE, unsigned long* msStep, unsigned int* cpuCycle ){
	
	if ( *cpuCycle == 0 )
		return 0;
		
//	Movement completed
	if ( ( absAXES->axeX - TOLL_MM ) <= *spAXE  && ( absAXES->axeX + TOLL_MM ) >= *spAXE )
		return 1;
		
	char tmrEnd = delay_us( 1, *msStep, &axeXcounter, *cpuCycle );
	if ( tmrEnd == 0 )
		return 0;
		
//	Run on FWD ( incremental movement )
	if ( absAXES->axeX  < ( *spAXE - TOLL_MM ) ) {
			axeXcStep++;
			absAXES->axeX	+=	STEP_MM;
			if ( axeXcStep > 3 )
				axeXcStep = 0;
		}
//	Run on REV ( decremental movement )
	else if ( absAXES->axeX  > ( *spAXE + TOLL_MM ) ) {
		axeXcStep--;
		absAXES->axeX	-=	STEP_MM;
		if ( axeXcStep < 0 )
			axeXcStep = 3;
	}
	
	PORTA_OUT = stepX[axeXcStep] | ( 0x3F & PORTA_OUT );

//	Reset counter
	axeXcounter = 0;
		
	return 0;
}

char axeYCtr( AXES* absAXES, float* spAXE, unsigned long* msStep, unsigned int* cpuCycle ){
	
	if ( *cpuCycle == 0 )
		return 0;
		
//	Movement completed
	if ( ( absAXES->axeY - TOLL_MM ) <= *spAXE  && ( absAXES->axeY + TOLL_MM ) >= *spAXE ) 		
		return 1;
		
	char tmrEnd = delay_us( 1, *msStep, &axeYcounter, *cpuCycle );
	if ( tmrEnd == 0 )
		return 0;
		
//	Run on FWD ( incremental movement )
	if ( absAXES->axeY  < ( *spAXE - TOLL_MM ) ) {
			axeYcStep++;
			absAXES->axeY	+=	STEP_MM;
			if ( axeYcStep > 3 )
				axeYcStep = 0;
		}
//	Run on REV ( decremental movement )
	else if ( absAXES->axeY  > ( *spAXE + TOLL_MM ) ) {
		axeYcStep--;
		absAXES->axeY	-=	STEP_MM;
		if ( axeYcStep < 0 )
			axeYcStep = 3;
	}
	
	PORTA_OUT = stepY[axeYcStep] | ( 0xCF & PORTA_OUT );

//	Reset counter
	axeYcounter = 0;
		
	return 0;
}

char axeZCtr( AXES* absAXES, float* spAXE, unsigned long* msStep, unsigned int* cpuCycle ){
	
	if ( *cpuCycle == 0 )
		return 0;
		
//	Movement completed
	if ( ( absAXES->axeZ - TOLL_MM ) <= *spAXE  && ( absAXES->axeZ + TOLL_MM ) >= *spAXE ) 		
		return 1;
		
	char tmrEnd = delay_us( 1, *msStep, &axeZcounter, *cpuCycle );
	if ( tmrEnd == 0 )
		return 0;
		
//	Run on FWD ( incremental movement )
	if ( absAXES->axeZ  < ( *spAXE - TOLL_MM ) ) {
			axeZcStep++;
			absAXES->axeZ	+=	STEP_MM;
			if ( axeZcStep > 3 )
				axeZcStep = 0;
		}
//	Run on REV ( decremental movement )
	else if ( absAXES->axeZ  > ( *spAXE + TOLL_MM ) ) {
		axeZcStep--;
		absAXES->axeZ	-=	STEP_MM;
		if ( axeZcStep < 0 )
			axeZcStep = 3;
	}
	
	//PORTA_OUT = stepY[axeYcStep] | ( 0xCF & PORTA_OUT );

//	Reset counter
	axeZcounter = 0;
		
	return 0;
}

char axeECtr( AXES* absAXES, float* spAXE, unsigned long* msStep, unsigned int* cpuCycle ){
	
	if ( *cpuCycle == 0 )
		return 0;
		
//	Movement completed
	if ( ( absAXES->axeE - TOLL_MM ) <= *spAXE  && ( absAXES->axeE + TOLL_MM ) >= *spAXE ) 		
		return 1;
		
	char tmrEnd = delay_us( 1, *msStep, &axeEcounter, *cpuCycle );
	if ( tmrEnd == 0 )
		return 0;
		
//	Run on FWD ( incremental movement )
	if ( absAXES->axeE  < ( *spAXE - TOLL_MM ) ) {
			axeEcStep++;
			absAXES->axeE	+=	STEP_MM;
			if ( axeEcStep > 3 )
				axeEcStep = 0;
		}
//	Run on REV ( decremental movement )
	else if ( absAXES->axeE  > ( *spAXE + TOLL_MM ) ) {
		axeEcStep--;
		absAXES->axeE	-=	STEP_MM;
		if ( axeEcStep < 0 )
			axeEcStep = 3;
	}
	
	//PORTA_OUT = stepY[axeYcStep] | ( 0xCF & PORTA_OUT );

//	Reset counter
	axeEcounter = 0;
		
	return 0;
}

char extruderFwdRev ( unsigned char fwdRev, float mmFwdRev ) {
	
	float	backPos	= 0.0;
	
//	Run extruder on forward
	if ( !fwdRev ) 
		while ( backPos < mmFwdRev - TOLL_MM ) {
			axeEcStep++;
			if ( axeEcStep > 3 )
				axeEcStep = 0;
			
			PORTA_OUT	= stepE[axeEcStep] | ( 0xCF & PORTA_OUT );
			_delay_ms(5);
		}
//	Run extruder on reverse
	else
		while ( backPos < mmFwdRev - TOLL_MM ) {
			axeEcStep--;
			if ( axeEcStep < 0 )
				axeEcStep = 3;
			
			PORTA_OUT	= stepE[axeEcStep] | ( 0xCF & PORTA_OUT );
			_delay_ms(5);
		}
		
	return 0;
}

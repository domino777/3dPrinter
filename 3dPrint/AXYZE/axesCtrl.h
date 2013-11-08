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


#ifndef AXESCTRL_H_
#define AXESCTRL_H_

//#include "tmr.h"

#define STEP_MM		0.2 // 1 step = 0.2 mm 
#define TOLL_MM		0.5

typedef struct {
	float	axeX;
	float	axeY;
	float	axeZ;
	float	axeE;
	} AXES;

extern volatile AXES absAxeAxtualPos;
extern volatile int axeXcStep;
extern volatile int axeYcStep;
extern volatile int axeZcStep;
extern volatile int axeEcStep;

char extrudeStart ( AXES* absAXES, float* spPos, float* exeSpeed, float* prevExeSpeed );


/**********************************************************************************/
/*  axesWorkStart start axes movement										      */
/*  absAXES      -- absolute AXES position (deprecated, extern volatile to use)   */
/*	spAXES       -- set point position        									  */
/*	exeSpeed     -- movement speed, XYZE are interpolated for axes syn            */
/*  holdExtruder -- no movement for extruder/ extruder locked                     */
/**********************************************************************************/
char axesWorkStart ( AXES* absAXES, AXES* spAXES, float* exeSpeed, float* prevExeSpeed, char holdExtruder );

char axeXCtr ( AXES* absAXES, float* spAXE, unsigned long* msStep, unsigned int* cpuCycle );
char axeYCtr ( AXES* absAXES, float* spAXE, unsigned long* msStep, unsigned int* cpuCycle );
char axeZCtr ( AXES* absAXES, float* spAXE, unsigned long* msStep, unsigned int* cpuCycle );
char axeECtr ( AXES* absAXES, float* spAXE, unsigned long* msStep, unsigned int* cpuCycle );

#endif /* AXESCTRL_H_ */
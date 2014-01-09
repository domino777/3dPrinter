/*
 *	tmr.h
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

#ifndef TMR_H_
#define TMR_H_

#define CPU_CLOCK	32000000;

char delay_us(char EN, unsigned long dly, unsigned long *counter, unsigned int cpuCycle) 
{
	if (EN) {
		*counter += cpuCycle;
		if (*counter >= dly)
		{
			*counter = dly;
			return 1;
		}
	}		
	else
		*counter = 0;

		return 0;
}
/*
void sleep_ms( unsigned int *delay ){
	
	unsigned long us_dly_step	= (unsigned double)( ( 1 / CPU_CLOCK ) * 1000000000 );
	unsigned long counter		= 0;
		
	for( counter = 0; counter < (unsigned long)( *delay * 1000 ); counter += us_dly_step );
			
}*/

#endif /* TMR_H_ */

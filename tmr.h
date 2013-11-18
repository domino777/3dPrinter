/*
 * tmr.h
 *
 * Created: 23/09/2013 19:47:15
 *  Author: winShit
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
/*
 * tmr.h
 *
 * Created: 23/09/2013 19:47:15
 *  Author: winShit
 */ 


#ifndef TMR_H_
#define TMR_H_


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



#endif /* TMR_H_ */
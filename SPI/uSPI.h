/*
 * uSPI.h
 *
 * Created: 26/09/2013 19:03:05
 *  Author: winShit
 */ 


#ifndef USPI_H_
#define USPI_H_

void initSPI();
unsigned int sendSPI (unsigned char *data);
unsigned int receiveSPI();
void highSpeedSPI();


#endif /* USPI_H_ */
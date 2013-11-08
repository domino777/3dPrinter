/*
 * SDMMC.c
 *
 * Created: 28/09/2013 16:20:56
 *  Author: winShit
 */ 

#include "PARSER/parsing.h"
#include "LCD/graphic.h"

#include "SDMMC.h"
#include "SPI/uSPI.h"
#include <asf.h>

#include "STRING/string_hdl.h"

unsigned long ff;
int sendCmdSD(unsigned char cmd, long arg, unsigned char CRCval)
{
	int count = 0;
	unsigned int response;
	
	Byte byteArray[4];
	 byteArray[0] = (int)((arg >> 24) & 0xFF) ;
	 byteArray[1] = (int)((arg >> 16) & 0xFF) ;
	 byteArray[2] = (int)((arg >> 8) & 0XFF);
	 byteArray[3] = (int)((arg & 0XFF));
	
	SD_CS_OF;
		
	sendSPI(cmd | 0x40);
	sendSPI(byteArray[0]);
	sendSPI(byteArray[1]);
	sendSPI(byteArray[2]);
	sendSPI(byteArray[3]);
	sendSPI(CRCval);
	
	while ((response = receiveSPI()) == 0xFF)
		if (count++ > 0xFE)  
			return 0xFF; 			// wait 256 times

	SD_CS_ON;
	receiveSPI();

	return response;
}

int initSD()
{
	unsigned int response;
	int count = 0;					// Card selected	
	do{
		for (int i = 0; i < 20; i++)
			sendSPI(0xFF);
			
		response = sendCmdSD(SD_RESET, 0, 0x95);
		
		if (count++ > 0xFE) 
			return 0x01;		// Error code - SD Reset ERROR
	}		
	while (response != 0x01);
	
	SD_CS_ON;
	sendSPI(0xFF);
	
//	Check version of the card - must be V2.0 else chard will be reject
	if ( vCheckSD() == 0xFF)
		return 0xFF;
// vCheckSD();
	
	count = 0;
	do 
	{
		sendCmdSD(APP_CMD, 0x00, 0x65);
		response = sendCmdSD(ASD_INIT_REQ, 0x50000000, 0x17);
		
		if (count++ > 0xFFE) 
			return 0x02;		//	Error code - SD init ERROR
	} while (response);

	sendCmdSD(CRC_ON_OFF, OFF, 0x91);	
	sendCmdSD(SET_BLOCKLEN, BLOCK_SIZE, 0x13);
	
	highSpeedSPI();
	
	return 0x00;
}

/*-----------------------------------------------------------------------------------
	SD card version check - return 0 if OK
-----------------------------------------------------------------------------------*/
int vCheckSD()
{
	int response;
	unsigned char data[3];
	
	response = sendCmdSD(SD_V_CHECK, 0x1AA, 0x87);
	if (response = 0x01){
		SD_CS_OF
		for (int i = 0; i < 4; i++)
			data[i] = receiveSPI();
		SD_CS_ON
		receiveSPI();
	}		
	if ( data[1] != 0x01 || data[2] != 0xAA || response != 0x01)
		return 0xFF;
		
	return 0;
}

/************************************************************************/
/*                 Read SD Card 1KB block                               */
/************************************************************************/
int readBlockSD(unsigned long blkStart)
{
	int response;
	unsigned long count = 0;
	int blk_r_no = 0;
	
	do {
		response = sendCmdSD(READ_SINGLE_BLOCK, blkStart + blk_r_no, 0xFF);
		if (response != 0x00)
			return 0x01;
		
		SD_CS_OF
		
		count = 0;
		while(receiveSPI() != 0xFE)					// wait for data TOKEN
			if (count++ > 0xfffe) { SD_CS_ON; return 0x02; }
			
		for (unsigned int i = blk_r_no * 512; i < (blk_r_no + 1) * 512; i++){
			buffer[i] = receiveSPI();
		}	
	
		receiveSPI();		// CRC data wasted
		receiveSPI();		// CRC data wasted
	
		SD_CS_ON;
		
		receiveSPI();	
		receiveSPI();	
	
		blk_r_no++;
		
	} while ( blk_r_no < 2);
		
	return 0;
}


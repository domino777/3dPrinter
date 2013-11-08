/*
 * SDMMC.h
 *
 * Created: 26/09/2013 19:13:55
 *  Author: winShit
 */ 


#ifndef SDMMC_H_
#define SDMMC_H_

#define OFF					0
#define ON					1
#define CRC_ON_OFF			59
#define SET_BLOCKLEN 		16	
#define SD_RESET			0
#define SD_INIT_REQ			1
#define READ_SINGLE_BLOCK	17
#define SEND_CSD			9
#define APP_CMD				55
#define ASD_INIT_REQ		41
#define SD_V_CHECK			8

#define BLOCK_SIZE			512

#define SD_CS_ON PORTC_OUT |= 0x10;
#define SD_CS_OF PORTC_OUT &= ~0x10;

int sendCmdSD(unsigned char cmd, long int arg, unsigned char CRCval);
int initSD();
int readBlockSD(unsigned long blkStart);
int vCheckSD();

extern volatile unsigned char buffer[1024];

#endif /* SDMMC_H_ */
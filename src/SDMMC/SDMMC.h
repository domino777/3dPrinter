/*
 *	SDMMC.h
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

int sendCmdSD(unsigned char cmd, long int arg, unsigned char CRCval);
int initSD();
int readBlockSD(unsigned long blkStart);
int vCheckSD();

extern volatile unsigned char buffer[1024];

#endif /* SDMMC_H_ */

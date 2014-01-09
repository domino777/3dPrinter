/*
 *	main.c
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

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */

#define CPU_CLOCK	32000000;

//#include "asf.h"
#include <avr/io.h>
#include "uBoard.h"
#include "sys_clock.h"
#include "LCD/LCDCtrl/lcd_monochrome.h"
#include "LCD/graphic.h"
#include "PARSER/parsing.h";
#include "STRING/string_hdl.h"
#include "SPI/uSPI.h"
#include <avr/delay.h>
#include "EXT2/EXT2.h"
#include "SDMMC/SDMMC.h"
#include "domy_logos.h"
#include "3dPrint/_3dPrint.h"


#define true	1
#define false	0

//	GLOBAL ABSOLUTE VARIABLE

volatile unsigned char buffer[1024];		//	buffer used by SDMMC.h

volatile AXES absAxeAxtualPos;				//	absolute axes position - _3dPrint.h
volatile int axeXcStep;						//	actual index step motor - axe X - _3dPrint.h
volatile int axeYcStep;		
volatile int axeZcStep;						
volatile int axeEcStep;


void gCodeFile( DIR* file );
void readFile( DIR* file );
char pulse( char pb, char* vmem);
	
char mSw2		= 0;
char mSw1		= 0;
	
int main()
{
	
//	SYSTEM INITIALIZATION
	board_clearing();
	cpu_reset();
	
//	MCU CLOCK INITIALIZATION
	sys_clock();
	
//	LCD INITIALIZATION
	lcd_usart_spi_port_init();
	lcd_init();
	lcd_cleaning();												//	screen cleaning
	lcd_back_light(true);										//	Switch on back light

	//write_logo_fs(load_logo);
	_delay_ms(1000);
	
	PORTA_DIR |= 0xF0;
//	SD CARD INITIALIZATION
	initSPI();													//	Init SPI interface
	
	while( 1 ) {												//	Try_Re-try SD card init
		int retVal		= initSD();
		lcd_cleaning();
		while( retVal ) {
			write_txt("SD card failure", 0, 0, 0);
			write_txt("Press SW1 for retry", 0, 1, 0);
			if (!(PORTF_IN & 0x02)) {
				lcd_cleaning();
				retVal	= initSD();
			}
		}		

		write_txt("EXT2 fs mounting", 0, 1, 0);
		retVal		= EXT_mount();								//	Try to mount SD card file system
		lcd_cleaning();
		if ( retVal != 0 ) {
			if ( retVal == 0x01 )
				write_txt("Not MBR disk", 0, 0, 0);
			else if ( retVal == 0x02 )
				write_txt("Block must be = 1kB", 0, 0, 0);
				
			write_txt("Put a valid SD card", 0, 1, 0);
			write_txt("Press SW1 for retry", 0, 2, 0);
			while (PORTF_IN & 0x02);
		} 
		else
			break;	
	}
	write_txt("EXT2 mounted", 0, 0, 0);
	_delay_ms(1000);
	lcd_cleaning();
	write_txt("Reading /", 0, 0, 0);

//	Variable declaration
	DIR dirContent[4];	
	DIR_HNDL dirHNDL;
	
	DIR selDir;
	
//	Variable cleaning
	selDir.inode_id					= 0;
	selDir.inode_type				= 0;
	dirHNDL.dir_entry_byte			= 0;
	dirHNDL.last_inode_block_index	= 0;
	
	char pVal		= 0;
	int entrySel	= 0;
	
	int	i 			= 0;
	//	getting the first 4 dir entry
	while (i < 4 && (dirContent[i] = EXT_ls(selDir, &dirHNDL)).inode_id != 0)
		i++;
		
	lcd_cleaning();

/*
 *	MAIN CYCLE SYSTEM 
 *	
 *	reading dir, print dir entry, file selection, 3D print, read file 
 */
	while( 1 ){
		
//	Write entry on display
		for ( int p = 0; p < 4 && dirContent[p].inode_id != 0; p++) {
			write_txt(dirContent[p].inode_name, 0, p, entrySel == p);
			if ( dirContent[p].inode_type == EXT2_FT_DIR )
				write_txt("d", 20, p, 0);															//	d flag - directory
			else if ( dirContent[p].inode_type == EXT2_FT_REG_FILE )								//	f flag - regular file
				write_txt("f", 20, p, 0);
		}		
		
//	SW1 rise edge detect
		if ( pulse ( !(PORTF_IN & 0x02), &mSw1 ) )
			entrySel++;
			
//	Diplay row highlight and gettting next 4 dir's entries
		if ( entrySel > 3 || entrySel > i - 1) {		
			i = 0;
			while ( i < 4 && (dirContent[i] = EXT_ls(selDir, &dirHNDL)).inode_id != 0)
				i++;
			entrySel = 0;
			lcd_cleaning();
		}		
		
//	dir handler clearing when EOF is reached AND SW1 rise edge detect
		if ( dirContent[entrySel].inode_id == 0 || ( pVal = pulse( !(PORTF_IN & 0x04), &mSw2 )) ) {		
			if ( dirContent[entrySel].inode_type == EXT2_FT_DIR && pVal ) 
				selDir	= dirContent[entrySel];			
					
			else if ( dirContent[entrySel].inode_type == EXT2_FT_REG_FILE && pVal )
				gCodeFile( &dirContent[entrySel] );													//	Call function from main.c for read or print a gCode file - file extensione isn't checked
				
			dirHNDL.dir_entry_byte			= 0;
			dirHNDL.last_inode_block_index	= 0;
			entrySel						= 4;
		}

		/*
		//	SW1 rise edge detect
		if ( !(PORTF_IN & 0x04) ) {
			dirHNDL.dir_entry_byte			= 0;
			dirHNDL.last_inode_block_index	= 0;	
		}*/
	}
	/*
	int i = 0;
	int datas = 0;
	int counter = 0;
	char bit;;
	int crc_val;
	int retVal = 0;
	//crc_val = getCRC(values);
	
	//char *cc;	
	initSPI();
	_delay_ms(1000);
	retVal = initSD();
	TCC0_CTRLA = 0x02;
	TCC0_CTRLB = 0x00;
	TCC0_CTRLFSET = 0x00;			//	up counter

	EXT_mount();
	
	DIR myDir;
	DIR returnDir[10];
	DIR_HNDL myDirHndl;
	
	myDir.inode_id = 0;
	myDirHndl.last_inode_block_index = 0;
	myDirHndl.dir_entry_byte = 0;
	//returnDir.inode_type = 0;

	int lock = 0;
	int entryNo = 0;
/*
	int value;
	value =  string_to_int("-1024");
	char cc[5];
	byte8_to_string(value, cc);
	write_txt(cc, 0, 0, 0);
*/	/*
	int no = 0;
	do {
		returnDir[ no ] = EXT_ls(myDir, &myDirHndl);
		no++;
	} while ( returnDir[ no - 1].inode_id != 0)	;

	while (1) {
		while ( PORTF_IN & 0x04 ) {		//SW2
			if ( !(PORTF_IN & 0x02) && lock == 0 ) { //SW1
				entryNo++;
				if (entryNo > no - 1)
					entryNo = 0;
				lock = 1;
				lcd_cleaning();
			}
			if ( (PORTF_IN & 0x02) && lock == 1)
				lock = 0;
				
			for ( int i = 4 * ( entryNo / 4 ); i < 4 * ( entryNo / 4 + 1) && returnDir[i].inode_id != 0; i++ ) {
				write_txt(returnDir[i].inode_name, 0, i - ( 4 * ( entryNo / 4 )) , ( entryNo % 4 == i - ( 4 * ( entryNo / 4 )) ) );
			}			
		}
		lcd_cleaning();
		if ( returnDir[entryNo].inode_type == EXT2_FT_DIR ){
			no = 0;
			myDirHndl.dir_entry_byte = 0;
			myDirHndl.last_inode_block_index = 0;
			myDir.inode_id = returnDir[entryNo].inode_id;
			myDir.inode_type = returnDir[entryNo].inode_type;
			do {
				returnDir[ no ] = EXT_ls(myDir, &myDirHndl);
				no++;
			} while ( returnDir[ no - 1].inode_id != 0)	;
			entryNo = 0;
		}		
		else if ( returnDir[entryNo].inode_type == EXT2_FT_REG_FILE ) {
			write_txt("file:", 0, 0, 0);
			FILE_HNDL fill;
			fill.inode_id = returnDir[entryNo].inode_id;
			fill.last_byte = 0;
			char line[100];
			char xt = 0;
			GCODE_PARSED data;
			unsigned int tm = 0;
			char yy[10];
			do {
					TCC0_CTRLFSET = 0x0C;
					xt = EXT_readfile(&fill, line);
					data = gCode_parsing( line );
					if ( data.cmdType == 'G' ) {
						clear_line(0, 2);
						write_txt(line, 0, 2, 0);
						clear_line(0, 3);
						unsigned int cycle = (unsigned int)(tm * 0.0625);
						byte8_to_string(cycle, yy);
						write_txt(yy, 0, 3, 0);
					}		
					tm = TCC0_CNT;			
			}			
			while ( xt != EOF );
			char tt[2];
			byte8_to_string(data.cmdType, tt);	
			write_txt(tt, 0, 3, 0);
			while ( !( PORTF_IN & 0x04 ));
		}
	}		
	/*
	DIR_HNDL dd;
	dd.last_inode_block_index = 0;
	dd.dir_entry_byte	= 0x00;
	
	FILE_HNDL filll;
	filll.inode_id	=	returnDir.inode_id;
	filll.last_byte	= 0;
	int lineno = 0;
	int pbAux = 0;
	while(1) {
		
	/*	if ( !(PORTF_IN & 0x02) && ( pbAux == 0 ) )  {
			pbAux = 1; 
			for (int i = 0; i < 4; i++) {  */
		/*		char *line = EXT_readfile(&filll);
				if ( line != EOF ) {
					clear_line(0, i);
					write_txt(line, 0, 0, 0);
				}
				else
					goto out;
		//	}
			lineno += 4;
			char ll[7];
			NULL_char(ll, 7);
			long_to_string(filll.last_byte, ll);
			write_txt(ll, 0, 3, 0);
		//	NULL_char(ll, 7);
		//	long_to_string(lineno, ll);
		//	write_txt(ll, 0, 2, 0);
		//}
		/*
		if ( PORTF_IN & 0x02 )
			pbAux = 0;*/
	/*}
	out:
	//readOCR();
	/*_delay_ms(1000);
	byte8_to_string(retVal, cc);
	write_txt(cc,0, 0);

				retVal = readBlockSD(0);
				byte8_to_string(retVal, cc);
				//clear_line(0,1);
				write_txt(cc,0, 1);
				for (int i = 0; i < 512; i++)
				{
				
					_delay_ms(200);
					clear_line(0,2);
					byte8_to_string(buffer[i], cc);
					write_txt(cc,0, 2);
				}
		*/				
	while(true);
	/*TCC0_CTRLA = 0x02;				//	Set clock prescaled CLK/2
	TCC0_CTRLB = 0x00;
	TCC0_CTRLFSET = 0x00;			//	up counter
	unsigned int cnt;
	char cc[5];
	int tt;
	unsigned long int counterOn;
	unsigned long int counterOff;
	int i=0;
	char dnOn = false;
	char dnOff = false;
	int step[4] = {0x00, 0x80, 0xC0, 0x40};
	char app = false;
	PORTA_DIR |= 0xC0 | LCD_RESET_PIN_bm;
	int steps = 0;
	while(true){
		TCC0_CTRLFSET = 0x08;		//reset counter
		//PORTA_OUT	= 0x08;
		if (tt > 0)
		{
			int cycle = tt * 0.0625;
			dnOn = delay_us(true,  4000	, &counterOn, cycle);
			dnOff = delay_us(dnOn, 4000, &counterOff, cycle);
			
			if (dnOn && steps < 500)
			{
				PORTA_OUT = step[i] | LCD_RESET_PIN_bm;
			}				
			else
			{
				//write_txt("2", 0, 1);	
				
			}			
				
			byte8_to_string(cycle, cc);
			write_txt(cc, 0, 0);
			
			if (dnOff && !app  ) {
						
						if (PORTE_IN & 0x20)
						{
							i++;
							steps++;
							if (i > 3)
							i = 0;
							app = true;
						}
						else
						{
							i--;
							steps--;
							if (i < 0)
							i = 3;
							app = true;
						}						
			}
			
			if (!dnOff) { app = false; }
				
			if (dnOff)
			{
				counterOn = 0;
			}
		}		
		tt = TCC0_CNT;
	}
	// Insert application code here, after the board has been initialized.
	
	*/
}


/*
 *	gCodeFile
 *	expect DIR type variable as argument
 * 
 * 	selection menu is show in lcd display
 * 	Read or 3DPrint
 */
void gCodeFile( DIR* file ) {
	char retVal;
	char line[128];
	FILE_HNDL	fHNDL;
	fHNDL.inode_id	=	file->inode_id;
	fHNDL.last_byte =	0;
	
	lcd_cleaning();
	while ( 1 ) {
		write_txt("What you wanna do?", 0, 0, 0);
		write_txt("SW1 - Read", 0, 1, 0);
		write_txt("SW2 - 3DPrint", 0, 2, 0);
		if ( pulse( !(PORTF_IN & 0x02) , &mSw1) ){
			readFile( &*file );									//	Call readFile function from main.c
			lcd_cleaning();
		}
		else if ( pulse( !(PORTF_IN & 0x04) , &mSw2) ) {
				retVal	= 0;
				while ( retVal != EOF ) {
					retVal = EXT_readfile( &fHNDL, &line );
					write_txt(&line, 0, 3, 0);
					printFromString(&line);
					write_txt(&line, 0, 2, 0);
				}
				write_txt("Fine stampa", 0, 3, 0);
		}		
	}
}

/*
 *	readFile
 *	expect DIR type variable as argument
 * 
 *	read the content of a given file
 */
 
void readFile ( DIR* file ) {
	char retVal;
	char line[128]; 
	
	FILE_HNDL	fHNDL;
	fHNDL.inode_id	=	file->inode_id;							//	Extract file's inide_id
	fHNDL.last_byte =	0;
	
	lcd_cleaning();
	write_txt("Use push button", 0, 0, 0);
	write_txt("SW1 for next page", 0, 1, 0);
	
	while ( 1 ){
		if ( pulse( !(PORTF_IN & 0x02) , &mSw1) ){
			lcd_cleaning();
			for ( int i = 0; i < 4 && retVal != EOF; i++ ) {
				retVal	= EXT_readfile( &fHNDL, &line);
				write_txt(line, 0, i, 0);
			}		
		}			
		if ( retVal == EOF )
			write_txt("## EndOfFile ##", 0, 3, 0);
			
		if ( pulse( !(PORTF_IN & 0x04 ) , &mSw2))			//	Exit from file when SW2 is pressed											
				break;
	}
}


/*
 *	pulse
 * 	pb		-- pushbutton status
 * 	vmem	-- pushbutton memory
 * 
 * 	pointer passed to pulse must be an unique variable for each push button and not cleared in the same loop call
 *	
 *	function return true when a rise edge of pb is detected and it stay true for one and only one cpu cylce
 * 
 */
 
char pulse( char pb, char* vmem) {
	_delay_ms(50);
	if ( pb && !*vmem ) {
		*vmem	= true;
		return true;
	}		
	if ( !pb && *vmem )
		*vmem	= false;
	return false;
}

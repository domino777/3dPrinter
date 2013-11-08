/*
 * sys_clock.h
 *
 * Created: 29/10/2012 19:22:45
 *  Author: domyno
 */ 


#define CCP_UNLOCK_bm		0xD8
#define CCP_UNLOCKED_bm		0x01

#ifndef SYS_CLOCK_H_
#define SYS_CLOCK_H_

void sys_clock()
{

	OSC_CTRL		= OSC_RC32MEN_bm;									//Internal 32MHz oscillator selected and external
	while(!(OSC_STATUS&OSC_RC32MRDY_bm));								//Wait for oscillators ready
	OSC_DFLLCTRL	= OSC_RC32MCREF_XOSC32K_gc|OSC_RC2MCREF_bm;			//Reference for oscillator is the external OSC crystal at 32KHz
	DFLLRC32M_CTRL  = 0x01;												//Auto calibration for 32MHz int osc is enable
	DFLLRC2M_CTRL	= 0x01;												//Auto calibration for 2MHz int osc is enable

	CCP			= CCP_UNLOCK_bm;						//Unlock Restricted register
	CLK_CTRL	= CLK_SCLKSEL_RC32M_gc;					//System clock is set to 32Mhz internal generator
	while(CCP & CCP_UNLOCKED_bm);						//Wait re-locking restricted register
	
	CCP			= CCP_UNLOCK_bm;						//Unlock Restricted register
	CLK_PSCTRL  = 0x00;									//No division for sys clock Clk2 - Clk4 - Clkper -- ClkPER run at 32MHz
	while(CCP & CCP_UNLOCKED_bm);						//Wait re-locking restricted register

	CCP			= CCP_UNLOCK_bm;						//Unlock Restricted register
	CLK_LOCK	= 0x01;									//System clock is locked - cannot be changed
	while(CCP & CCP_UNLOCKED_bm);						//Wait re-locking restricted register

	CLK_RTCCTRL = CLK_RTCSRC_TOSC_gc|CLK_RTCEN_bm;		//Select RTC to EXT32Khz Crystal and enabled for RTC
	CLK_USBCTRL = 0x00|CLK_USBSRC1_bm;					//Clock source for USB is Int32MHz osc
	
// All Clock signal are disable	
	PR.PRGEN	= 0xFF;	// STOP all periferial CLK
	PR.PRPA		= 0xFF;	// STOP port clk gen
	PR.PRPB		= 0xFF;	// STOP port clk gen
	PR.PRPD		= 0xFF;	// STOP port clk gen
	PR.PRPE		= 0xFF;	// STOP port clk gen
	PR.PRPF		= 0xFF;	// STOP port clk gen
	PR.PRPD		= 0xFF;	// STOP port clk gen
}

#endif /* SYS_CLOCK_H_ */
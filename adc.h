/*
 * adc.h
 *
 * Created: 02/11/2012 19:45:04
 *  Author: domyno
 */ 

#define SIGNED_MODE		0x10	//signe mode enable
#define CH_START		0x80	//Conversion start

#ifndef ADC_H_
#define ADC_H_

void adc_init_portA(Bool _reslution_12, Byte _prescaler, Bool _signed_mode)
{
	
// Enabling clock generator for ADC on portA	
	PR.PRPA &= ~PR_ADC_bm;
	
// ADC resolution selection
	if(_reslution_12)
		ADCA_CTRLB	=	0x00;						// Write 0 select 12bit resolution
	else
		ADCA_CTRLB	=	ADC_RESOLUTION_8BIT_gc;		// 8bit resolution
		
	if(_signed_mode)
		ADCA_CTRLB	|=	SIGNED_MODE;
	else
		ADCA_CTRLB	&=	~SIGNED_MODE;
		
// Reference to Vcc/1.6 also temperature reference is enabled		
	ADCA_REFCTRL	=	ADC_REFSEL_VCC_gc|ADC_TEMPREF_bm;
	
// Alla event are disabled		
	ADCA_EVCTRL		=	0x00;
	
// Prescaler division selection
	ADCA_PRESCALER	=	_prescaler;
	
//	Signature write form CPU signature for calibration
	ADCA_CAL		=	PRODSIGNATURES_ADCACAL0|(PRODSIGNATURES_ADCACAL1<<8);
	
// ADC enabling
	ADCA_CTRLA = ADC_ENABLE_bm;	
	
	
}

void adca_ch0_init(Byte _input_mode, Byte _adc_pin_pos_sel, Byte _adc_pin_neg_sel)
{
// input mode selection - INERNAL - SINGLEENDED	- (DIFF - DIFFWGAIN) only with signet in signe mode
//	No gain
	ADCA_CH0_CTRL	= _input_mode;
	
// mux control only for PIN selection
	ADCA_CH0_MUXCTRL = _adc_pin_pos_sel<<3|_adc_pin_neg_sel;

// Set interrupt falg for complete conversion	
	ADCA_CH0_INTCTRL = ADC_CH_INTMODE_COMPLETE_gc;
}

Byte adca_ch0_conv_start()
{
	ADCA_CH0_CTRL	|=	CH_START;
}

#endif /* ADC_H_ */
/*
 * ADC.h
 *
 * Created: 4/4/2021 5:29:32 PM
 *  Author: shady mamdouh
 */ 


#ifndef ADC_H_
#define ADC_H_




#define RESOLUTION_LEVELS 1024UL

// bits 
#define	ADMUX_REFS1 7
#define	ADMUX_REFS0 6
#define	ADMUX_ADLAR 5
#define	ADMUX_MUX4 4
#define	ADMUX_MUX3 3
#define	ADMUX_MUX2 2
#define	ADMUX_MUX1 1
#define	ADMUX_MUX0 0

#define ADCSRA_ADEN 7
#define ADCSRA_ADSC 6
#define ADCSRA_ADATE 5
#define ADCSRA_ADIF 4
#define ADCSRA_ADIE 3
#define ADCSRA_ADPS2 2
#define ADCSRA_ADPS1 1
#define ADCSRA_ADPS0 0

#define SFIOR_ADTS2 7
#define SFIOR_ADTS1 6
#define SFIOR_ADTS0 5

enum ADC_Trigger_src
{
	free_runnig,
	analog_comparator,
	external_interupt0,
	TIMER0_Compare_match,
	TIMER0_Over_Flow,
	TIMER_Compare_match_B,
	TIMER1_Over_Flow,
	TIMER1_Capture_event
	
	};
enum ADC_Vref_selector
{
	Aref_external,
	AVCC_with_extCapacitor,   // capacitor at AREF pin
	reserved,
	internal_with_extCapacitor // capacitor at AREF pin
	
	};
enum ADC_Channels   // S refers to single ended and D refers to differential and numbers refer to gain 
{
	S_ADC0,              // single ended modes
	S_ADC1,
	S_ADC2,
	S_ADC3,
	S_ADC4,
	S_ADC5,
	S_ADC6,
	S_ADC7,  
	D_ADC0_ADC0_10,     //differential modes with gain 
	D_ADC1_ADC0_10,
	D_ADC0_ADC0_200,
	D_ADC1_ADC0_200,
	D_ADC2_ADC2_10,
	D_ADC3_ADC2_10,
	D_ADC2_ADC2_200,
	D_ADC3_ADC2_200,
	D_ADC0_ADC1_1,    //differential modes with gain x1
	D_ADC1_ADC1_1,
	D_ADC2_ADC1_1,
	D_ADC3_ADC1_1,
	D_ADC4_ADC1_1,
	D_ADC5_ADC1_1,
	D_ADC6_ADC1_1,
	D_ADC7_ADC1_1,
	D_ADC0_ADC2_1,
	D_ADC1_ADC2_1,
	D_ADC2_ADC2_1,
	D_ADC3_ADC2_1,
	D_ADC4_ADC2_1,
	D_ADC5_ADC2_1,
	VBG,   //1.22V
	ZERO_GND
	
	};
enum ADC_Register_Shift  // the 10 bit converted data will be shifted left or right in 16 bit register
{
	right,    // default 
	lift
	};
enum ADC_Clock_selector  // prescale XTAL divided by
{
	clk_2,
	clk2_2,
	clk_4,
	clk_8,
	clk_16,
	clk_32,
	clk_64,
	clk_128
	};
enum ADC_Interrupt_Enable
{  
	 interrupt_disable,
	interrupt_enable
	};
enum ADC_autoTrigger_enable
{
	autoTrigger_Disable,
	autoTrigger_Enable
	};
typedef struct S_ADC_cofiguration
{
	enum ADC_Trigger_src Trigger_src;
	enum ADC_Vref_selector Vref_selector;
	enum ADC_Channels Channels;
	enum ADC_Register_Shift Register_Shift;
	enum ADC_Clock_selector Clock_selector;
	enum ADC_Interrupt_Enable Interrupt_Enable;
	enum ADC_autoTrigger_enable autoTrigger_enable;
	}S_ADC_cofiguration ;
	
	
S_ADC_cofiguration ADC_CONFIG_STRUCT;


/***************************APIs******************************/
void ADC_init(S_ADC_cofiguration ADC_config);	
void ADC_enable(void);
void ADC_disable(void);
void ADC_start_convertion(void);
void ADC_GetSingleSample(uint16_t *Sample);
/************************************************************/



#endif /* ADC_H_ */
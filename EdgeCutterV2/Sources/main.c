/* ###################################################################
 **     Filename    : main.c
 **     Project     : SonicScrewdriver
 **     Processor   : MKL02Z32VFM4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2015-12-04, 13:49, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "PTA.h"
#include "DACSEL.h"
#include "CLOCKINT.h"
#include "SW_MODE.h"
#include "LATCH.h"
#include "DATA.h"
#include "CLOCK.h"
#include "SW_TRIGGER.h"
#include "SW_SPEED.h"
#include "PTB.h"
#include "KSDK1.h"
#include "EE241.h"
#include "GI2C1.h"
#include "CI2C1.h"
#include "IntI2cLdd1.h"
#include "JACK_RETRIGGER.h"
#include "WAIT1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

#include <math.h>
#include <stdio.h>
#include "main.h"

volatile int measured = 0;

int adcchannels[ADC_Count];


#include "EdgeCutter2.h"
#define SKIPDAC
#include "../../EurorackShared/EurorackShared.c"

#include "../../EurorackShared/Math.c"
#include "../../libfixmath/libfixmath/fix16.c"
EdgeCutter2_Envelope Envelope;
EdgeCutter2_Settings Settings;
EdgeCutter2_Params Params;

static struct denoise_state_t speedsw_state = {0};
static struct denoise_state_t modesw_state = {0};
static struct denoise_state_t triggersw_state = {0};
static struct denoise_state_t retriggerjack_state = {0};

void UpdateButtons()
{
	denoise(JACK_RETRIGGER_GetVal(0), &retriggerjack_state);
	denoise(SW_TRIGGER_GetVal(0), &triggersw_state);
	denoise(SW_MODE_GetVal(0), &modesw_state);
	denoise(SW_SPEED_GetVal(0), &speedsw_state);

}
uint32_t t = 0;

//4096 = 2.048v
/*2.5 * (2.048 * INP)/4096
		(x * 4096)
		/ 2.5 * 2.048
		 = inp*/

#define VOLT(x) ((int)((4096.0 * (x)) / (2.5 * 2.048)))
#define NOTE(x) VOLT((x) / 12.0)

byte outleds[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0};
byte targetleds[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0};
//                    13                 5, 6, 7, 8, 9,10, 4, 3,2,1,0

//byte ledorder[13] = {19,18,17,16,15, 8,9, 10,11,12,13,14, 2};
unsigned char pwm = 3;
//int counter = 0;


#define SetIf(x){if (x) {DATA_SetVal(DATA_DeviceData);}else {DATA_ClrVal(DATA_DeviceData);}CLOCK_ClrVal(CLOCK_DeviceData); CLOCK_SetVal(CLOCK_DeviceData);};
#define SetNotIf(x){if (x) {DATA_ClrVal(DATA_DeviceData);}else {DATA_SetVal(DATA_DeviceData);}CLOCK_ClrVal(CLOCK_DeviceData); CLOCK_SetVal(CLOCK_DeviceData);};
void ShiftOut()
{
	//counter++;
	pwm += 9;




	LATCH_ClrVal(LATCH_DeviceData);


	SetIf(outleds[12] > pwm);
	SetIf(outleds[17] > pwm);

	SetIf(outleds[16] > pwm);
	SetIf(outleds[15] > pwm);
	SetIf(outleds[14] > pwm);

	SetIf(outleds[13] > pwm);

	SetIf(outleds[18] > pwm);


	SetIf(outleds[4] > pwm);
	SetIf(outleds[5] > pwm);
	SetIf(outleds[6] > pwm);
	SetIf(outleds[7] > pwm);
	SetIf(outleds[8] > pwm);
	SetIf(outleds[9] > pwm);
	SetIf(outleds[10] > pwm);
	SetIf(outleds[11] > pwm);



	SetNotIf(Envelope.Gates[GATE_DECAYEND]>0);
	SetNotIf(Envelope.Gates[GATE_RELEASESTART]>0);
	SetNotIf(Envelope.Gates[GATE_RELEASEEND]>0);

	SetIf(outleds[3] > pwm);
	SetIf(outleds[2] > pwm);
	SetIf(outleds[1] > pwm);
	SetIf(outleds[0] > pwm);
	SetNotIf(Envelope.Gates[GATE_ATTACKEND]>0);


	LATCH_SetVal(LATCH_DeviceData);//



}



int KnobOpt(int val)
{
	int r = 0;
	if (val > (65536*1)/5) r++;
	if (val > (65536*2)/5) r++;
	if (val > (65536*3)/5) r++;
	if (val > (65536*4)/5) r++;
	return 1 + 4 - r;
}


int tickssincecommit = 0;

// half-millisecond timer -> update each dacchannel in turn
int LinearOut = 0;
int CurvedOut = 0;

void DAC_DATA_SET() {GPIOA_PDOR |= (1<<7);};
void DAC_DATA_CLR() {GPIOA_PDOR &= ~(1<<7);};
void DAC_CLK_SET() {GPIOB_PDOR |= (1<<0);};
void DAC_CLK_CLR() {GPIOB_PDOR &= ~(1<<0);};
void DAC_INIT()
{
	PORTA_PCR7 = PORT_PCR_MUX(0x01);
	PORTB_PCR0 = PORT_PCR_MUX(0x01);

	GPIOA_PDDR |= (1 << 7);
	GPIOB_PDDR |= (1 << 0);

}
void DAC_Shift(byte b)
{
	for(byte i =0x80;i;i>>=1)
	{
		if ((b&i) == i) 	DAC_DATA_SET();else DAC_DATA_CLR();
		DAC_CLK_SET();DAC_CLK_CLR();
	}

}
void DACB_Write(int channel, int value)
{
	DACSEL_ClrVal(0); // SetVal done in interrupt handler
	const int shutdown1 = 0;
	const int gain1 = 0;
	const int shutdown2 = 0	;
	const int gain2 = 0;
	unsigned char coms[2];

	unsigned int command;
	if(channel == 1)
	{
		command = 0x0000;
		command |= shutdown1 ? 0x0000 : 0x1000;
		command |= gain1 ? 0x0000 : 0x2000;
		command |= (value & 0x0FFF);
		coms[0] =  command >> 8;
		coms[1] = command &0xff;

	}
	else
	{
		command = 0x8000;
		command |= shutdown2 ? 0x0000 : 0x1000;
		command |= gain2 ? 0x0000 : 0x2000;
		command |= (value & 0x0FFF);
		coms[0] =  command >> 8;
		coms[1] = command &0xff;


	}
	DAC_Shift(coms[0]);
	DAC_Shift(coms[1]);
	DACSEL_SetVal(0); // SetVal done in interrupt handler
	denoise(JACK_RETRIGGER_GetVal(0), &retriggerjack_state);

}
EdgeCutter2_Calibration EdgecutterCalibration;

int justretriggered = 0;
int buttonjustpressed  = 0;

void doTimer()
{
	UpdateButtons();
	tickssincecommit++;
	t++;
	switch(t%2)
	{
	case 0:
	{
		if (pressed(&retriggerjack_state))
		{
			justretriggered = 1;
			EdgeCutter2_Retrigger(&Envelope);
		}
		EdgeCutter2_GetEnv(&Envelope, &Params,&EdgecutterCalibration);
		LinearOut = Envelope.LinearOutput;
		DACB_Write(0, LinearOut);

		for(int i =0 ;i<13;i++)
		{

			targetleds[i] = Envelope.StateLeds[i];
			if (outleds[i] < targetleds[i]) outleds[i] = Envelope.StateLeds[i];;
		}
		for (int i = 0; i < 20; i++)
		{
			if (targetleds[i] > outleds[i])
			{
				outleds[i]++;
			}
			else
			{
				if (targetleds[i] < outleds[i])
				{
					outleds[i]--;
				}
			}
		}
	}
	break;
	case 1:
	{
		CurvedOut = Envelope.CurvedOutput;
		DACB_Write(1, CurvedOut);
	}

	break;
	}
	ShiftOut();
}

void SetModeLeds(int mode)
{
	switch(mode)
	{
	case 0: targetleds[15]=0; targetleds[14] = 0;targetleds[13] =255 ;break;
	case 1: targetleds[15]=0; targetleds[14] = 255;targetleds[13] =0 ;break;
	case 2: targetleds[15]=255; targetleds[14] = 0;targetleds[13] =0 ;break;
	}
}

enum
{
	SPEEDSWITCH_NORMAL,
	SPEEDSWITCH_GATEMODE,
	__SPEEDSWITCH_COUNT
};
int SpeedSwitchMode = SPEEDSWITCH_NORMAL;


void SetGateModeLeds(int gatemode)
{

	switch(gatemode)
	{
	case SPEEDSWITCH_NORMAL: targetleds[16]=255; targetleds[17] = 0;break;
	case SPEEDSWITCH_GATEMODE: targetleds[16]=0; targetleds[17] = 255;break;
	case -1:targetleds[16]=0;targetleds[17] = 0;break;
	}
}
void SetSpeedLeds(int speed)
{
	switch(speed)
	{
	case 1: targetleds[16]=255; targetleds[17] = 0;break;
	case 0: targetleds[16]=0; targetleds[17] = 255;break;
	case -1:targetleds[16]=0;targetleds[17] = 0;break;
	}
}

#define VERSIONBYTE 0x10
#define CALIBRATIONVERSIONBYTE 0x10
#define EEPROM_CALIBRATIONBASE 0x20

void SaveEeprom()
{
	EE24_WriteByte(0, VERSIONBYTE);
	int paramsize = sizeof(Params);
	EE24_WriteBlock(1, (byte *)&Params, paramsize);
}

void SaveCalibrationEeprom()
{
	int calibrationsize = sizeof(EdgecutterCalibration);
	EE24_WriteByte(EEPROM_CALIBRATIONBASE, CALIBRATIONVERSIONBYTE);
	EE24_WriteBlock(EEPROM_CALIBRATIONBASE + 1, (byte *)&EdgecutterCalibration, calibrationsize);
}

void LoadCalibrationEeprom()
{
	int Ver = EE24_ReadByte(EEPROM_CALIBRATIONBASE);
	if (Ver == CALIBRATIONVERSIONBYTE)
	{
		int paramsize = sizeof(EdgecutterCalibration);
		EE24_ReadBlock(EEPROM_CALIBRATIONBASE+1, (byte *)&EdgecutterCalibration, paramsize);
		unsigned char *b = (byte *)&EdgecutterCalibration;

	}
	else
	{
		EdgecutterCalibration.CalibCurved =114 ;
		EdgecutterCalibration.CalibNormal =134 ;
	//	SaveCalibrationEeprom();
	}
}

void LoadEeprom()
{
	byte Ver;
	Ver = EE24_ReadByte(0);
	if (Ver == VERSIONBYTE)
	{
		int paramsize = sizeof(Params);
		EE24_ReadBlock(1, (byte *)&Params, paramsize);
		EdgeCutter2_ValidateParams(&Params);
	}
	else
	{
		SaveEeprom();
	}
}

void SetupLeds()
{
	if (SpeedSwitchMode == SPEEDSWITCH_NORMAL) SetSpeedLeds(Params.speed);
	if (SpeedSwitchMode == SPEEDSWITCH_GATEMODE)
	{
		if (t%1000<400)
		{
			SetGateModeLeds(Params.GatedMode);
		}
		else
		{
			SetGateModeLeds(-1);
		}
	}
	SetModeLeds(Params.mode);
}

int buttonpressed = 0;

void EnvelopeTrigger(int sw)
{
	if (buttonpressed == 1) return;
	EdgeCutter2_Trigger(&Envelope, sw>0?0:1, &Params);
	if (sw==0) buttonjustpressed = 1;
}

uint16_t Adjust(uint16_t inp)
{
			if (inp > 0xc00)
			{
				uint32_t r = inp - (0xc00);
				r *= 0xffff;
				r /= (0xffff - (0xc00));
				return r;
			}
			else
			{
				return 0;
			}

}
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	DAC_INIT();
	EdgeCutter2_Init(&Envelope);

#ifdef USE_SEMIHOST
	initialise_monitor_handles();
#endif

	EdgeCutter2_LoadSettings(&Settings, &Params);
	LoadCalibrationEeprom();
	LoadEeprom();
	for(int j =0 ;j<18;j++) targetleds[j] = 255;
	TI1_Enable();
	AD1_Calibrate(TRUE);
	AD1_Measure(FALSE);
	for(int i = 0;i<13;i++)
	{
		for(int j =0 ;j<13;j++)
		{
			if (i == j) outleds[j] = 255; else outleds[j] = 0;
		}

		//	ShiftOut();
		WAIT1_Waitms(40);
	}
	for(int j =0 ;j<18;j++) targetleds[j] = 0;
	WAIT1_Waitms(140);

	ShiftOut();
	int switchmode = 1;
	SetupLeds();
	ShiftOut();

	byte commitchange = 0;
	for (;;)
	{


		if (pressed(&modesw_state))
		{
			switchmode = 1;
			Params.mode = (Params.mode + 1) % EDGECUTTER2_MAXMODE;
			commitchange = 1;
		}
		else
		{
			if (islongpress(&modesw_state))
			{
				Params.mode = (Params.mode + EDGECUTTER2_MAXMODE-1) % EDGECUTTER2_MAXMODE;
				commitchange = 1;
				switchmode = 1;
				switch(SpeedSwitchMode)
				{
				case SPEEDSWITCH_GATEMODE:  SpeedSwitchMode = SPEEDSWITCH_NORMAL;break;
				case SPEEDSWITCH_NORMAL:  SpeedSwitchMode = SPEEDSWITCH_GATEMODE;break;

				}



			}
		}


		if (pressed(&speedsw_state))
		{
			switchmode = 1;
			switch(SpeedSwitchMode)
			{

			case SPEEDSWITCH_NORMAL:  Params.speed = (Params.speed + 1) % EDGECUTTER2_MAXSPEED;break;
			case SPEEDSWITCH_GATEMODE:  Params.GatedMode = (Params.GatedMode + 1) % __SPEEDSWITCH_COUNT;break;
			}
			commitchange = 1;
		}

		if (pressed(&triggersw_state) )
		{
			buttonpressed = 1;
			EdgeCutter2_Trigger(&Envelope, 1, &Params);
			buttonjustpressed = 1;

		}

		if (released(&triggersw_state) )
		{
			buttonpressed = 0;
			EdgeCutter2_Trigger(&Envelope, 0 ,&Params);
		}
		int buttonled= 0;
		if (buttonpressed > 0 || Envelope.TriggerState == 1) buttonled = 128;
		if (buttonjustpressed >0)buttonled = 255;
		if (justretriggered > 0 && buttonpressed) buttonled = 255;
		justretriggered = 0;
		buttonjustpressed = 0;
		targetleds[18]  = buttonled;

		if (targetleds[18] > outleds[18]) outleds[18] = targetleds[18];

		if (measured == 1)
		{
			measured = 0;
			AD1_Measure(FALSE);
		}

		Envelope.A =Adjust( ~(adcchannels[ADC_A] ));
		Envelope.D =Adjust( ~(adcchannels[ADC_D] ));
		Envelope.S =Adjust( ~(adcchannels[ADC_S] ));
		Envelope.R = Adjust(~(adcchannels[ADC_R] ));
		Envelope.Curvature = Adjust(~(adcchannels[ADC_CURVATURE] ));
		Envelope.Velocity = ~(adcchannels[ADC_VELOCITY]);



		//if (switchmode == 1)
		//	{
		SetupLeds();

		//}
		denoise(JACK_RETRIGGER_GetVal(0), &retriggerjack_state);

		if (commitchange == 1 && tickssincecommit >= 10)
		{
			SaveEeprom();
			commitchange = 0;
			tickssincecommit = 0;
		}
	}
	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */


#ifndef KNOB
	#define KNOB(name,x,y,mintext,maxtext)
#endif

#ifndef LEDBUTTON
	#define LEDBUTTON(name,x,y)
#endif
#ifndef LED
	#define LED(name,x,y)
#endif

#ifndef ENCODER
#define ENCODER(name,x,y)
#endif

#ifndef SCREEN
#define SCREEN(name,x,y,w,h)
#endif

#ifndef FADER
#define FADER(name,x,y)
#endif

KNOB(Master_Tune, 1,1,"","")
LEDBUTTON(VCO1, 2,1)
KNOB(VCO1_Pitch, 3,1, "-2_oct","+2_oct")
KNOB(VCO1_PW, 4, 1, "", "")
LEDBUTTON(VCO4, 5, 1)
KNOB(VCO4_Pitch,6,1,"min","max")

KNOB(FM_1_to_2,1,2,"0","")
LEDBUTTON(VCO2,2,2)
KNOB(VCO2_Pitch,3,2,"-1/3d","+1/3d")
KNOB(VCO2_PW,4,2,"","")
LEDBUTTON(VCO5,5,2)
KNOB(VCO5_Pitch,6,2,"0","+3_oct")

KNOB(FM_2_to_3,1,3,"0","")
LEDBUTTON(VCO3,2,3)
KNOB(VCO3_Pitch,3,3,"-1/3d","+1/3d")
KNOB(VCO3_PW,4,3,"","")
LEDBUTTON(VCO6,5,3)
KNOB(VCO6_Pitch,6,3,"0","+3_oct")

LEDBUTTON(VCO7,5,4)
KNOB(VCO7_Pitch,6,4,"0","+3_oct")


LEDBUTTON(Interval_spread,2,4)

#define VCF1X 8
#define VCF1Y 1.5

KNOB(VCF1_Resonance,VCF1X,VCF1Y,"min","max")
LEDBUTTON(VCF1_ResonanceBut,VCF1X-0.2,VCF1Y+0.5)
LED(VCF1_O_L,VCF1X+0.5,VCF1Y-0.2)
KNOB(VCF1_Spectrum_Mod,VCF1X+1,VCF1Y,"0","")
LEDBUTTON(VCF1_Spectrum_ModBut,VCF1X+1.5,VCF1Y+0.5)

KNOB(VCF1_Frequency,VCF1X+0.5,VCF1Y + 1,"min","max")
LEDBUTTON(VCF1_FrequencyBut,VCF1X,VCF1Y+1.5)

#define VCF2X 11
#define VCF2Y 1.1


KNOB(VCF2_Spectrum_mod,VCF2X,VCF2Y,"0","")
KNOB(VCF2_Feed_Back,VCF2X+1,VCF2Y,"0","")
KNOB(VCF2_Resonance,VCF2X+2,VCF2Y,"0","")
LED(VCF2_O_L,VCF2X+2.5,VCF2Y-0.2)

LEDBUTTON(VCF2_SPM,VCF2X,VCF2Y+0.7)
LEDBUTTON(VCF2_F_B,VCF2X,VCF2Y+1.2)
LEDBUTTON(VCF2_RES,VCF2X,VCF2Y+1.7)


#define BANKX 14
#define BANKY 1
KNOB(Bank_Low,BANKX,BANKY,"min","max")
KNOB(Bank_Mid_1,BANKX+1,BANKY,"min","max")
KNOB(Bank_Mid_2,BANKX+2,BANKY,"min","max")
KNOB(Bank_High,BANKX+3,BANKY,"min","max")

LEDBUTTON(LowButton,BANKX,BANKY+1)
LEDBUTTON(Mid1Button,BANKX+1,BANKY+1)
LEDBUTTON(Mid2BUtton,BANKX+2,BANKY+1)
LEDBUTTON(HighButton,BANKX+3,BANKY+1)


KNOB(PB1,BANKX,BANKY+2,"min","max")
KNOB(PB2,BANKX+1,BANKY+2,"min","max")
KNOB(PB3,BANKX+2,BANKY+2,"min","max")
KNOB(PB4,BANKX+3,BANKY+2,"min","max")

LEDBUTTON(PB1but,BANKX,BANKY+3)
LEDBUTTON(PB2but,BANKX+1,BANKY+3)
LEDBUTTON(PB3but,BANKX+2,BANKY+3)
LEDBUTTON(PB4but,BANKX+3,BANKY+3)

#define AMPX 19
#define AMPY 1.5

LEDBUTTON(Cleanfeed_M_S,AMPX,AMPY+0.5)
KNOB(Cleanfeed,AMPX+1,AMPY,"L","R")
LEDBUTTON(VCF1_M_S,AMPX+2,AMPY+0.5)
KNOB(VCF1,AMPX+3,AMPY,"L","R")
LEDBUTTON(VCF2_M_S,AMPX+4,AMPY+0.5)
KNOB(VCF2,AMPX+5,AMPY,"L","R")

LEDBUTTON(Cleanfeed_VCA,AMPX,AMPY+1.5)
KNOB(Cleanfeed_Lvl,AMPX+1,AMPY+1,"L","R")
LEDBUTTON(VCF1_VCA,AMPX+2,AMPY+1.5)
KNOB(VCF1_Lvl,AMPX+3,AMPY+1,"L","R")
LEDBUTTON(VCF2_VCA,AMPX+4,AMPY+1.5)
KNOB(VCF2_lvl,AMPX+5,AMPY+1,"L","R")

LEDBUTTON(Cleanfeed_FX,AMPX+1,AMPY+2)
LEDBUTTON(VCF1_FX,AMPX+3,AMPY+2)
LEDBUTTON(VCF2_FX,AMPX+5,AMPY+2)


#define ADSRX VCF2X
#define ADSRY 7

LEDBUTTON(ADSR,ADSRX-0.5,ADSRY+0.5)
KNOB(ADSR_A,ADSRX,ADSRY,"","")
KNOB(ADSR_D,ADSRX+1,ADSRY,"","")
KNOB(ADSR_S,ADSRX+2,ADSRY,"","")
KNOB(ADSR_R,ADSRX+3,ADSRY,"","")


#define ADX VCF2X-0.5
#define ADY 8

LEDBUTTON(AD,ADX-0.5,ADY+0.5)
KNOB(AD_A,ADX,ADY,"","")
KNOB(AD_D,ADX+1,ADY,"","")


#define SCREENX (VCF2X+1)
#define SCREENY (VCF2Y+1)

SCREEN(mainscreen,SCREENX,SCREENY,2,4)
ENCODER(leftencoder,SCREENX-1,SCREENY+2)
ENCODER(rightencoder,SCREENX+2,SCREENY+2)


#undef SCREEN
#undef FADER
#undef ENCODER
#undef LEDBUTTON
#undef KNOB
#undef LED

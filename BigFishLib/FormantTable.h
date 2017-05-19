#pragma once
#include <stdint.h>

enum VoiceRegister
{
	Bass,
	Tenor,
	CounterTenor,
	Alto,
	Soprano
}; 

typedef struct Formant_t
{
	uint16_t Freq;
	int8_t Ampl;
	uint8_t Bandwidth;
} Formant_t;

typedef struct FormantSet_t
{
	VoiceRegister Reg;
	char Vowel;
	Formant_t Formants[5];
} FormantSet_t;

FormantSet_t Formants[] =
{
	{ Bass,'a',{ { 600,0,60 },{ 1040,-7,70 },{ 2250,-9,110 },{ 2450,-9,120 },{ 2750,-20,130 } } },
	{ Bass,'e',{ { 400,0,40 },{ 1620,-12,80 },{ 2400,-9,100 },{ 2800,-12,120 },{ 3100,-18,120 } } },
	{ Bass,'i',{ { 250,0,60 },{ 1750,-30,90 },{ 2600,-16,100 },{ 3050,-22,120 },{ 3340,-28,120 } } },
	{ Bass,'o',{ { 400,0,40 },{ 750,-11,80 },{ 2400,-21,100 },{ 2600,-20,120 },{ 2900,-40,120 } } },
	{ Bass,'u',{ { 350,0,40 },{ 600,-20,80 },{ 2400,-32,100 },{ 2675,-28,120 },{ 2950,-36,120 } } },

	
	{ Tenor,'a',{ { 650,0,80 },{ 1080,-6,90 },{ 2650,-7,120 },{ 2900,-8,130 },{ 3250,-22,140 } } },
	{ Tenor,'e',{ { 400,0,70 },{ 1700,-14,80 },{ 2600,-12,100 },{ 3200,-14,120 },{ 3580,-20,120 } } },
	{ Tenor,'i',{ { 290,0,40 },{ 1870,-15,90 },{ 2800,-18,100 },{ 3250,-20,120 },{ 3540,-30,120 } } },
	{ Tenor,'o',{ { 400,0,70 },{ 800,-10,80 },{ 2600,-12,100 },{ 2800,-12,130 },{ 3000,-26,135 } } },
	{ Tenor,'u',{ { 350,0,40 },{ 600,-20,60 },{ 2700,-17,100 },{ 2900,-14,120 },{ 3300,-26,120 } } },

	{ CounterTenor,'a',{ { 660,0,80 },{ 1120,-6,90 },{ 2750,-23,120 },{ 3000,-24,130 },{ 3350,-38,140 } } },
	{ CounterTenor,'e',{ { 440,0,70 },{ 1800,-14,80 },{ 2700,-18,100 },{ 3000,-20,120 },{ 3300,-20,120 } } },
	{ CounterTenor,'i',{ { 270,0,40 },{ 1850,-24,90 },{ 2900,-24,100 },{ 3350,-36,120 },{ 3590,-36,120 } } },
	{ CounterTenor,'o',{ { 430,0,40 },{ 820,-10,80},{ 2700,-26,100},{ 3000,-22,120},{ 3300,-34,120} } },
	{ CounterTenor,'u',{ { 370,0,40 },{ 630,-20,60 },{ 2750,-23,100},{ 3000,-30,120 },{ 3400,-34,120 } } },

	{ Alto,'a',{ { 800,0,80 },{ 1150,-4,90 },{ 2800,-20,120 },{ 3500,-36,130 },{ 4950,-60,140 } } },
	{ Alto,'e',{ { 400,0,60 },{ 1600,-24,80 },{ 2700,-30,120 },{ 3300,-35,150 },{ 4950,-60,200 } } },
	{ Alto,'i',{ { 350,0,50 },{ 1700,-20,100 },{ 2700,-30,120 },{ 3700,-36,150 },{ 4950,-60,200 } } },
	{ Alto,'o',{ { 450,0,70 },{ 800,-9,80 },{ 2830,-16,100 },{ 3500,-28,130 },{ 4950,-55,135 } } },
	{ Alto,'u',{ { 325,0,50 },{ 700,-12,60 },{ 2530,-30,170 },{ 3500,-40,180 },{ 4950,-64,200 } } },
	
	{ Soprano,'a',{ { 800,0,80 },{ 1150,-6,90 },{ 2900,-32,120 },{ 3900,-20,130 },{ 4950,-50,140 } } },
	{ Soprano,'e',{ { 350,0,60 },{ 2000,-20,100 },{ 2800,-15,120 },{ 3600,-40,150 },{ 4950,-56,200} } },
	{ Soprano,'i',{ { 270,0,60 },{ 2140,-12,90 },{ 2950,-26,100 },{ 3900,-26,120 },{ 4950,-44,120 } } },
	{ Soprano,'o',{ { 450,0,40 },{ 800,-11,80 },{ 2830,-22,100 },{ 3800,-22,120},{ 4950,-50,120 } } },
	{ Soprano,'u',{ { 325,0,50 },{ 700,-16,60 },{ 2700,-35,170 },{ 3800,-40,180},{ 4950,-60,200 } } }


};
//#include "..\..\EdgeCutter\Sources\EdgeCutter.h"
#include "..\..\EdgeCutterV2\Sources\EdgeCutter2.h"
//#include "..\..\Wobbler\Sources\Wobbler.h"
#include "..\..\WobblerV2\Sources\Wobbler2.h"
#include "..\..\Tuesday\Sources\Tuesday.h"
#include "..\..\Tuesday\Sources\Algo.h"

#include "../../BigFishLib/BigFish.cpp"
#include "../../BigFishLib/BleppyOscs.cpp"
#include "../../BigFishLib/OrganOsc.cpp"
#include "../../BigFishLib/ADSREnvelope.cpp"
#include "../../BigFishLib/FMOsc.cpp" 



BigFish_t Fish;
Tuesday_PatternGen Tuesday;
Tuesday_Settings TuesdaySettings;
Tuesday_Params TuesdayParams;


EdgeCutter2_Envelope EnvRunning;
EdgeCutter2_Envelope EnvStatic;
EdgeCutter2_Settings EnvSettings;
EdgeCutter2_Params EnvParams;


/*struct  Wobbler_LFO LFORunning;
struct  Wobbler_LFO LFOStatic;
struct  Wobbler_Settings LFOSettings;
struct  Wobbler_Params LFOParams;
*/

Wobbler2_LFO_t LFO2Static;
Wobbler2_Settings LFO2Settings;
Wobbler2_LFO_t LFO2Running;
Wobbler2_Params LFO2Params;

//Wobbler2_Pendulum_t Pendulum;
Wobbler2_PendulumInt_t PendulumInt;


extern "C"
{
	void __cdecl doTick()
	{
		Tuesday_Tick(&Tuesday, &TuesdayParams);
	}
	void __cdecl DoClock(int state)
	{
		Tuesday_Clock(&Tuesday, &TuesdaySettings, &TuesdayParams, state);
	}

	__declspec(dllexport) long __stdcall GetLFOPhaseInc(int p)
	{
		return Wobbler2_LFORange3(p<<8, 2000);
	}

	__declspec(dllexport) void __stdcall Init()
	{
		Wobbler2_Init(&LFO2Running);
#ifdef INTPENDULUM
		Wobbler2_InitIntPendulum(&LFO2Running.Pendulum, &LFO2Running);
#else
		Wobbler2_InitPendulum(&LFO2Running.Pendulum, &LFO2Running);
#endif
//		Wobbler2_InitIntPendulum(&PendulumInt);

		LFO2Static.Amount1 = 1 << 14;
		LFO2Static.Amount2 = 1 << 14;
		LFO2Running.Amount1 = 1 << 14;
		LFO2Running.Amount2 = 1 << 14;

		EdgeCutter2_LoadSettings(&EnvSettings, &EnvParams);
		EdgeCutter2_Init(&EnvRunning);
		EdgeCutter2_Init(&EnvStatic);
//		Wobbler_LoadSettings(&LFOSettings, &LFOParams);
		//Wobbler_Init(&LFORunning);
		Wobbler2_Init(&LFO2Static);

		EuroRack_InitCalibration();
		Tuesday_LoadSettings(&TuesdaySettings, &TuesdayParams);

		Tuesday_Init(&Tuesday);
		Tuesday_Generate(&Tuesday, &TuesdayParams, &TuesdaySettings);
	}

	__declspec(dllexport) void __stdcall  ResetStatic()
	{
		EdgeCutter2_Init(&EnvStatic);
		Wobbler2_Init(&LFO2Static);
	}

	__declspec(dllexport) int __stdcall GetEnv(int staticenv, int attack, int decay, int sustain, int release, int curvature, int speed, int mode)
	{
		EnvParams.mode = mode;
		EnvParams.speed = speed;
		EnvStatic.A = EnvRunning.A = attack;
		EnvStatic.D = EnvRunning.D = decay;
		EnvStatic.S = EnvRunning.S = sustain;
		EnvStatic.R = EnvRunning.R = release;
		EnvStatic.Curvature = EnvRunning.Curvature = curvature;
		EdgeCutter2_Calibration Calib = { 0 ,0 };
		if (staticenv == 0) return EdgeCutter2_GetEnv(&EnvRunning, &EnvParams, &Calib);
		return	EdgeCutter2_GetEnv(&EnvStatic, &EnvParams, &Calib);
	}

	__declspec(dllexport) int __stdcall GetEnvCurve(int staticenv)
	{
		if (staticenv == 0) return (int)(EnvRunning.CurvedOutput);
		return (int)(EnvStatic.CurvedOutput);
	}

	__declspec(dllexport) int __stdcall GetLed(int Led)
	{
		return EnvRunning.StateLeds[Led];
	}

	__declspec(dllexport) int __stdcall GetGate(int gate)
	{
		return EnvRunning.Gates[gate];
	}

	__declspec(dllexport) void __stdcall Trigger(int val, int staticenv, int mode)
	{
		EnvParams.mode = mode;
		if (staticenv == 0) EdgeCutter2_Trigger(&EnvRunning, val, &EnvParams);
		EdgeCutter2_Trigger(&EnvStatic, val, &EnvParams);
	}

	__declspec(dllexport) int __stdcall GetLFOLed(int led)
	{
		return LFO2Running.Led[0][led];
	}

	__declspec(dllexport)  int __stdcall GetLFO(int staticlfo, int speed, int shape, int mod, int phaseing)
	{
		struct Wobbler2_LFO_t *L = &LFO2Running;
		if (staticlfo) L = &LFO2Static;

		L->Speed = speed ;
		L->Shape = shape ;
		L->Mod = mod ;
		L->Phasing = phaseing ;
		 
		return Wobbler2_Get(L, &LFO2Params);
	}

	__declspec(dllexport)  int __stdcall GetLFOBasicShape(int staticlfo)
	{
		struct Wobbler2_LFO_t *L = &LFO2Running;
		if (staticlfo) L = &LFO2Static;
		return L->OutputsNormal[0];
	}


	__declspec(dllexport) int __stdcall GetLFOGate(int gate)
	{
		return LFO2Running.Gate[gate];
	}

	__declspec(dllexport) int __stdcall GetLFOPhased(int staticlfo)
	{
		if (staticlfo) return (int)(LFO2Static.OutputPhased);
		return (int)(LFO2Running.OutputPhased);
	}

	__declspec(dllexport) void __stdcall LFOTrigger(int value, int staticlfo)
	{
		struct Wobbler2_LFO_t *L = &LFO2Running;
		if (staticlfo) L = &LFO2Static;

		Wobbler2_Trigger(L, value, &LFO2Params);
	}

	__declspec(dllexport) int __stdcall Tuesday_GetTickVel(int tick)
	{
		return Tuesday.CurrentPattern.Ticks[tick].vel;
	}

	__declspec(dllexport) int __stdcall Tuesday_GetTickNote(int tick)
	{
		return Tuesday.CurrentPattern.Ticks[tick].note;
	}

	__declspec(dllexport) int __stdcall Tuesday_GetTickGate(int tick)
	{
		return Tuesday.CurrentPattern.Ticks[tick].vel > 0 ? 1 : 0;
	}

	__declspec(dllexport) int __stdcall Tuesday_GetTickSlide(int tick)
	{
		return Tuesday.CurrentPattern.Ticks[tick].slide;
	}

	__declspec(dllexport) int __stdcall Tuesday_GetTickLength(int tick)
	{
		return Tuesday.CurrentPattern.Ticks[tick].maxsubticklength;
	}

	__declspec(dllexport) int __stdcall Tuesday_GetTickAccent(int tick)
	{
		return Tuesday.CurrentPattern.Ticks[tick].accent;
	}

	__declspec(dllexport) int __stdcall Tuesday_GetPatternLength()
	{
		return Tuesday.CurrentPattern.Length;
	}

	__declspec(dllexport) void __stdcall Tuesday_UpdatePattern(int algo, int scale, int ticks, int beats, int tempo, int x, int y, int i)
	{
		TuesdayParams.algo = 0;
		TuesdaySettings.algooptions[0] = algo;

		TuesdayParams.beatopt = 0;
		TuesdaySettings.beatoptions[0] = beats;
		
		TuesdayParams.scale = 0;
		TuesdaySettings.scale[0] = scale;


		TuesdayParams.tpbopt = 0;
		TuesdaySettings.tpboptions[0] = ticks;

		Tuesday.seed2 = y;
		Tuesday.seed1 = x;
		Tuesday.intensity = i;
		Tuesday.tempo = tempo;

		Tuesday_Generate(&Tuesday, &TuesdayParams, &TuesdaySettings);
	}

	__declspec(dllexport) void __stdcall Tuesday_ClockTick(int ClockConnected, int val)
	{
		Tuesday.ClockConnected = ClockConnected;
		Tuesday_Clock(&Tuesday, &TuesdaySettings,&TuesdayParams,val);
	}

	__declspec(dllexport) void __stdcall Tuesday_DoTimer()
	{
		Tuesday_TimerTick(&Tuesday, &TuesdayParams);
	}


	__declspec(dllexport) bool __stdcall  Tuesday_GetAccent()
	{
		return Tuesday.Gates[GATE_ACCENT] > 0;
	}

	__declspec(dllexport) int __stdcall Tuesday_GetVel()
	{
		return Tuesday.VelocityOut;
	}

	__declspec(dllexport) int __stdcall Tuesday_GetCV()
	{
		return Tuesday.CVOut;
	}

	__declspec(dllexport) bool __stdcall  Tuesday_GetGate()
	{
		return Tuesday.Gates[GATE_GATE] > 0;
	}

	__declspec(dllexport) void TriggerWobbler()
	{
		Wobbler2_Trigger(&LFO2Running, 0, &LFO2Params);
	}

	__declspec(dllexport) float RunPendulum()
	{
#ifdef INTPENDULUM
		Wobbler2_DoublePendulumInt(&LFO2Running.Pendulum,10);
#else
		Wobbler2_DoublePendulum(&LFO2Running.Pendulum, 0.05);
#endif


		LFO2Running.Output = LFO2Running.Pendulum.As;
		LFO2Running.OutputPhased = LFO2Running.Pendulum.Bs;


		LFO2Running.Output = LFO2Running.Output / (0xffff * 4);
		LFO2Running.OutputPhased = LFO2Running.OutputPhased / (0xffff * 4);


		LFO2Running.Output += 2048;// + (2540 - 2048);
		LFO2Running.OutputPhased += 2048;// +(2540 - 2048);


		Wobbler2_GetSteppedResult(0xffff, 2, &LFO2Running.ShapeStepped);
		Wobbler2_DoLeds(&LFO2Running);


		return (float)LFO2Running.Pendulum.A;
	}

	__declspec(dllexport) float RunPendulum2()
	{
		return (float)LFO2Running.Pendulum.B;
	}

	__declspec(dllexport) int32_t RunPendulumInt()
	{
//		Wobbler2_DoublePendulumInt(&PendulumInt);
		return PendulumInt.A;
		
	}
	__declspec(dllexport) int32_t GetWobbleLed(int32_t i, int32_t v)
	{
		return LFO2Running.Led[v][i];
		
	}
	

	__declspec(dllexport) int32_t RunPendulum2Int()
	{
		return PendulumInt.B;
	}

	char *GetName(int i)
	{
		switch (i)
		{
		case 0: return "_2sub1";
		case 1: return "_1sub2";
		case 2: return "c1sub2";
		case 3: return "c1sub2SQUARED";
		case 4: return "s1sub2";
		case 5: return "T1a1";
		case 6: return "T1a2";
		case 7: return "T1a";
		case 8: return "T1";
		case 9: return "T2b1";
		case 10: return "T2b";
		case 11: return "T2";
		case 12: return "T3b";
		case 13: return "T3"; 
		case 14: return "T4";
		case 15: return "T5a1";
		case 16: return "T5a2";
		case 17: return "T5a";
		case 18: return "T5";
		case 19: return "T6b";
		case 20: return "T6";		
		case 21: return "st1";
		case 22: return "st2";
		case 23: return "dTheta1SQUARED";
		case 24: return "dTheta2SQUARED";
		case 25: return "l1_x_dTheta1SQUARED";
		case 26: return "l2_x_dTheta2SQUARED";
		case 27: return "Theta1";
		case 28: return "Theta2";
		case 29: return "d2Theta1";
		case 30: return "d2Theta2";
		case 31: return "dTheta1";
		case 32: return "dTheta2";

		}
		return "beh";
	}
	__declspec(dllexport) void Compare()
	{
		printf(" Compare start\n");
		float *A = (float*)&LFO2Running.Pendulum._2sub1;
		int32_t *B = (int32_t*)&PendulumInt._2sub1;
		for (int i = 0; i < 33;i++)
		{
			float fB = *B *(1.0 / (1 << WOBBLER_FIXBITS));
			float fA = *A;
			A++;
			B++;

			float diff = fB - fA;
			printf("%20s -> %.6f -> %.6f = %.6f\n",GetName(i), fA, fB, diff);
		}
		printf(" Compare done\n");
	}

}

#include <Windows.h>
#include <stdio.h>

extern "C"
{
	void SaveSettingsEeprom()
	{

	}

	void SaveCalibrationEeprom()
	{

	}
	void SaveEeprom()
	{
	}
}

void DoSubDivTest(int clockmode, int maxclocks, int tpbopt)
{

	Init();
	TuesdaySettings.ClockSubDivMode = clockmode;
	Tuesday_SetupClockSubdivision(&Tuesday, &TuesdaySettings, &TuesdayParams);

	Tuesday.CurrentPattern.TPB = 4;
	Tuesday.tempo = 128;
	Tuesday.intensity = 100;
	TuesdayParams.tpbopt = tpbopt;
	Tuesday_UpdatePattern(0, 0, 4, 4, 200, 0, 0, 255);
	int LastI = 0;
	int gates[TUESDAY_GATES];
	for (int i = 0; i < TUESDAY_GATES; i++) gates[i] = -1;
	int LastTick = -2;
	int LastNewTick = -3;
	
	Tuesday_Reset(&Tuesday, &TuesdaySettings, 1);
	Tuesday_Reset(&Tuesday, &TuesdaySettings, 0);

	int lastnonzeroes = -1;
	int cv = 0;
	for (int i = 0; i < maxclocks; i++)
	{
		Tuesday_Clock(&Tuesday,&TuesdaySettings, &TuesdayParams, ((cv++)%2==0)?1:0);

		int nonzeroes = 0;
		for (int j = 0; j < TUESDAY_GATES - 1; j++)
		{
			nonzeroes += Tuesday.Gates[j];
		}
		bool print = true;
		if (nonzeroes == 0) print = false;
		lastnonzeroes = nonzeroes;
		if (print)
		{
			printf("%d) ", i);

			for (int j = 0; j < TUESDAY_GATES - 1; j++)
			{
				nonzeroes += Tuesday.Gates[j];
				char L[TUESDAY_GATES] = { 'G', 'a', 'L', 'b', 'c', 't' };
				printf("%c ", Tuesday.Gates[j] > 0 ? L[j] : ' ');
				Tuesday.Gates[j] = 0;
			}
		}


		if (Tuesday.Tick != LastTick || Tuesday.NewTick != LastNewTick)
		{
			if (!print)
			{
				printf("%d) ", i);
			}
			print = true;
			if (Tuesday.Tick != LastTick || Tuesday.NewTick != LastNewTick)
			{
				printf("NewTick: %d - Tick: %d - delta %d ", Tuesday.NewTick, Tuesday.Tick, i - LastI);
				LastI = i;
				LastTick = Tuesday.Tick;
				LastNewTick = Tuesday.NewTick;
			}
		}
		if (print) printf("\n");
	}
}

void RunTimingTest()
{
	for (int i = 0; i < 4; i++)
	{
		printf("**** 4 PPQN %d tpb\n", (int)TuesdaySettings.tpboptions[i]);
		DoSubDivTest(CLOCKSUBDIV_4, 4 * 4, i);
		printf("\n\n**** 8 PPQN %d tpb\n", (int)TuesdaySettings.tpboptions[i]);
		DoSubDivTest(CLOCKSUBDIV_8, 8 * 4,i);
		printf("\n\n**** 16 PPQN %d tpb\n", (int)TuesdaySettings.tpboptions[i]);
		DoSubDivTest(CLOCKSUBDIV_16, 16 * 4,i);
		printf("\n\n**** 24 PPQN %d tpb\n", (int)TuesdaySettings.tpboptions[i]);
		DoSubDivTest(CLOCKSUBDIV_24PPQN, 24 * 4,i);
	}

}

void checkbuffer(int32_t *buf, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (buf[i] > 35000 || buf[i] < -35000)
		{
			printf("^");
		}
	}
}
void FishCycle()
{
	int bufferosc[1000];
	int buffermain[1000];
	int inputfalse[1000];
	for (int i = 0; i < 127; i++)
	{
		printf(".");
		BigFish_GenerateBlock(&Fish, inputfalse, bufferosc, buffermain, 1000);
		checkbuffer(bufferosc, 1000);
		checkbuffer(buffermain, 1000);

		int32_t pitchtarget = (i * (1 << 14)) / 12;
		Fish.PitchInput = pitchtarget;

		Fish.Gates[GATE_GATE] = 1;
		BigFish_GenerateBlock(&Fish, inputfalse, bufferosc, buffermain, 1000);
		checkbuffer(bufferosc, 1000);
		checkbuffer(buffermain, 1000);
		Fish.Gates[GATE_GATE] = 0;
	}
	printf("!\n");
}

void RunFishTest()
{
	BigFish_Update(&Fish);
	for (int i = 0; i < __PARAMCOUNT; i++)
	{
		Fish.Parameters[i] = 0;
	}
	Fish.Parameters[AMP_ATTACK] = (10 * 65536) / 127;;
	Fish.Parameters[AMP_DECAY] = (10 * 65536) / 127;;

	Fish.Parameters[FILTER_ATTACK] = (10 * 65536) / 127;;
	Fish.Parameters[FILTER_DECAY] = (80 * 65536) / 127;;

	Fish.Parameters[AMP_SUSTAIN] = (64 * 65536) / 127;
	Fish.Parameters[AMP_RELEASE] = (64 * 65536) / 127;;
	Fish.Parameters[PITCH_COARSE] = (64 * 65536) / 127;;
	Fish.Parameters[PITCH_FINE] = (64 * 65536) / 127;;

	//Fish.Parameters[OSC_SHAPE] = ( * 65536) / 127;;

	FishCycle();

	for (int i = 0; i < 2; i++)
	{
		for (int i2 = 0; i2 < __PARAMCOUNT; i2++)
		{
			Fish.Parameters[i2] = rand()%65536;
		}
		FishCycle();
	}
}

void RunTest(const char * name, int i)
{
	int min = 10000;
	int max = -1000;
	double avg = 0;
	int c = 0;
	bool HasOffs = false;
	for (int bang = 0; bang < 255; bang += 16)
	{
		for (int y = 0; y < 255; y += 16)
		{

			for (int x = 0; x < 255; x += 16)
			{
				int patlen = Tuesday.CurrentPattern.Length;
				
				Tuesday_UpdatePattern(i, 0, 1, 2, 0, x, y, bang);
				for (int j = 0; j < patlen; j++)
				{
					Tuesday_Tick_t &T = Tuesday.CurrentPattern.Ticks[j];
					if (T.note != TUESDAY_NOTEOFF)
					{
						c++;
						if (T.note < min) min = T.note; else if (T.note > max) max = T.note;
					}
					else
					{
						HasOffs = true;
					}
					avg = avg + T.note;
				}
			}
		}
	}
	avg /= (double)c;

	printf("%s (%d): \tmin %d \tmax %d\tavg:%2f\tHas Offs: %d\n", name, i, min, max, avg, HasOffs ? 1 : 0);
}

void CalTest()
{
	for (int i = 0; i < 4096; i += 256)
	{
		int R = CalibratedDAC(0, i);
		printf("%d %d\n", i, R);
	}
}

void PrintPlot(int V, int min, int max)
{
	float F = (V - min) / (float)(max - min);
	if (F < 0) F = 0;
	if (F > 1) F = 1;
	printf("|");
	for (int i = 0; i < 42; i++)
	{
		float F2 = i / 41.0f;
		if (F < F2) printf(" "); else printf("*");
	}
	printf("|\n");
}
void PrintPlot2(int V,int V2, int min, int max)
{
	float F = (V - min) / (float)(max - min);
	if (F < 0) F = 0;
	if (F > 1) F = 1;
	float F2 = (V2 - min) / (float)(max - min);
	if (F2 < 0) F2 = 0;
	if (F2 > 1) F2 = 1;
	printf("|");
	for (int i = 0; i < 75; i++)
	{
		float Fl = i / 74.0f;
		bool a = F > Fl;
		bool b = F2 > Fl;
		int R = (a ? 1 : 0) + (b ? 2 : 0);
		switch (R)
		{
		case 0: printf(" "); break;
		case 1: printf("*"); break;
		case 2: printf("o"); break;
		case 3: printf("#"); break;
		}
	}
	printf("|\n");
}
extern void ADSR_BuildTable();
void ExpTest()
{


	ADSR_BuildTable();
	ADSR_Envelope_t Env;
	ADSR_Init(&Env, ENVMODE_GATE, 0, ENVTABLE_LOG);
	Env.A = 140<<1;
	Env.D = 140<<2;
	Env.S = 150;
	Env.R = 160<<1;
	ADSR_Trigger(&Env, 1);
	ADSR_Update(&Env, 1000);
	for (int i = 0; i < 1000; i++)
	{

		int R = ADSR_Get(&Env);
		int R2 = Env.CurvedOutput >> (ENVFIXEDBITS - 16);
		if (i == 500) ADSR_Trigger(&Env, 0);
		//if (i%10 == 0) PrintPlot(R, 0, 0xffff);
		if (i % 10 == 0) PrintPlot2(R,R2, 0, 0xffff);
	}

	for (uint32_t i = 0; i < (uint32_t)(65536.0* 60000); i += uint32_t( 60000 * 600))
	{
//		printf("%08x\n",GetExpTable(i));
	}
//	printf("done!\n");
}

void FindDoublePendulumFreqs()
{
	
	LFO2Static.Shape = ((255 / 5) * 4) << 8;
	for (int i = 0; i < 256; i++)
	{
		int timesincezcross = 0;
		Wobbler2_Init(&LFO2Static);
		LFO2Static.Speed = i << 10;
		LFO2Static.Mod = 128 << 8;
		LFO2Static.Phasing = 0;
		LFO2Static.Shape = 0;

		Wobbler2_Trigger(&LFO2Static, 1, &LFO2Params);
		int zerocrosstimes = 0;
		int totaltime = 0;
		int last = 0;
		for (int j = 0; j < 100; j++)
		{
			Wobbler2_Get(&LFO2Static, &LFO2Params);
			int newv = LFO2Static.OutputsNormal[4];
			if (last < 0 && newv > 0)
			{
				totaltime += timesincezcross;
				zerocrosstimes++;
				timesincezcross = 0;
			}		
			else
			{
				timesincezcross++;
			}
			last = newv;
		}
		printf("%d -> %d crossings at %f samples per cross average\n", i, zerocrosstimes, totaltime / (float)zerocrosstimes);
	};
}

BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
)
{

	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		int32_t V[4] = { 0,65536,0,65536 };
		//CalTest();
		Wobbler2_LoadSettings(&LFO2Settings, &LFO2Params);
		Wobbler2_Init(&LFO2Running);
		Wobbler2_Init(&LFO2Static);

		LFO2Running.Amount1 = 1 << 14;
		LFO2Running.Amount2 = 1 << 14;

		LFO2Static.Amount1 = 1 << 14;
		LFO2Static.Amount2 = 1 << 14;

		BigFish_Init(&Fish, 44100);

//		FindDoublePendulumFreqs();

//		ExpTest();
	//	RunFishTest();
		LFO2Static.Speed = 0x80;
		Init();

	/*	RunTest("Tests", ALGO_TESTS);
		RunTest("TriTrance", ALGO_TRITRANCE);
		RunTest("Stomper", ALGO_STOMPER);
		RunTest("Markov", ALGO_MARKOV);
		RunTest("Wobble", ALGO_WOBBLE);
		RunTest("Chip 1", ALGO_CHIPARP1);
		RunTest("Chip 2", ALGO_CHIPARP2);
		RunTest("SNH", ALGO_SNH);
		RunTest("Saiko Lead", ALGO_SAIKO_LEAD);
		RunTest("Saiko Classic", ALGO_SAIKO_CLASSIC);
		RunTest("ScaleWalker", ALGO_SCALEWALKER);
		RunTest("TooEasy", ALGO_TOOEASY);
		RunTest("Random", ALGO_RANDOM);
		*/

//		RunTimingTest();

		if (0)
		{
			for (int i = 0; i < 256; i++)
			{
				LFO2Static.Phasing = 80 + ((i / 80) % 2);

				Wobbler2_Get(&LFO2Static, &LFO2Params);

			//	printf("%x %x %x\n", LFOStatic.OldPhase2, LFOStatic.Phase2, LFOStatic.Gate[1]);

			}
		}
	}
	return TRUE;
}
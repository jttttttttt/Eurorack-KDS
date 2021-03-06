#pragma once

#include <dsplib/zdfsvf.hpp>
#include <stdint.h>

extern "C" {
#include "cv_adc.h"
#include "dsplib/cvsmooth.h"
//#include "dsplib/dpw_osc.h"
//#include "dsplib/cvsmooth.h"

#include "MODE1A.h"
#include "MODE1B.h"
#include "MODE2A.h"
#include "MODE2B.h"
#include "LEDS.h"
};

static volatile int32_t mode1 = 0;
static volatile int32_t mode2 = 0;

static inline void dsp_work(int32_t *outl, int32_t *outr, int32_t inl, int32_t inr)
{
	//static struct dpw_sawtooth_state_t state1;
	//static struct dpw_pulse_state_t state2;
	//static struct cvsmooth_state_t pw_smooth_state;

	//uint32_t pulsewidth = cvsmooth(adc_value(2) << 16, &pw_smooth_state);

	int32_t cutoff_knob = adc_value(0);
	int32_t resonance_knob = adc_value(1);
	int32_t gain_knob = adc_value(2);
	int32_t pitch = cv_adc_value() + (cutoff_knob>>2) + (cutoff_knob>>5);
	if (pitch > 0x7fff) pitch = 0x7fff;
	else if (pitch < 0) pitch = 0;

	svf_stereo(outl, outr, inl, inr, pitch, resonance_knob, gain_knob, mode1, mode2);

	//*outl = dpw_sawtooth(pitch, &state1);
	//*outr = dpw_pulse(pitch, pulsewidth, &state2);
}

static inline void dsp_loop()
{
	if (!MODE1A_GetVal(MODE1A_DeviceData)) {
		mode1 = 0;
	}
	else if (!MODE1B_GetVal(MODE1B_DeviceData)) {
		mode1 = 2;
	}
	else {
		mode1 = 1;
	}

	if (!MODE2A_GetVal(MODE2A_DeviceData)) {
		mode2 = 0;
	}
	else if (!MODE2B_GetVal(MODE2B_DeviceData)) {
		mode2 = 2;
	}
	else {
		mode2 = 1;
	}

	LEDS_WriteByte((4 >> mode1) | (8 << mode2));
}


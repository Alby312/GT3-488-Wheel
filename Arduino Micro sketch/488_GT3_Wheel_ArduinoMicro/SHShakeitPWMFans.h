#ifndef __SHSHAKEITPWMFANS_H__
#define __SHSHAKEITPWMFANS_H__

#include <Arduino.h>
#include "SHShakeitBase.h"
#include <TimerOne.h>

class SHShakeitPWMFans : public SHShakeitBase {
private:

	byte pins[4];
	byte mins[4];
	byte maxs[4];
	byte enabledOutputs;
public:
	uint8_t motorCount() {
		return enabledOutputs;
	}

	String providerName() {
		return "PWMFan";
	}

	void begin(byte pEnabledOutputs, byte pPin01, byte pPin02, byte	pPin03, byte pPin04) {

		Timer1.initialize(40);

		pins[0] = pPin01;
		pins[1] = pPin02;
		pins[2] = pPin03;
		pins[3] = pPin04;
		enabledOutputs = pEnabledOutputs;
		for (int i = 0; i < pEnabledOutputs; i++) {
			Timer1.pwm(pins[i], 0);
		}
	}

	void setMin(byte pMin01, byte pMin02, byte	pMin03, byte pMin04) {
		mins[0] = pMin01;
		mins[1] = pMin02;
		mins[2] = pMin03;
		mins[3] = pMin04;
	}

	void setMax(byte pMax01, byte pMax02, byte	pMax03, byte pMax04) {
		maxs[0] = pMax01;
		maxs[1] = pMax02;
		maxs[2] = pMax03;
		maxs[3] = pMax04;
	}

protected:
	void setMotorOutput(uint8_t motorIdx, uint8_t value) {
		double value2 = value;
		if (value2 < mins[motorIdx]) {
			value2 = 0;
		}
		else {
			value2 = (value2) / 255.0 * (double)maxs[motorIdx];
		}

		Timer1.pwm(pins[motorIdx], (int)(((float)value2 / 255.0) * 1023.0));
		
	}
};

#endif

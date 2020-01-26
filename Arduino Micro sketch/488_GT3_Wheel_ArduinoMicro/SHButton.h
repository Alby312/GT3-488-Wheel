#ifndef __SHBUTTON_H__
#define __SHBUTTON_H__

#include <Arduino.h>
#include "SHFastIO.h"

typedef void(*SHButtonChanged) (int, byte);

class SHButton {

private:

	FastDigitalPin button;
	uint8_t buttonState;
	int buttonLastState;
	unsigned long buttonLastStateChanged;
	byte id;
	SHButtonChanged shButtonChangedCallback;

public:

	void begin(byte buttonid, uint8_t buttonPin, SHButtonChanged changedcallback) {
		button.begin(buttonPin);
		if (buttonPin > 0) {
			pinMode(buttonPin, INPUT_PULLUP);
		}
		id = buttonid;
		buttonLastState = button.digitalRead();
		shButtonChangedCallback = changedcallback;
	}

	uint8_t getPressed() {
		return !buttonLastState;
	}

	void read() {
		buttonState = button.digitalRead();
		if (buttonState != buttonLastState && buttonLastStateChanged - millis() > 50) {
			shButtonChangedCallback(id, buttonState == HIGH ? 0 : 1);
			buttonLastState = buttonState;
			buttonLastStateChanged = millis();
		}
	}
};

#endif

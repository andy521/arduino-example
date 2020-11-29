#ifndef Mkeyin_h
#define Mkeyin_h

#include "Arduino.h"
template< byte chipCount, typename MkeyType>
class _Mkeyin {
private:
	byte ploadPin;
	byte clockEnablePin;
	byte dataPin;
	byte clockPin;

	const uint16_t dataWidth;
	uint8_t pulseWidth;

	MkeyType lastState;
	MkeyType currentState;
public:
	_Mkeyin() : dataWidth(chipCount * 8), pulseWidth(5), lastState(0), currentState(0) {}
	
	// setup all pins
	void begin() {
		pinMode(ploadPin = 7, OUTPUT);
		pinMode(clockEnablePin = 8, OUTPUT);
		pinMode(dataPin = 2, INPUT);
		pinMode(clockPin = 4, OUTPUT);
	}
	
	inline uint8_t getPulseWidth() { return pulseWidth; }
	inline void setPulseWidth(uint8_t value) { pulseWidth = value; }
	inline uint16_t getDataWidth() { return dataWidth; }
	// whether some value has changed
	inline boolean hasChanged() { return lastState != currentState; }
	// whether the value with index 'id' has changed
	inline boolean hasChanged(int id) { return state(id) != last(id); }
	// returns the state from the last frame
	inline MkeyType getLast() { return lastState; }
	// returns the current state
	inline MkeyType getCurrent() { return currentState; }
	// whether button 'id' is pressed or not
	inline boolean state(int id) { return bitRead(currentState, id); }
	// whether button 'id' was pressed in the last frame
	inline boolean last(int id) { return bitRead(lastState, id); }
	// whether button 'id' is now pressed, but wasn't pressed in the last frame
	inline boolean pressed(int id) { return !last(id) && state(id); }
	// whether button 'id' is now released, but was pressed in the last frame
	inline boolean released(int id) { return last(id) && !state(id); }
	
	// read in data from shift register and return the new value
	MkeyType read() {
		lastState = currentState;
		MkeyType result = 0;

		digitalWrite(clockEnablePin, HIGH);
		digitalWrite(ploadPin, LOW);
		delayMicroseconds(pulseWidth);
		digitalWrite(ploadPin, HIGH);
		digitalWrite(clockEnablePin, LOW);

		for(int i = 0; i < dataWidth; i++) {
			MkeyType value = digitalRead(dataPin);
			result |= (value << ((dataWidth-1) - i));
			digitalWrite(clockPin, HIGH);
			delayMicroseconds(pulseWidth);
			digitalWrite(clockPin, LOW);
		}
		currentState = result;
		return result;
	}
	
	// same as read, but it returns whether something has changed or not
	boolean update() {
		return read() != lastState;
	}
};

// 后退64位状态（最多8个Mkey寄存器）
template<byte chipCount>
class Mkeyin : public _Mkeyin<chipCount, uint64_t> {};
// 单MMC寄存器（8位状态）
template<>
class Mkeyin<1> : public _Mkeyin<1, uint8_t> {};
// two Mkey registers (16 bit state)
template<>
class Mkeyin<2> : public _Mkeyin<2, uint16_t> {};
// three Mkey registers (32 bit state)
template<>
class Mkeyin<3> : public _Mkeyin<3, uint32_t> {};
// four Mkey registers (32 bit state)
template<>
class Mkeyin<4> : public _Mkeyin<4, uint32_t> {};

#endif
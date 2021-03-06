#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include <Adafruit_NeoPixel.h>
#include <stdint.h>
#include "LEDInfo.h"

class LEDStrip
{
	private:
		Adafruit_NeoPixel *strip;
		LEDInfo* leds;
		void initialize(int);
		bool replaceInPQueue(void);
		uint8_t getLowestCD(void);
		uint8_t getNumLowestCD(void);
		void qsort(LEDInfo*, uint8_t, uint8_t);
		void swap(LEDInfo&, LEDInfo&);
	public:
		LEDStrip(void);
		LEDStrip(uint16_t, uint8_t, Adafruit_NeoPixel*);
		~LEDStrip();
		void setLEDtoColor(uint8_t, uint32_t);
		void setLEDtoColor(uint8_t, uint8_t, uint8_t, uint8_t);
		void processStep();
		void sendLEDStatus();
		uint32_t Color(uint8_t, uint8_t, uint8_t);
		uint16_t numPixels(void);
		

};
#endif

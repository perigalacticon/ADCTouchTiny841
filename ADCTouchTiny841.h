/*
  ADCTouchTiny841.h - Library for Capacittive touch sensors using only one ADC PIN for the ATTINY841 Microcontroller.
  Created by Stephen Kramer 7/24/2016.
  This is a version of ADCTouch.h by martin2250, April 23, 2014; modified for the ATTINY841 Microcontroller.
  Released into the public domain.
*/
#ifndef ADCT_h
#define ADCT_h

#include "Arduino.h"

class ADCTouchTiny841Class
{
	public:
	int read(byte ADCChannel, int samples = 100);
};

extern ADCTouchTiny841Class ADCTouchTiny841;

#endif
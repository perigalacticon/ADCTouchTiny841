/*
  ADCTouchTiny841.cpp - Library for Capacittive touch sensors using only one ADC PIN for the ATTINY841 Microcontroller.
  Created by Stephen Kramer 7/24/2016.
  This is a version of ADCTouch.cpp by martin2250, April 23, 2014; modified for the ATTINY841 Microcontroller.
  Released into the public domain.
*/
#include <SPI.h>
#include "DataFlash.h"
#include "Arduino.h"
#include "ADCTouchTiny841.h"
// #define DEBUG true


int ADCTouchTiny841Class::read(byte ADCChannel, int samples)
{
	
#if DEBUG
    Serial.print("1st ADCSRA = ");
	Serial.println(ADCSRA, BIN);
	Serial.println("library initial");
	Serial.print("DDRA = ");
	Serial.println(DDRA, BIN);
	Serial.print("PUEA = ");
	Serial.println(PUEA, BIN);	
	// Serial.print("DDRB = ");
	// Serial.println(DDRB, BIN);
	// Serial.print("PUEB = ");
	// Serial.println(PUEB, BIN);
	Serial.print("ADCChannel = ");
	Serial.println(ADCChannel);	
#endif

	long _value = 0;
	for(int _counter = 0; _counter < samples; _counter ++)
	{
		
#if DEBUG		
		Serial.println("b4 set INPUT_PULLUP");
		Serial.print("DDRA = ");
		Serial.println(DDRA, BIN);		
		Serial.print("PUEA = ");
		Serial.println(PUEA, BIN);
		// delay(10000);
#endif		

		pinMode(ADCChannel, INPUT_PULLUP);
		
#if DEBUG
		Serial.println("after set INPUT_PULLUP");
		Serial.print("DDRA = ");
		Serial.println(DDRA, BIN);
		Serial.print("PUEA = ");
		Serial.println(PUEA, BIN);		
		// Serial.print("DDRB = ");
		// Serial.println(DDRB, BIN);
		// Serial.print("PUEB = ");
		// Serial.println(PUEB, BIN);		
				// delay(10000);
		Serial.print("0 ADMUXA = ");
		Serial.println(ADMUXA, BIN);
#endif

		ADMUXA = 0b00001110; // set MUX to GND;  ADMUX = 0b1101 for Tiny85, ADMUXA = 0b001110 for 841.
		ADCSRA |= _BV(ADPS1) | _BV(ADPS2); // set clock to 64.
		ADMUXB = 0b00000000;  // 841 sets voltage ref = VCC and gain = 1.		

#if DEBUG
        Serial.print("1st ADMUXA = ");
		Serial.println(ADMUXA, BIN);
		Serial.print("ADMUXB = ");		
		Serial.println(ADMUXB, BIN);
        Serial.print("2nd ADCSRA = ");			
		Serial.println(ADCSRA, BIN);		
		Serial.println("b4 set ADSC");
		Serial.print("DDRA = ");
		Serial.println(DDRA, BIN);
		Serial.print("PUEA = ");
		Serial.println(PUEA, BIN);		
		// Serial.print("DDRB = ");
		// Serial.println(DDRB, BIN);
		// Serial.print("PUEB = ");
		// Serial.println(PUEB, BIN);		
#endif

		//  for Tiny85:  ADCSRA |= _BV(ADPS1) | _BV(ADPS2);  //  sets ADC clock prescaler to 64.
		ADCSRA |= (1<<ADSC); //start conversion
		
#if DEBUG
        Serial.print("3rd ADCSRA = ");		
		Serial.println(ADCSRA, BIN);
#endif

		while(!(ADCSRA & (1<<ADIF))); //wait for conversion to finish
		ADCSRA |= (1<<ADIF); //reset the flag
		
#if DEBUG
        Serial.print("4th ADCSRA = ");		
		Serial.println(ADCSRA, BIN);
#endif

		pinMode(ADCChannel, INPUT);
		// delay(5000);

#if DEBUG
		Serial.print("2nd ADMUXA = ");
		Serial.println(ADMUXA, BIN);
		Serial.println("b4 aR");
		Serial.print("DDRA = ");
		Serial.println(DDRA, BIN);
		Serial.print("PUEA = ");
		Serial.println(PUEA, BIN);	
		// Serial.print("DDRB = ");
		// Serial.println(DDRB, BIN);
		// Serial.print("PUEB = ");
		// Serial.println(PUEB, BIN);		
#endif

		_value += analogRead(ADCChannel);
		
#if DEBUG
		Serial.print("3rd ADMUXA = ");
		Serial.println(ADMUXA, BIN);
		Serial.println("after aR");	
		Serial.print("DDRA = ");
		Serial.println(DDRA, BIN);
		Serial.print("PUEA = ");
		Serial.println(PUEA, BIN);	
		// Serial.print("DDRB = ");
		// Serial.println(DDRB, BIN);
		// Serial.print("PUEB = ");
		// Serial.println(PUEB, BIN);		
#endif

	}
	
	return _value / samples;
}

ADCTouchTiny841Class ADCTouchTiny841;
#ifndef WIFI_H_
#define WIFI_H_

#include <Arduino.h>

#include <Stream.h>
#include "crc16.h"
//#include <mqtt.h>
#include "rest.h"
#include "espduino.h"
#include "ringbuf.h"
#include "FP.h"
#include <string.h>

#ifdef __AVR_ATmega328P__

//#else

#include "SC16IS750.h"

class WifiClass {

	public:
		void begin();

		void print(String str);
		void println(String str);
		int read();		

		WifiData stream();

		boolean available();
		boolean connected();

		void connect(char* , char*);

		void powerON();
		void powerOFF();

};

extern WifiClass Wifi;

#endif


#endif /* WIFI_H_ */

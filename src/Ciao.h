/*
****************************************************************************
* Copyright (c) 2015 Arduino srl. All right reserved.
*
* File : Ciao.h
* Date : 2016/02/16
* Revision : 0.0.2 $
* Author: andrea[at]arduino[dot]org
* Author: adriano[at]arduino[dot]org
*
****************************************************************************

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef CIAO_H_
#define CIAO_H_

#include <Arduino.h>
#include "lib/CiaoData.h"
#include <Stream.h>

#if defined(__AVR_ATmega32U4__) || defined(ARDUINO_ARCH_SAMD)

#if defined(__AVR_ATmega32U4__)
#define BAUDRATE 250000
#elif defined(ARDUINO_ARCH_SAMD)
#define BAUDRATE 115200
#endif

class CiaoClass {
	public:
		void begin();
		CiaoData read( String protocol, String param1 = "", String param2 = "", String param3 = "");
		CiaoData write( String protocol, String param1, String param2 = "", String param3 = "");
		CiaoData writeResponse( String protocol, String id, String param1="", String param2 = "", String param3 = "");
		CiaoData parse( String, String);
		void println(String log){};
		#if defined(__AVR_ATmega32U4__) 
		CiaoClass(Stream &_stream);
		#elif defined(ARDUINO_ARCH_SAMD)
		CiaoClass(Serial_ stream);
		#endif

	private:
		void dropAll();
		bool started;
		#if defined(__AVR_ATmega32U4__)
		Stream &stream;
		#elif defined(ARDUINO_ARCH_SAMD)
		Serial_ stream;
		#endif
};

// This subclass uses a serial port Stream
class SerialCiaoClass : public CiaoClass {
	public:
		#if defined(__AVR_ATmega32U4__)
		SerialCiaoClass(HardwareSerial &_serial)
			: CiaoClass(_serial), serial(_serial) {
			// Empty
		}
		#elif defined(ARDUINO_ARCH_SAMD)
		SerialCiaoClass(Serial_ serial)
			: CiaoClass(serial){
			// Empty	
		}
		#endif
		void begin( unsigned long baudrate = BAUDRATE) {
			serial.begin(baudrate);
			CiaoClass::begin();
		}
	private:
		#if defined(__AVR_ATmega32U4__)
		HardwareSerial &serial;
		#elif defined(ARDUINO_ARCH_SAMD)
		Serial_ serial;
		#endif
};

void splitString(String, String, String[], int size);

extern SerialCiaoClass Ciao;

#else

class CiaoClass {
	public:
		void begin();

		CiaoData read( char*, char*, String );            // “rest”, ”hostname”, ”Stringone”,		
		CiaoData read( char*, char*, String, char*);      // “rest”, ”hostname”, ”Stringone”, ”method”

		CiaoData write( char*, char*, String );            // “rest”, ”hostname”, ”Stringone”,		
		CiaoData write( char*, char*, String, char*);      // “rest”, ”hostname”, ”Stringone”, ”method”
		
		void print(String str);
		void println(String str);
	
};
extern CiaoClass Ciao;

#endif


#endif /* CIAO_H_ */

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

#ifndef _CIAO_H_
#define _CIAO_H_

#include <Arduino.h>
#include <Stream.h>
#include "CiaoData.h"

#if defined(__AVR_ATmega32U4__)
#define BAUDRATE 250000
#define SERIAL_PORT_IN_USE Serial1
#elif defined(__SAMD21G18A__)
#define BAUDRATE 4000000
#define SERIAL_PORT_IN_USE SerialUSB
#else
#error CPU not yet supported
#endif

#define SERIAL_TRANSPORT typeof(SERIAL_PORT_IN_USE)

class CiaoClass {
	public:
		void begin();
		CiaoData read( String protocol, String param1 = "", String param2 = "", String param3 = "");
		CiaoData write( String protocol, String param1, String param2 = "", String param3 = "");
		CiaoData writeResponse( String protocol, String id, String param1="", String param2 = "", String param3 = "");
		CiaoData parse( String, String);
		void println(String log){};
		CiaoClass(Stream &_stream);
		void splitString(String, String, String[], int size);

	private:
		void dropAll();
		Stream &stream;
		bool started;

};

// This subclass uses a serial port Stream
class SerialCiaoClass : public CiaoClass {
	public:
		SerialCiaoClass(SERIAL_TRANSPORT &_serial)
			: CiaoClass(_serial), serial(_serial) {
			// Empty
		}
		void begin( unsigned long baudrate = BAUDRATE) {
			serial.begin(baudrate);
			CiaoClass::begin();
		}
	private:
		SERIAL_TRANSPORT &serial;
};

extern SerialCiaoClass Ciao;

#endif /* CIAO_H_ */

/*
****************************************************************************
* Copyright (c) 2015 Arduino srl. All right reserved.
*
* File : Ciao.cpp
* Date : 2015/07/03
* Revision : 0.0.1 $
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

#include "Ciao.h"

CiaoClass::CiaoClass(Stream &_stream) :
  stream(_stream), started(false) {
  // Empty
}

void CiaoClass::begin( bool CRC) {
	
	use_CRC = CRC;  //CRC flag
	String start;
	String stop;

  // Wait for U-boot to finish startup
	do {
		dropAll();
		delay(1000);
	}while (stream.available() > 0);

	stream.println("ciao;r;status");					//check the bridge python status	
	String status = stream.readStringUntil(end_trasmit);
	if(status == "1;running"){						
		do{												//kill a istance of the bridge.py
			stream.println("ciao;w;quit");
			stop = stream.readStringUntil(end_trasmit);
			delay(3000);
		}while(stop != "1;done");
    }
	
	do{ 
		stream.print(F("run-ciao\n"));				//start bridge python
		stream.readStringUntil(end_trasmit);
		delay(3000);
		stream.println("ciao;r;status");				//check if bridge python is running
		start = stream.readStringUntil(end_trasmit);
	}while (start != "1;running");
	
}

CiaoData CiaoClass::read( String connector) {

	CiaoData data;
	stream.println(connector + ";r");					// send read request 
	String message = stream.readStringUntil(end_trasmit);
	data = parse(message, ";");
	return data;
}

void CiaoClass::write(String connector, String param1, String param2 , String param3 ) {

	CiaoData data;
	if (param1 != "")									//serialize the parameter to be transmit
		data.serialize(param1);
	if (param2 != "")
		data.serialize(param2);
	if (param3 != "")
		data.serialize(param3);
	stream.println(connector + ";w;" + data.message()); 
	String mess_receive = stream.readStringUntil(end_trasmit);
	data = parse(mess_receive, ";");
	
}

void CiaoClass::writeResponse( String connector, String id, String param1, String param2 , String param3) {

	CiaoData data;
	if (param1 != "")
		data.serialize(param1);
	if (param2 != "")
		data.serialize(param2);
	if (param3 != "")
		data.serialize(param3);
	if(data.check_id(id)){
		stream.println(connector + ";wr;"+ id +";"+ data.message());
		String mess_receive = stream.readStringUntil(end_trasmit);
		data = parse(mess_receive, ";");
	}
}

CiaoData CiaoClass::parse(String message, String split){
	String status;
	CiaoData data;
	int statusIndex = message.indexOf(split);
	int messIndex = message.indexOf(split, statusIndex+1);
	status = message.substring(0, statusIndex);				//message status (0: no message; 1:data ready; -1:error)

	if(status == ready && message.substring(statusIndex+1, messIndex) != "done"){
		data.msg_split[0]=message.substring(statusIndex+1, messIndex);
		data.parseMessage(message.substring(messIndex+1));	//parsing data received
	}
	else{
		data.msg_split[0] = status;
		data.msg_split[2] = message.substring(statusIndex+1, messIndex);
	}
	return data;
}

void CiaoClass::dropAll() {
  while (stream.available() > 0) {
    stream.read();
  }
}

// Ciao instance
#ifdef __AVR_ATmega32U4__
// Leonardo variants (where HardwareSerial is Serial1)
SerialQiaoClass Ciao(Serial1);
#else
SerialQiaoClass Ciao(Serial);
#endif

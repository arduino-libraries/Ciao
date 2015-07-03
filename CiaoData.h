/*
****************************************************************************
* Copyright (c) 2015 Arduino srl. All right reserved.
*
* File : CiaoData.h
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

#include <Arduino.h>

class CiaoData {
	public:
		CiaoData(){
			serial_command="";
		}
		
		String get(int index){
			return msg_split[index];
		}

		void serialize(String param){
			if (serial_command == "")
				serial_command = param ;
			else
				serial_command = serial_command + String(data_separator) + param ;	
		}
		
		void split_command(String command, String split){		//fuction to split the digital/analog command (ex: digital/13/1)
			if(check_command(command,split)){		//if command is empty don't running the split
				int statusIndex = command.indexOf(split);
				int messIndex = command.indexOf(split, statusIndex+1);
				msg_split[0] = command.substring(0, statusIndex);
				msg_split[1] = command.substring(statusIndex+1, messIndex);
				if(messIndex != -1)
					msg_split[2] = command.substring(messIndex+1);
				else
					msg_split[2]="-1";
			}
		}
		
		String message(void){		
			return serial_command;		
		}
		
		void parseMessage(String command){
			int statusIndex = command.indexOf(data_separator);
			msg_split[1] = command.substring(0, statusIndex);
			msg_split[2] = command.substring(statusIndex+1);
		}
  
		bool check_id(String id){		//check if the id is valid
			if(id.length()> 20)
				return true;
			else
				return false;	
		}
		
		bool check_command(String command, String split){	
			if(command.indexOf(split) == -1)
				return false;
			else
				return true;	
		}
		
	private:
		String serial_command;
		char data_separator= (char)30;	
		
	public:
		String msg_split[3];
		
};



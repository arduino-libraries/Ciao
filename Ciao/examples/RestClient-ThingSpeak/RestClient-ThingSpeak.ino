#include <Wire.h>
#include <Ciao.h>

/* 

This example show the interaction between the Ciao Library and the Thingspeak Cloud. 
To run the example you need to register an account on thingspeak.com and create a 
new channel by clicking "Channels" section in the website (Channels -> My Channels -> New Channel). 
In the new channel you need to add two fields. The first one refers to the humidity data and the second one to the temperature value.
After that, replace the "XXXXXXXXX" value of APIKEY_THINGSPEAK with "Write API key" value reported in the API Keys section of the channel. 

*/

#define CONNECTOR     "rest" 
#define SERVER_ADDR   "api.thingspeak.com"

#define APIKEY_THINGSPEAK  "XXXXXXXXXXXXX"

void setup() {
  Wifi.begin(); // INIT WIFI
  Wifi.connect("SSID","PASSWORD"); // CONNECT TO HOME AP (essid,pwd)

  Ciao.begin(); // CIAO INIT
}

short hum = 60;
short temp = 22;

void loop() {
  
  if(Wifi.connected()){
    
    String stringoneW = "/update?api_key=";
    stringoneW += APIKEY_THINGSPEAK;
    stringoneW += "&field1=";
    stringoneW += String(hum);
    stringoneW += "&field2=";
    stringoneW += String(temp);

    Wifi.println("Send data on ThingSpeak Channel"); 
      
    CiaoData data = Ciao.write(CONNECTOR, SERVER_ADDR, stringoneW);

    if ( atoi( data.get(1) ) > 0 ){
      Wifi.println( "State: " + String (data.get(1)) );
      Wifi.println( "Response: " + String (data.get(2)) );
    }
    else{ 
      Wifi.println ("Write Error");
    }    
  }
 
  delay(30000); // Thinkspeak policy

}  

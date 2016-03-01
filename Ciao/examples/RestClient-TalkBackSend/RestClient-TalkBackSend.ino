#include <Wire.h>
#include <Ciao.h>

/* 

This example show the interaction between the Ciao Library and the Thingspeak Cloud. 
To run the example you need to register an account on thingspeak.com.
After that, you need to create a new channel and a new talkback app.
To create a new channel click the "Channels" section in the website (Channels -> My Channels -> New Channel).
To create a new talkback click the "Apps" section in the website (Apps -> TalkBack -> New TalkBack). 
Replace the APIKEY_TALKBACK and ID_TALKBACK values with the values reported in the API section of the site. 

*/

#define CONNECTOR     "rest" 
#define SERVER_ADDR   "api.thingspeak.com"

#define APIKEY_TALKBACK     "XXXXXXXXXXXXXX"
#define ID_TALKBACK         "XXXX"


void setup() {
  Wifi.begin(); // INIT WIFI
  Wifi.connect("SSID","PASSWORD"); // CONNECT TO HOME AP (essid,pwd)

  Ciao.begin(); // CIAO INIT
}

String cmd = "D13_ON";

void loop() {
  
  if(Wifi.connected()){
      
      String stringoneL = "/talkbacks/";
    	stringoneL += ID_TALKBACK;
    	stringoneL += "/commands?api_key=";
    	stringoneL += APIKEY_TALKBACK;
    	stringoneL += "&command_string=";
    	stringoneL += cmd;

      Wifi.println("Write cmd on TalkBack Queue"); 
      CiaoData data = Ciao.write(CONNECTOR, SERVER_ADDR, stringoneL,"POST");
  
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
    

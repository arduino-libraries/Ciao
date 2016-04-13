/*

 This sketch uses the restserver connector receive rest calls. It allows access to
 the analog and digital pin of the board via rest calls.

 supported boards: Yun,Tian.

 Possible commands to send from the xmpp client:

 * "/arduino/digital/PIN"       -> to read a digital PIN
 * "/arduino/digital/PIN/VALUE" -> to write a digital PIN (VALUE: 1/0)
 * "/arduino/analog/PIN/VALUE"  -> to write in a PWM PIN(VALUE range: 0 - 255);
 * "/arduino/analog/PIN"        -> to read a analog PIN
 * "/arduino/servo/PIN/VALUE"   -> to write angle in a SERVO PIN(VALUE range: 0 - 180);
 * "/arduino/mode/PIN/VALUE"    -> to set the PIN mode (VALUE: input / output)

 Example:
 "/arduino/mode/13/output" -> pinMode(13, OUTPUT)
 "/arduino/digital/13/1"     -> digitalWrite(13, HIGH)


 NOTE: be sure to activate and configure restserver connector on Linino OS
  http://labs.arduino.org/Ciao

 created September 2015
 by andrea[at]arduino[dot]org

 */

#include <Ciao.h>
#include <Servo.h>

Servo servo;

void setup() {

  Ciao.begin();
}

void loop() {

  CiaoData data = Ciao.read("restserver");
  if(!data.isEmpty()){
    String id = data.get(0);
    String sender = data.get(1);
    String message = data.get(2);

    message.toUpperCase();

    String command[3];

    splitString(message,"/",command,3);
    execute(command,id);

  }
}

void execute(String cmd[], String id) {

  if (cmd[0] == "DIGITAL") {
    digitalCommand(cmd,id);
  }
  else if (cmd[0] == "ANALOG") {
    analogCommand(cmd,id);
  }
  else if (cmd[0] == "SERVO") {
    servoCommand(cmd,id);
  }
  else if (cmd[0] == "MODE") {
    setMode(cmd,id);
  }
  else
    Ciao.writeResponse("restserver",id,"sorry, i don't understand :(");
}

void servoCommand(String cmd[], String id){
   int pin, value;

  pin = (cmd[1]).toInt();

  if (cmd[2] != "-1") {
    value = (cmd[2]).toInt();
    if(value <= 180 && value >=0){
      servo.attach(pin);
      servo.write(value);
      Ciao.writeResponse("restserver",id,"Servo D"+String(pin)+" set to "+String(value)+" degrees");
    }
    else
      Ciao.writeResponse("restserver",id,"Invalid angle value");
  }
  else
    Ciao.writeResponse("restserver",id,"Invalid command");
}

void digitalCommand(String cmd[], String id) {
  int pin, value;

  pin = (cmd[1]).toInt();

  if (cmd[2] != "-1") {
    value = (cmd[2]).toInt();
    digitalWrite(pin, value);
    if (value == 1)
      Ciao.writeResponse("restserver",id,"Pin D"+String(pin)+" ON");
    else if(value == 0)
      Ciao.writeResponse("restserver",id,"Pin D"+String(pin)+" OFF");
  }
  else if (cmd[2] == "-1") {
    value = digitalRead(pin);
    Ciao.writeResponse("restserver",id,"D"+String(pin)+" value = "+String(value));
  }
}

void analogCommand(String cmd[], String id) {
  int pin, value;

  pin = (cmd[1]).toInt();

  if (cmd[2] != "-1") {
    value =(cmd[2]).toInt();
    analogWrite(pin, value);
    Ciao.writeResponse("restserver",id,"D"+String(pin)+" set to analog");
  }
  else if (cmd[2] == "-1") {
    value = analogRead(pin);
    Ciao.writeResponse("restserver",id,"A"+String(pin)+" value = "+String(value));
  }
}

void setMode(String cmd[], String id) {
  int pin;

  pin = (cmd[1]).toInt();

  if (cmd[2] == "INPUT") {
    pinMode(pin, INPUT);
    Ciao.writeResponse("restserver",id," pin D"+String(pin)+" set in INPUT mode");
    return;
  }

  if (cmd[2] == "OUTPUT") {
    pinMode(pin, OUTPUT);
    Ciao.writeResponse("restserver",id," pin D"+String(pin)+" set in OUTPUT mode");
    return;
  }
  Ciao.writeResponse("restserver",id,"invalid mode");
}

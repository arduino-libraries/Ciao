#include <Wire.h>
#include <Ciao.h>

#define BAUD 9600
SC16IS750 espSerial1 = SC16IS750(SC16IS750_PROTOCOL_I2C, SC16IS750_ADDRESS_AA);

void setup()
{
  Serial.begin(BAUD);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  espSerial1.begin(BAUD);

};

void loop()
{
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    espSerial1.write(inChar);
  }

  while (espSerial1.available()) {
    char inChar = (char)espSerial1.read();
    Serial.write(inChar);
  }

};


#include "BlueSmirf_HID.h"

#include "Arduino.h"


BlueSmirf_HID::BlueSmirf_HID()
{

}

void BlueSmirf_HID::setup()
{
  Serial.begin(115200);

  Serial.print("$$$"); //Enter command mode. No end of line.
  delay(1000);
  Serial.println("SN,N64_bluetooth"); //set name of device
  delay(1000);
  Serial.println("SH,0210"); //switch to game pad mode
  delay(1000);
  Serial.println("C"); //reconnect
  delay(1000);
  Serial.println("---"); //Exit command mode
}

void BlueSmirf_HID::sendUpdate(char stick1_x, char stick1_y, char stick2_x, char stick2_y, byte buttons1, byte buttons2)
{
  Serial.write(0xFD); //RAW report
  Serial.write(6); //6 bytes
  Serial.write(stick1_x);
  Serial.write(stick1_y);
  Serial.write(stick2_x);
  Serial.write(stick2_y);
  Serial.write(buttons1);
  Serial.write(buttons2);
}

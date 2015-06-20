#include "N64_bluetooth_HID.h"

N64_bluetooth_HID::N64_bluetooth_HID() : controller()
{

}

void N64_bluetooth_HID::setup()
{
  if (Serial)
  {
    Serial.print("$$$"); //Enter command mode. No end of line.
    delay(1000);
    Serial.println("SN,N64_bluetooth"); //set name of device
    delay(1000);
    Serial.println("SH,0210"); //switch to game pad mode
    delay(1000);
    Serial.println("C"); //reconnect
    delay(5000);
    Serial.println("---"); //Exit command mode
  }
}

void N64_bluetooth_HID::sendUpdate(N64_status status)
{
  //minus 128 cannot have its sign changed (kinda like zero)
  if (status.stick_y == -128)
    status.stick_y = -127;

  //invert y-axis
  status.stick_y = -status.stick_y;

  Serial.write(0xFD);
  Serial.write(6);
  Serial.write(status.stick_x);
  Serial.write(status.stick_y);
  Serial.write(0);
  Serial.write(0);
  Serial.write(status.data1);
  Serial.write(status.data2);
}

void N64_bluetooth_HID::updateController()
{
  controller.sendStatusByte();
  controller.receiveStatus();
}

void N64_bluetooth_HID::sendBluetooth()
{
  sendUpdate(controller.getStatus());
}

#include "N64_controller.h"
#include "BlueSmirf_HID.h"

N64_controller controller;
N64_status status, oldStatus;
BlueSmirf_HID bluetooth;

void setup()
{
  bluetooth.setup();

} //setup

void loop()
{
  //byte sendBuf[] = { COMMAND_STATUS };

  noInterrupts();
  //hid.updateController();
  //controller.N64_send(sendBuf, sizeof sendBuf);
  controller.sendStatusByte();
  controller.N64_get((byte*) &status, sizeof status);
  //controller.receiveStatus();
  interrupts();

  //status = controller.getStatus();
  
  if(status.stick_y == -128)
    status.stick_y = -127;

  //hid.sendBluetooth();
  bluetooth.sendUpdate(status.stick_x, -status.stick_y, 0, 0, status.data1, status.data2);

  /*
   if (memcmp (&status, &oldStatus, sizeof status) != 0)
   {
     printN64status(status);
     oldStatus = status;
   }
    */

  delay(100);

} //loop

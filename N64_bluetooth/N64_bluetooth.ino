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
  //controller.N64_send(sendBuf, sizeof sendBuf);
  controller.sendStatusByte();
  controller.N64_get((byte*) &status, sizeof status);
  interrupts();

  if (status.stick_y == -128) //we need to invert the y-axis, but due to the way integers are stored, -128 is like 0 and cannot change its sign
    status.stick_y = -127;

  if (memcmp (&status, &oldStatus, sizeof status) != 0) //If the status has changed
  {
    bluetooth.sendUpdate(status.stick_x, -status.stick_y, 0, 0, status.data1, status.data2);
    //printN64status(status);
    oldStatus = status;
  }

  delay(100);

} //loop

#include "N64_Controller.h"
#include "BlueSmirf_HID.h"

N64_Controller controller;
N64_Status status, old_status;
BlueSmirf_HID bluetooth;
byte command_status[] = { COMMAND_STATUS };

void setup()
{
  bluetooth.setup();

} //setup

void loop()
{

  noInterrupts();
  //controller.sendStatusByte(); //this function does the same as the functions below, but its timings are hardcoded
  controller.N64_send(command_status, sizeof command_status); //this is how we send the status command to the controller
  controller.N64_get((byte*) &status, sizeof status); //this is how we receive the status response
  interrupts();

  if (status.stick_y == -128) //we need to invert the y-axis, but due to the way integers are represented, -128 is like 0 and we cannot change its sign
    status.stick_y = -127;

  if (memcmp (&status, &old_status, sizeof status) != 0) //If the status has changed
  {
    bluetooth.sendUpdate(status.stick_x, -status.stick_y, 0, 0, status.buttons1, status.buttons2);
    //printN64status(status);
    old_status = status;
  }

  delay(50); //check controller 20 times per second

} //loop

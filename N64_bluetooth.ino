#include "N64_Controller.h"
#include "BlueSmirf_HID.h"


//Comment the following line to disable bluetooth. Do this to test the N64 controller with Serial Monitor. Physically disconnect the BlueSmirf module.
#define BLUETOOTH_ENABLE

//This is the speed of the serial connection when Bluetooth is disabled.
#define SERIAL_BITRATE 115200


N64_Controller controller;
N64_Status status, old_status;
byte command_status[] = { COMMAND_STATUS };

#ifdef BLUETOOTH_ENABLE
BlueSmirf_HID bluetooth;
#endif


void setup()
{
#ifdef BLUETOOTH_ENABLE
  bluetooth.setup();
#else
  Serial.begin(SERIAL_BITRATE);
#endif

} //setup

void loop()
{

  noInterrupts(); //disable interrupts so they don't interfere with the N64 communication protocol
  controller.N64_send(command_status, sizeof command_status); //this is how we send the status command byte to the controller
  controller.N64_get((byte*) &status, sizeof status); //this is how we receive the status response from the controller
  interrupts();

  if (status.stick_y == -128) //we need to invert the y-axis, but due to the way integers are represented, -128 is like 0 and we cannot change its sign
    status.stick_y = -127;

  if (memcmp (&status, &old_status, sizeof status) != 0) //If the status has changed
  {
#ifdef BLUETOOTH_ENABLE
    bluetooth.sendUpdate(status.stick_x, -status.stick_y, 0, 0, status.buttons1, status.buttons2);
#else
    printN64status(status);
#endif
    old_status = status;
  }

  delay(50); //check controller 20 times per second

} //loop

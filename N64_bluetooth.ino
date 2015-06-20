#include "N64_bluetooth_HID.h"

//N64_controller controller;
//N64_status status, oldStatus;
N64_bluetooth_HID hid;

void setup()
{
   Serial.begin(115200);  
   hid.setup();
 
} //setup

void loop()
{ 
  noInterrupts();  
  hid.loop();
  //byte sendBuf[] = { COMMAND_STATUS };
  //controller.N64_send(sendBuf, sizeof sendBuf); 
  //controller.sendStatusByte();
  //controller.N64_get((byte*) &status, sizeof status);
  //status = controller.getStatus();
  interrupts();
  
 /*
  if (memcmp (&status, &oldStatus, sizeof status) != 0)
  { 
    printN64status(status);
    oldStatus = status;
  }
   */
   
   delay(100);  
 
} //loop

//#include "N64_controller.h"
#include "N64_bluetooth_HID.h"

N64_controller controller;
N64_status status, oldStatus;
N64_bluetooth_HID hid;

void setup()
{
 
   //delay(5000);
  
   Serial.begin(115200);  
   hid.setup();
 
 /*
   
   
   */
} //setup

void loop()
{ 
 // Serial.println("loop");


  noInterrupts();  
  hid.loop();
//  byte sendBuf[] = { 0x01 };
  //controller.N64_send(sendBuf, sizeof sendBuf); 
//  controller.sendStatusByte();
  //N64_status status; 
  //controller.N64_get((byte*) &status, sizeof status);
 // status = controller.getStatus();
  interrupts();
  
  delay(100);
  
  
//  static N64_status oldStatus;
 /*
  if (memcmp (&status, &oldStatus, sizeof status) != 0)
  { 
    printN64status(status);
    oldStatus = status;
  }
    
    delay(200);
   
   */
  
 // delay(100);  
 
} //loop

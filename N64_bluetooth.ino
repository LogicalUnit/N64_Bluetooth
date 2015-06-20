#include "N64_controller.h"

N64_controller controller;
N64_status status, oldStatus;

void setup()
{
 
   //delay(5000);
  
   Serial.begin(115200);  
 
 /*
   Serial.print("$$$"); //Enter command mode. No end of line.
   delay(1000);
   Serial.println("SN,N64_bluetooth"); //set name of device
   delay(1000);
   Serial.println("SH,0210"); //switch to game pad mode
   delay(1000);
   Serial.println("C"); //reconnect
   delay(5000);
   Serial.println("---"); //Exit command mode
   
   */
} //setup

void loop()
{ 
 // Serial.println("loop");


  noInterrupts();  
//  byte sendBuf[] = { 0x01 };
  //controller.N64_send(sendBuf, sizeof sendBuf); 
  controller.sendStatusByte();
  //N64_status status; 
  //controller.N64_get((byte*) &status, sizeof status);
  status = controller.getStatus();
  interrupts();

//  delay(1000);
  
  
//  static N64_status oldStatus;
 
  if (memcmp (&status, &oldStatus, sizeof status) != 0)
  { 
    printN64status(status);
    oldStatus = status;
  }
    
    delay(200);
   
   //minus 128 cannot have its sign changed (kinda like zero)
  /*
  if(status.stick_y == -128)
    status.stick_y = -127;

  //invert y-axis
  status.stick_y = -status.stick_y;     
  
  Serial.write(0xFD);
  Serial.write(6);
  Serial.write((int)status.stick_x);
  Serial.write((int)status.stick_y);
  Serial.write(0);
  Serial.write(0);
  Serial.write(status.data1);
  Serial.write(status.data2);  
  
  delay(100);  
  */
} //loop

#include "N64_controller.h"

N64_controller controller;
N64_status status;

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
  byte sendBuf[] = { 0x01 };
  controller.N64_send(sendBuf, sizeof sendBuf); 
  N64_status status; 
  controller.N64_get((byte*) &status, sizeof status);
  //controller.sendStatusByte();
  //status = controller.getStatus();
  interrupts();

//  delay(1000);
  
  
  static N64_status oldStatus;
 
  if (memcmp (&status, &oldStatus, sizeof status) != 0)
    {
    if (status.stick_x || oldStatus.stick_x)
      {
      Serial.print ("X: ");
      Serial.print ((int) status.stick_x);
      Serial.print (" ");
      }
    if (status.stick_y || oldStatus.stick_y)
      {
      Serial.print ("Y: ");
      Serial.print ((int) status.stick_y);
      Serial.print (" ");
      }     
    oldStatus = status;
    if (status.data2 &  BUTTON_C_RIGHT)
      Serial.print (F("C right "));
    if (status.data2 &  BUTTON_C_LEFT)
      Serial.print (F("C left "));
    if (status.data2 &  BUTTON_C_UP)
      Serial.print (F("C up "));
    if (status.data2 &  BUTTON_C_DOWN)
      Serial.print (F("C down "));
    if (status.data2 &  BUTTON_R)
      Serial.print (F("R "));
    if (status.data2 &  BUTTON_L)
      Serial.print (F("L "));    
    if (status.data1 &  BUTTON_D_RIGHT)
      Serial.print (F("D right "));
    if (status.data1 &  BUTTON_D_LEFT)
      Serial.print (F("D left "));
    if (status.data1 &  BUTTON_D_UP)
      Serial.print (F("D up "));
    if (status.data1 &  BUTTON_D_DOWN)
      Serial.print (F("D down "));
    if (status.data1 &  BUTTON_START)
      Serial.print (F("Start "));
    if (status.data1 &  BUTTON_Z)
      Serial.print (F("Z "));
    if (status.data1 &  BUTTON_B)
      Serial.print (F("B "));
    if (status.data1 &  BUTTON_A)
      Serial.print (F("A "));
    
    if (status.data1 == 0 && status.data2 == 0)
      Serial.print (F("(no buttons)"));
    Serial.println ();
    Serial.flush ();
 
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

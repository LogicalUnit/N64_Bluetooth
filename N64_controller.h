/*





*/

#ifndef N64_controller_h
#define N64_controller_h

#include "Arduino.h"

// status data1:
const byte BUTTON_D_RIGHT = 0x01;
const byte BUTTON_D_LEFT = 0x02;
const byte BUTTON_D_DOWN = 0x04;
const byte BUTTON_D_UP = 0x08;
const byte BUTTON_START = 0x10;
const byte BUTTON_Z = 0x20;
const byte BUTTON_B = 0x40;
const byte BUTTON_A = 0x80;

// status data2:
const byte BUTTON_C_RIGHT = 0x01;
const byte BUTTON_C_LEFT = 0x02;
const byte BUTTON_C_DOWN = 0x04;
const byte BUTTON_C_UP = 0x08;
const byte BUTTON_R = 0x10;
const byte BUTTON_L = 0x20;

typedef struct {
    byte data1;
    byte data2;
    char stick_x;
    char stick_y;
} N64_status;


class N64_controller
{
  public:
    N64_controller();
    
    void sendStatusByte();
    N64_status getStatus();
    
    void N64_send (byte * output, byte length);
    void N64_get(byte * output, byte length);
    
  private:
   // N64_status status;
};

#endif

/*
  N64_controller
  John Crain Welsby aka LogicalUnit, john.welsby@gmail.com
  Special thanks to Nick Gammon, Andrew Brown, Peter Den Hartog
  Sends and receives data to a Nintendo 64 controller
*/

#ifndef N64_Controller_H
#define N64_Controller_H

typedef unsigned char byte;

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

//Controller commands
const byte COMMAND_IDENTIFY = 0x00;
const byte COMMAND_STATUS = 0x01;

typedef struct {
  byte data1;
  byte data2;
  char stick_x;
  char stick_y;
} N64_status;


void printN64status(N64_status status);

class N64_controller
{
  public:
    N64_controller();

    void sendStatusByte();

    void N64_send (byte * output, byte length);
    void N64_get(byte * output, byte length);

};

#endif

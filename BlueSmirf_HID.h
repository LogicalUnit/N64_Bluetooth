/*
  BlueSmirf_HID
  John Crain Welsby aka LogicalUnit, john.welsby@gmail.com
  Use a SparkFun BlueSmirf HID module as a bluetooth gamepad device
*/

#ifndef BlueSmirf_HID_H
#define BlueSmirf_HID_H

typedef unsigned char byte;

class BlueSmirf_HID
{
  public:
    BlueSmirf_HID();
    void setup();
    void sendUpdate(char stick1_x, char stick1_y, char stick2_x, char stick2_y, byte buttons1, byte buttons2);
};


#endif

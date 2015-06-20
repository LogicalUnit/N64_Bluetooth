/*



*/

#ifndef N64_bluetooth_HID_h
#define N64_bluetooth_HID_h

#include "N64_controller.h"

class N64_bluetooth_HID
{
  public:
    N64_bluetooth_HID();
    void setup();
    void loop();
  
  private:
    N64_controller controller;    
    void sendUpdate(N64_status status);
};


#endif

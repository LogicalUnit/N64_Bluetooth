#include "N64_controller.h"

#include <avr/wdt.h>

#define N64_PIN 2
#define N64_PIN_DIR DDRD

// these two macros set arduino pin 2 to input or output, which with an
// external 1K pull-up resistor to the 3.3V rail, is like pulling it high or
// low.  These operations translate to 1 op code, which takes 2 cycles
#define N64_HIGH    N64_PIN_DIR &= ~0x04
#define N64_LOW     N64_PIN_DIR |= 0x04
#define N64_QUERY  (PIND & 0x04)

#define nop asm volatile ("nop\n\t")

N64_controller::N64_controller()
{
  pinMode (N64_PIN, INPUT);  // do not make OUTPUT or INPUT_PULLUP! This will fry the controller!
  //status = 0; 
}


/*
  Although we could write logic to send an arbitrary byte to the controller,
  in practice we will only send 0x01 which is a request for input
*/

void N64_controller::sendStatusByte()
{
  //bit 1 (0)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop; 
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  N64_HIGH;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  
  //bit 2 (0)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop; 
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  N64_HIGH;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  
  //bit 3 (0)
  N64_LOW;        
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop; 
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  N64_HIGH;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  
  //bit 4 (0)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop; 
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  N64_HIGH;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  
  //bit 5 (0)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop; 
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  N64_HIGH;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  
  //bit 6 (0)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop; 
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  N64_HIGH;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  
  //bit 7 (0)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop; 
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  N64_HIGH;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  
  //bit 8 (1)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop;
  N64_HIGH;   
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; 
  
  //stop bit (1)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop;
  N64_HIGH;   
/*  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop;*/
}

//N64_status status;

N64_status N64_controller::getStatus()
{
 //N64_status status; 
 N64_get((byte *) &status, sizeof status);
/* Serial.println(status.data1);
 Serial.println(status.data2);
 Serial.println(status.stick_x);
 Serial.println(status.stick_y);*/
 return status; 
}

void N64_controller::N64_send(byte * output, byte length)
{
   byte bitOn;
   byte bits;
 
   while (length--)
    {
    PINB = bit (5); // toggle D13 
    byte currentByte = *output++;
    
    for (bits = 0; bits < 8; bits++)  // 5 cycles if staying in loop
      {
      bitOn = currentByte & 0x80;  // 2 cycles
      currentByte <<= 1;   // 1 cycle
      
      // ------- low for 1 uS
      PINB = bit (3); // toggle D11
      N64_LOW; // start bit
      
      // we want 14 but subtract 2 for toggling the LED
      // and another 2 for the decision below
  #if WANT_8MHZ
      nop; nop; nop; // 3
  #else
      nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; // 11
  #endif
      // -------------------
      
      // -------low or high for 2 uS
      if (bitOn)  // test bit, 1 if high, 2 if low
        {
        N64_HIGH; // go high for one  - 2 cycles
        }
      else          
        {
        N64_LOW; //  stay low for zero - 2 cycles
        nop;  // compensate for branch  - 1 cycle
        }
  #if WANT_8MHZ
      nop; nop; nop; nop; nop; nop; nop; nop;   // 8
      nop; nop; // 10
  #else
      nop; nop; nop; nop; nop; nop; nop; nop;   // 8
      nop; nop; nop; nop; nop; nop; nop; nop;   // 16
      nop; nop; nop; nop; nop; nop; nop; nop;   // 24
      nop; nop; // 26
  #endif
  
      // -------------------
  
      // ------- high for 1 uS
      N64_HIGH; //  stop bit must be high
      
      // we want 14 but subtract 7 because of loop overhead
  #if WANT_8MHZ
  #else    
      nop; nop; nop; nop; nop; nop; nop; nop;   // 7
  #endif
  
      // -------------------
      }  // end of each bit

    }
    
  // console stop bit - low for 1 uS then high
  N64_LOW; // start bit (2 cycles)

#if WANT_8MHZ
  nop; nop; nop; nop; nop; nop;   // 6
#else    
  nop; nop; nop; nop; nop; nop; nop; nop;   // 8
  nop; nop; nop; nop; nop; nop;   // 14 
#endif

  N64_HIGH; 

}

void N64_controller::N64_get(byte * output, byte length)
{
  byte bits;

//  Serial.println("get");
  wdt_reset();  // pat the dog
  wdt_enable(WDTO_30MS);

  while (length--)
    {
     PINB = bit (5); // toggle D13
    for (bits = 0; bits < 8; bits++)
      {
      // wait for start bit
      while (N64_QUERY) { }            
      
      PINB = bit (3); // toggle D11
      
      // wait for 2 uS then check the line
      nop; nop; nop; nop; nop; nop; nop; nop;   
      nop; nop; nop; nop; nop; nop; nop; nop;
      nop; nop; nop; nop; nop; nop; nop; nop; 
      nop; nop; nop; nop; 
      
       PINB = bit (4); // toggle D12
        
      // shift left as the most significant bit comes first
      *output <<= 1;
      // or this bit in
      *output |= N64_QUERY != 0;
      
      // wait for line to go high again
      while (!N64_QUERY) { }
        
      }  // end of for each bit
    output++;
    }  // end of while each byte
 
  // wait for stop bit
  while (N64_QUERY) { }
  // then other end should let line go high
  while (!N64_QUERY) { }

  wdt_disable();  // disable watchdog
}

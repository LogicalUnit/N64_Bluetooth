#include <avr/wdt.h>

#define N64_PIN 2
#define N64_PIN_DIR DDRD

// these two macros set arduino pin 2 to input or output, which with an
// external 1K pull-up resistor to the 3.3V rail, is like pulling it high or
// low.  These operations translate to 1 op code, which takes 2 cycles
#define N64_HIGH    N64_PIN_DIR &= ~0x04
#define N64_LOW     N64_PIN_DIR |= 0x04
#define N64_QUERY  (PIND & 0x04) != 0

#define nop asm volatile ("nop\n\t")

#define LOGIC_16MHZ true
#define WANT_8MHZ false

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


void N64_send (byte * output, byte length)
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

/*
  Although we could write logic to send an arbitrary byte to the controller,
  in practice we will only send 0x01 which is a request for input
*/
void N64_send_poll_byte()
{
  //bit 1 (0)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop;  
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  N64_HIGH;
  nop; nop; nop; nop; nop; nop;
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  
  //bit 2 (0)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop;  
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  N64_HIGH;
  nop; nop; nop; nop; nop; nop;
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  
  //bit 3 (0)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop;  
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  N64_HIGH;
  nop; nop; nop; nop; nop; nop;
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  
  //bit 4 (0)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop;  
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  N64_HIGH;
  nop; nop; nop; nop; nop; nop;
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  
  //bit 5 (0)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop;  
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  N64_HIGH;
  nop; nop; nop; nop; nop; nop;
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  
  //bit 6 (0)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop;  
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  N64_HIGH;
  nop; nop; nop; nop; nop; nop;
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  
  //bit 7 (0)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop;  
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  N64_HIGH;
  nop; nop; nop; nop; nop; nop;
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  
  //bit 8 (1)
  N64_LOW;    
  nop; nop; nop; nop; nop; nop;  
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  N64_HIGH;   
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop;
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  
  //stop bit
  N64_LOW;
  nop; nop; nop; nop; nop; nop;
  #ifdef LOGIC_16MHZ
  nop; nop; nop; nop; nop; nop; nop; nop;
  #endif
  N64_HIGH;    
} //N64_send_poll_byte()

void N64_get(byte * output, byte length)
{
  byte bits;

  wdt_reset();  // pat the dog
  wdt_enable(WDTO_30MS);

  while (length--)
    {
    for (bits = 0; bits < 8; bits++)
      {
      // wait for start bit
      while (N64_QUERY) { }            
      
      // wait for 2 uS then check the line

      nop; nop; nop; nop; nop; nop; nop; nop;   
      nop; nop; nop; nop; nop; nop;
      
#ifdef LOGIC_16MHZ      
      nop; nop; nop; nop; nop; nop; nop; nop; 
      nop; nop; nop; nop; nop; nop; nop; nop;  
#endif
        
      // shift left as the most significant bit comes first
      *output <<= 1;
      // or this bit in
      *output |= N64_QUERY;
      
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
}  // end of N64_get


void setup()
{
  pinMode (N64_PIN, INPUT);  // do not make OUTPUT or INPUT_PULLUP! This will fry the controller!
  delay(5000);
  
   Serial.begin(115200);  
//   Serial.println("Starting. . .");
 
   Serial.print("$$$"); //Enter command mode. No end of line.
   delay(1000);
   Serial.println("SN,N64_bluetooth"); //set name of device
   delay(1000);
   Serial.println("SH,0210"); //switch to game pad mode
   delay(1000);
   Serial.println("C"); //reconnect
   delay(5000);
   Serial.println("---"); //Exit command mode
} //setup

void loop()
{ 
  N64_status status;
 byte command = 0x01;
 
  noInterrupts();  
  N64_send_poll_byte();
//  N64_send(command, 1);
  N64_get((byte *) &status, sizeof status);   
  interrupts();
  
/*   static N64_status oldStatus;
 
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
    delay(200);*/
    
   //minus 128 cannot have its sign changed (kinda like zero)
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
} //loop

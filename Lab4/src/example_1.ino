// CPE 301 - REGISTER-LEVEL Blink Example
// Written By Frank Mascarich, Spring 2018
//            Shawn Ray, Fall 2022

// Define Port B Register Pointers
volatile unsigned char* port_b = (unsigned char*) 0x25; 
volatile unsigned char* port_h = (unsigned char*) 0x102; 
volatile unsigned char* ddr_h  = (unsigned char*) 0x101; 
volatile unsigned char* ddr_b  = (unsigned char*) 0x24; 
volatile unsigned char* pin_b  = (unsigned char*) 0x23; 

#define BV(x) (1<<x)

void setup() 
{
  //set PB7 to OUTPUT
  *ddr_b |= 0x80;
}

void loop() 
{
  // drive PB7 HIGH
  *port_b |= 0x80;
  // wait 500ms
  //__asm__("nop\n\t");
  delay(500);
  // drive PB7 LOW
  *port_b &= 0x7F;
  // wait 500ms
  delay(500);
}

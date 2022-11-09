// Part 5
// Abigail Dolan & Keaton Clark
volatile unsigned char* port_k = (unsigned char*) 0x108; 
volatile unsigned char* ddr_k  = (unsigned char*) 0x107; 
volatile unsigned char* pin_k  = (unsigned char*) 0x106; 
volatile unsigned char* ddr_d  = (unsigned char*) 0x2A; 
volatile unsigned char* port_d = (unsigned char*) 0x2B; 
volatile unsigned char* ddr_e  = (unsigned char*) 0x2D; 
volatile unsigned char* port_e = (unsigned char*) 0x2E; 

#define BV(x) (1<<x)

void setup() 
{
  *port_k |= BV(2);
  *ddr_d |= BV(0);
  *ddr_e |= BV(3);
}

void loop() 
{
	if(!(*pin_k & BV(2))) {
		*port_d |= BV(0);
		*port_e &= !BV(3);
	} else {
		*port_d &= !BV(0);
		*port_e |= BV(3);
	}
}

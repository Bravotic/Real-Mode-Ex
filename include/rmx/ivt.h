/***
 * Real Mode Ex
 * Lisenced under LGPL 3.0
 * 
 * Contributors:
 * Collin McKinley <collinm@collinm.xyz>
 *
 * ivt.h -- Basic setup for interupt vector
 *
 * rmx_call_int(uint32_t intnum) -- calls interupt with intnum
 * if HLE is enabled, will attempt to call the HLE function before calling the 
 * emulated function
 ***/


extern void rmx_call_int(unsigned char i);

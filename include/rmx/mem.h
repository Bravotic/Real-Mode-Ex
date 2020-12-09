/***
 * Real Mode Ex
 * Lisenced under LGPL 3.0
 * 
 * Contributors:
 * Collin McKinley <collinm@collinm.xyz>
 *
 * mem.h -- Basic setup for virtual memory used by the RMX VM
 *
 * rmx_set_mem( uint32_t size ) -- creates memory buffer with 'size'
 * as the size
 *
 * rmx_set_mem_default() -- creates memory buffer with 1MB size
 ***/


extern unsigned char* mem;

extern void rmx_set_mem(unsigned int);
extern void rmx_set_mem_default();


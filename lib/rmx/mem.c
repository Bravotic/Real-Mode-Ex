/***
 * Real Mode Ex
 * Lisenced under LGPL 3.0
 * 
 * Contributors:
 * Collin McKinley <collinm@collinm.xyz>
 *
 * mem.c -- Basic setup for virtual memory used by the RMX VM
 *
 * set_mem( uint32_t size ) -- creates memory buffer with 'size'
 * as the size
 *
 * set_mem_default() -- creates memory buffer with 1MB size
 ***/

/***
 * TODO
 *
 * 0x0a000 is graphics memory, implement that as soon as we get proper mode
 * 0x13 working
 ***/
#include <rmx_types.h>

#ifndef _RMX_BAREMETAL
#include <stdlib.h>

byte_t* mem;

void rmx_set_mem(unsigned int size){
    mem = (byte_t*) malloc(size);
}

void rmx_set_mem_default(){
    mem = (byte_t*) malloc(1000000);
}
#else

byte_t mem[1000000] = { 0x00 };

void rmx_set_mem(unsigned int size){
    /* Do nothing */
}
void rmx_set_mem_default(){
    /* Do nothing */
}
#endif


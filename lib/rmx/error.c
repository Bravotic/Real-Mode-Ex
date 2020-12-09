/***
 * Real Mode Ex
 * Lisenced under LGPL 3.0
 * 
 * Contributors:
 * Collin McKinley <collinm@collinm.xyz>
 *
 * error.c -- Basic error handling with room to expand
 *
 * rmx_error_handler(const char* reason, unsigned char opcode) -- function called when error is triggered
 * 
 * rmx_simple_error_handler(const char* reason, unsigned char d) -- The default
 * error handler.  Very simplistic but works.
 *
 * rmx_register_error_handler(void (*function)() ) -- Sets the function as the 
 * error handler.
 *
 ***/

#include <rmx_types.h>

void (*rmx_error_handler)(const char*, unsigned char) = NULL;

#ifndef _RMX_BAREMETAL
#include <stdio.h>
void rmx_simple_error_handler(const char* r, unsigned char d){
    printf("RMX_ERROR: %s at 0x%2x\n", r, d);
}
#else
void rmx_simple_error_handler(const char* r, unsigned char d){

}
#endif

void rmx_register_error_handler(void (*handler)(const char*, unsigned char)){
    rmx_error_handler = handler;
}

/*void rmx_error(const char* reason, unsigned char d){
    #ifndef _RMX_NO_ERROR
    rmx_error_handler(reason, d);
    #endif
}*/

/***
 * Real Mode Ex
 * Lisenced under LGPL 3.0
 * 
 * Contributors:
 * Collin McKinley <collinm@collinm.xyz>
 *
 * error.h -- Basic error handling with room to expand
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

extern void (*rmx_error_handler)(const char*, unsigned char);


extern void rmx_simple_error_handler(const char* r, unsigned char d);
extern void rmx_register_error_handler(void (*)());

/* If we define that we dont want error messages, we only define the error 
 * macro, but dont actually give it any data. */

#ifndef _RMX_NO_ERROR
    #define rmx_error(r,d) rmx_error_handler(r, d)
#else
    #define rmx_error(r,d)
#endif
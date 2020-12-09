/***
 * Real Mode Ex
 * Lisenced under LGPL 3.0
 * 
 * Contributors:
 * Collin McKinley <collinm@collinm.xyz>
 *
 * handler.c -- High level interupt emulation handler
 *
 * (*hle_int_ptrs[255])() -- An array of functions, these are called when the
 * int number corresponding to their index in the array is called
 * (see ivt.c)
 * 
 * hle_add_interupt(byte_t int_number, void (*function)() ) -- Add the function
 * to work as the corresponding interupt
 *
 * hle_call_interupt(byte_t intnum) -- Calls the interupt at intnum if found in
 * the array, if it is found it returns TRUE, else it will return FALSE and the 
 * ivt will have to pick up from there.
 *
 ***/
 
extern void (*hle_int_ptrs[255])();

extern void hle_add_interupt(byte_t, void(*)());
extern bool_t hle_call_interupt(byte_t);

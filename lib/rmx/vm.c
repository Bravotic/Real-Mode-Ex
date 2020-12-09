/***
 * Real Mode Ex
 * Lisenced under LGPL 3.0
 * 
 * Contributors:
 * Collin McKinley <collinm@collinm.xyz>
 *
 * vm.c -- The main setup for the virtual machine ( slowly becoming used less
 * and less :( )
 *
 * rmx_init_vm( uint8_t flags ) -- creates virtual machine using 'flags'
 * 
 *
 * set_mem_default() -- creates memory buffer with 1MB size
 ***/

#include <rmx/registers.h>
#include <rmx/parser.h>
#include <rmx/error.h>

#ifndef _RMX_BAREMETAL
    #include <rmx/mem.h>
#else
    extern unsigned char mem[];
#endif

/***
 * HLE stuff
 * (should no longer be used within RMX proper)
 ****/

/*#include <hle/handler.h>
#include <hle/int/10h.h>*/

//#include <stdio.h>

void rmx_init_vm(unsigned char flags){
    rmx_register_setup();
    rmx_set_mem_default();
    if(rmx_error_handler == NULL){
        rmx_register_error_handler(rmx_simple_error_handler);
    }

    /***
     * For now we are assuming that we are loading HLE mode
     ***/

    /***
     * The following is now done within the actual VM creator
     ***/

    /*hle_add_interupt(0x10, hle_10h_handler);*/
}



void rmx_execute(const char* r, unsigned int size){
    
    for(int i = 0; i < size; i++){
        mem[0x7c00 + i] = r[i];
    }
    

    rmx_parse_opcode( &mem[0x7c00], 0x0a);    
}

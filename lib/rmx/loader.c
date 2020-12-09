/* This file is currently legacy and should not be used in any new applications */

#include <rmx/mem.h>


void rmx_loadmem( unsigned char* d, unsigned int size){
    
    /***
     * Load all data we are trying to execute, should be either 512 bytes
     * if we are loading in a boot rom or however big if we arent, but load
     * it in at address 0x7c00
     ***/

    for(unsigned int i = 0; i < size; i++){
        //mem[0x7c00 + i] = d[i];
    }
}

void rmx_loadmem_at(unsigned char* d, unsigned int size, unsigned short mlc){
    for(unsigned int i = 0; i < size; i++){
        //mem[mlc + i] = d[i];
    }
    
}

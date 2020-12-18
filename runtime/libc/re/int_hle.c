#include <runtime/int/10h.h>
#include <runtime/int/16h.h>
#include <rmx_types.h>
#include <hle/handler.h>

void vm_register_ints(){
    hle_add_interupt(0x10, hle_10h_handler); 
    hle_add_interupt(0x16, hle_16h_handler); 
}

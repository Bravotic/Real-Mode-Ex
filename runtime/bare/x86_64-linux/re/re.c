#include <rmx/vm.h>
#include <rmx/registers.h>

void _start(){
    rmx_init_vm(0);
    unsigned char buf[] = { (unsigned char)0xb4, (unsigned char)0x0e, (unsigned char)0xb0, (unsigned char)0x48, (unsigned char)0xcd, (unsigned char)0x10 };
    rmx_execute(buf, 255);
}

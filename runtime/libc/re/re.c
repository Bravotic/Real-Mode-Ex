#include <rmx/vm.h>
#include <rmx/registers.h>
#include <runtime/int_hle.h>
#include <draw/textmode.h>
#include <rmx/mem.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    FILE *fp;
    //unsigned char buf[512] = {0};

    fp = fopen(argv[1], "rb");
    //fgets(buf, 512, (FILE*)fp);

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);  /* same as rewind(f); */

    char *buf = malloc(fsize + 1);
    fread(buf, 1, fsize, fp);
    fclose(fp);

    buf[fsize] = 0;

    /*for(int i = 0; i < fsize; i++){
        printf("%02x", buf[i]);
    }*/

    

    //printf("\n");
    rmx_init_vm(0);

    //rmx_add_interupt();
    vm_register_ints();
    
    #ifdef _RMX_TEXTMODE_DEF
    draw_setup_text_surface(80, 25);
    #endif
    
    rmx_execute(buf, 512);
    
    #ifdef _RMX_TEXTMODE_DEF
    draw_dispose_window();
    #endif
    
    printf("AX: %04x\n", ax);
    printf("BX: %04x\n", bx);
    printf("CX: %04x\n", cx);
    printf("DX: %04x\n\n", dx);
    printf("SI: %04x\n", si);
    printf("DI: %04x\n", di);

    free(buf);
    
    /* Eventually free the memory within a function rmx_destroy_vm() */
    free(mem);
}

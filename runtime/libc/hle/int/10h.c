#include <rmx/registers.h>
#include <stdio.h>


void hle_10h_handler(){
    switch(ah){
        case 0x0:
            
        return;
        case 0x02:
            draw_move_cur(dh, dl);
        return;
        case 0x0e:
            #ifdef _RMX_TEXTMODE_DEF
            draw_char(al);
            #else
            printf("%c", al);
            #endif
        return;
        default:
            printf("Unknown AH value %x", ah);
        return;
    }
}

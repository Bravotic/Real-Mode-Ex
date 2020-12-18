#include <rmx/registers.h>
#include <draw/textmode.h>

typedef struct{
    unsigned int scancode;
    char ascii;
} keystroke;


void hle_16h_handler(){
    switch(ah){
        case 0x0:
            get_keypress();
            if(al == 0x08){
                if(draw_cursor_x > 0)
                    draw_cursor_x--;
            }
            else if(al == 0x0D){
                draw_cursor_x = 0;
            }
        return;
    }
}
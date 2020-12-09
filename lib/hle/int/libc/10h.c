/* LEGACY: This file can now be found in /runtime/libc/hle/int/10h.c */
#include <rmx/registers.h>
#include <stdio.h>

void hle_10h_handler(){
    switch(ah){
        case 0x0:
            switch(al){
                case 0xFF:

                break;
            }
        return;
        case 0x0e:
            printf("%c", al);
        return;

    }
}

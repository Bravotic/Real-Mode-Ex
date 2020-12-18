/***
 * Real Mode Ex
 * Lisenced under LGPL 3.0
 * 
 * Contributors:
 * Collin McKinley <collinm@collinm.xyz>
 *
 * parser.c -- The main parser for opcode
 *
 * rmx_parse_opcode(unsigned char* buffer, unsigned char terminator)
 * Parse the buffer until the terminator character is reached.
 ***/

/***
 * Opcode terminology reference
 *
 * A    Direct address.
 * I    Immediate data.
 *
 * b    Byte
 ***/

#include <rmx/registers.h>
#include <rmx/error.h>
#include <rmx/ivt.h>

/***
 * Please see vm.c for the rationale why we have this here
 ***/
#ifndef _RMX_BAREMETAL
    #include <rmx/mem.h>
#else
    extern unsigned char mem[];
#endif

#include <stdio.h>

#define RMX_STOP_CODE (unsigned int)0 - 2

    int cmpval = 0x0;
    int cmpreg = 0x0;

unsigned int rmx_parse_opcode_single(unsigned char* ref, unsigned int i){


    unsigned int prev_ref[256] = {0};

    unsigned char inst_count = 0;

    //for(int i = 0;i < sizeof(ref); i++){
    //for(unsigned int i = 0; ref[i] != term; i++){
     /*     printf("START LOOP: \n");
    printf("AX: %04x\n", ax);
    printf("BX: %04x\n", bx);
    printf("CX: %04x\n", cx);
    printf("DX: %04x\n\n", dx);
    printf("SI: %04x\n", si);
    printf("DI: %04x\n", di);*/
        //printf("Loaded next opcode at %x (%x)\n", i, ref[i]);
        prev_ref[inst_count] = i;
        inst_count++;
        
        switch(ref[i]){


            
            /***
             * This is an add instruction, but for now it will just terminate
             * the program
             *
             * TODO: make this function as intended
             ***/
            case 0x0: return RMX_STOP_CODE;
            
            //case 0xcb: return;

            case 0xFF: return RMX_STOP_CODE;

            case 0xc3:
                return RMX_STOP_CODE;
            break;

            case 0x3c:
                i++;
                cmpval = ref[i];
                cmpreg = 1; // AL
            break;

            

            case 0x46:
                //printf("SI Increment (%d to %d)\n", si, si+1);
                si = (unsigned short int)si + 1;
                //printf("SI Value to %x\n", ref[si]);
            break;

            case 0x47:
                di = (unsigned short int)di + 1;
                //printf("DI Value to %x\n", ref[di]);
            break;

            // Call
            case 0xe8:
                
                i++;
                unsigned short int goback_ret;
                if(ref[i] > 0xE0){
                    //printf("Calling here\n");
                    goback_ret = 0xFF - ref[i] + 1;
                    i++;
                    //goback *= 0xFF - ref[i] * 100;
                    //printf("Going to %d\n", goback_ret);
                    rmx_parse_opcode(&ref[(i - goback_ret) + 1], 0xcb);
                    //printf("Done parsing\n");
                }
                else{
                    
                    goback_ret = ref[i];
                    i++;
                //goback *= 0xFF - ref[i] * 100;
                //printf("Going to %d\n", goback_ret);
                rmx_parse_opcode_from(ref, 0xcb, (i + goback_ret) + 1);
                //printf("Done parsing\n");
                }
                

            break;

            case 0xeb:
                i++;
                
                /* Why is x86 so weird, shortjumps are signed 8 bit values, so basically if it is over (0xFF / 2), it is a jump backwards */
                if(ref[i] >= 0xFF / 2){

                    /* For now, don't loop infinately */
                    if(ref[i] == 0xFE){
                        return RMX_STOP_CODE;
                    }

                    /* We need to add 1 to the end here because i will be incremented by 1 
                       when the loop ends */
                    i -= ((0xFF - ref[i]) + 1);
                }
                /* How hard would it be guys to add in a new instruction for backjumps and forward jumps */
                else{
                    
                    /* TODO: we may need to subtract 1 from here for the same reason stated above, however this is untested and unverified */
                    i += ref[i];
                }
            break;

            case 0x74:
                i++;
                switch(cmpreg){
                    case 1:
                        if(cmpval == al){
                            if(ref[i] >= 0xFF / 2){
                            
                                i -= ((0xFF - ref[i]) + 1);
                            }
                            else{
                                i += ref[i];
                            }
                        }
                    break;
                    case 2:
                        if(cmpval == bl){
                            if(ref[i] >= 0xFF / 2){
                                i -= ((0xFF - ref[i]) + 1);
                            }
                            else{
                                i += ref[i];
                            }
                        }
                    break;

                    case 0x4:
                        if(cmpval == dl){
                            if(ref[i] >= 0xFF / 2){
                                i -= ((0xFF - ref[i]) + 1);
                            }
                            else{
                                i += ref[i];
                            }
                        }
                    break;
                    case 0x8:
                        if(cmpval == dh){
                            if(ref[i] >= 0xFF / 2){
                                i -= ((0xFF - ref[i]) + 1);
                            }
                            else{
                                i += ref[i];
                            }
                        }
                }
            break;
            
            case 0x75:
                i++;
                switch(cmpreg){
                    case 1:
                        //printf("CMP: %d != %d: ", cmpval, al);
                        if(cmpval != al){
                            //printf("TRUE\n");
                            if(ref[i] >= 0xFF / 2){
                                i -= ((0xFF - ref[i]) + 1);
                            }
                            else{
                                i += ref[i];
                            }
                        }
                        else{
                            //printf("FALSE\n");
                        }
                    break;
                    case 2:
                        if(cmpval != bl){
                            if(ref[i] >= 0xFF / 2){
                                i -= ((0xFF - ref[i]) + 1);
                            }
                            else{
                                i += ref[i];
                            }
                        }
                }
            break;

            case 0x80:
                i++;
                switch(ref[i]){
                    case 0xfa:
                        i++;
                        cmpreg = 4; /*dl*/
                        cmpval = ref[i];
                    break;
                    case 0xfb:
                        i++;
                        cmpreg = 2; /*bl*/
                        cmpval = ref[i];
                    break;
                    case 0xfe:
                        i++;
                        cmpreg = 8; /*dh*/
                        cmpval = ref[i];
                }
            break;

            case 0x38:
                i++;
                switch(ref[i]){
                    case 0xd8:
                        cmpreg = 1;
                        //printf("SETTING CMPVA TO %d, \n", bl);
                        cmpval = bl;
                    break;
                }
            break;

            case 0x83:
                i++;
                switch(ref[i]){
                    case 0xec:
                        i++;
                        //sp -= ref[i];
                    break;
                }
            break;

            case 0x0e:
                sp++;
                sp++;
            break;
            
/*************************************************************************
 * Move Instructions
 *************************************************************************/
            case 0xb8:
                i++;
                al = ref[i];
                i++;
                ah = ref[i];
            break;
            
            case 0xc6:
                i++;
                switch(ref[i]){
                    case 0x46:
                        i++;

                        byte_t goback_bp = 0xFF - ref[i] + 1;
                        i++;
                        mem[bp - goback_bp] = ref[i];
                    break;
                }
            break;

            case 0x8a:
                i++;
                switch(ref[i]){
                    case 0x04:
                        
                        //printf("Setting AL equal to %x\n", ref[si]);
                        al = ref[si];
                    break;

                    case 0x86:
                        i++;
                        unsigned short int goback_bp_al = 0xFF - ref[i] + 1;
                        i++;

                        /***
                         * STUB: Eventually implement this properly
                         ***/

                        /*goback *= 0xFF - ref[i] * 100;*/

                        al = mem[bp - goback_bp_al];
                    break;

                    case 0x1d:
                        //printf("Setting BL equal to %x\n", ref[di]);
                        bl = ref[di];
                    break;
                
                }
            break;

            case 0x8b:
               i++;
               switch(ref[i]){
                    case 0x36:
                        i++;
                        BYTEHIGH(si) = ref[i];
                        i++;
                        BYTELOW(si) = ref[i];
                    break;
               }
            break;

            case 0x88:
               i++;
                switch(ref[i]){
                    case 0x46:
                        i++;
                        byte_t goback = 0xFF - ref[i] + 1;
                        mem[bp - goback] = al;
                    break;
                    case 0x05:
                        ref[di] = al;
                    break;
                }

            break;   


            /***
             * Opcode: 0x89
             * Instruction: mov Ev, Gv
             ***/
            case 0x89:
                i++;
                switch(ref[i]){
                    
                    /***
                     * Opcode: 0x89 0xe5
                     * Instruction: mov BP, SP
                     ***/
                    case 0xe5:
                        bp = sp;
                    break;
                    case 0xfe:
                        si = di;
                    break;
                    default:
                        rmx_error("UNKNOWN_MOV", ref[i]); 
                    break;
                }
            break;


            /***
             * Opcode:      0xb0
             * Instruction: mov AL, Ib
             ***/
            case 0xb0:
                i++;
                al = ref[i];
            break;
                
            /***
             * Opcode:      0xb3
             * Instruction: mov BL, Ib
             ***/
            case 0xb3:
                i++;
                bl = ref[i];
            break;

            /***
             * Opcode:      0xb1
             * Instruction: mov CL, Ib
             ***/
            case 0xb1:      
                i++;
                cl = ref[i];
            break;
            
            /***
             * Opcode:      0xb2
             * Instruction: mov DL, Ib
             ***/
            case 0xb2:
                i++;
                dl = ref[i];
            break;

            /***
             * Opcode:      0xb4
             * Instruction: mov AH, Ib
             ***/
            case 0xb4:
                i++;
                ah = ref[i];
            break;
            
            /***
             * Opcode:      0xb7
             * Instruction: mov BH, Ib
             ***/
            case 0xb7:
                i++;
                bh = ref[i];
            break;
            
            /***
             * Opcode:      0xb5
             * Instruction: mov CH, Ib
             ***/
            case 0xb5:
                i++;
                ch = ref[i];
            break;
            
            /***
             * Opcode:      0xb6
             * Instruction: mov DH, Ib
             ***/
            case 0xb6:
                i++;
                dh = ref[i];
            break;

            case 0xbe:
                i++;
                byte_t seg = ref[i];
                i++;
                byte_t off = ref[i];
                
                //printf("SI set to 0x%2x\t0x%2x\n", seg, ref[seg]);
                si = seg;
            break;

            case 0xbf:
                i++;
                byte_t seg_di = ref[i];
                i++;
                byte_t off_di = ref[i];
                
                //printf("SI set to 0x%2x\t0x%2x\n", seg, ref[seg]);
                di = seg_di;
            break;
            
            /***
             * Opcode:      0xcd
             * Instruction: int Ib
             ***/
            case 0xcd:
                i++;
                rmx_call_int(ref[i]);
            break;

            case 0xfe:
                i++;
                switch(ref[i]){
                    case 0xc0:
                        al++;
                    break;
                    case 0xc2:
                        dl++;
                    break;
                    case 0xc6:
                        dh++;
                    break;
                }
            break;

            default:
                rmx_error("UNKNOWN_OPCODE", ref[i]);
#ifdef _RMX_PARSER_NO_STOP
                break;
#else
            return;
#endif //_RMX_PARSER_NO_STOP
        }
    return i;
}

void rmx_parse_opcode(unsigned char* ref, unsigned char term){
    printf("%x", ref[0]);
    for(unsigned int i = 0; ref[i] != term; i++){
        i = rmx_parse_opcode_single(ref, i);
        if(i == RMX_STOP_CODE){
            break;
        }
    }
}

void rmx_parse_opcode_from(unsigned char* ref, unsigned char term, unsigned int i){
    for(; ref[i] != term; i++){
        i = rmx_parse_opcode_single(ref, i);
        if(i == RMX_STOP_CODE){
            break;
        }
    }
}
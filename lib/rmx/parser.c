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

void rmx_parse_opcode(unsigned char* ref, unsigned char term){

    int cmpval = 0x0;
    int cmpreg = 0x0;
    unsigned int prev_ref[256] = {0};

    unsigned char inst_count = 0;

    //for(int i = 0;i < sizeof(ref); i++){
    for(unsigned int i = 0; ref[i] != term; i++){
        //printf("Loaded next opcode at %i (%x)\n", i, ref[i]);
        prev_ref[inst_count] = i;
        inst_count++;
        
        switch(ref[i]){


            
            /***
             * This is an add instruction, but for now it will just terminate
             * the program
             *
             * TODO: make this function as intended
             ***/
            case 0x0: return;
            
            //case 0xcb: return;

            case 0xFF: return;

            case 0x3c:
                i++;
                cmpval = ref[i];
                cmpreg = 1; // AL
            break;

            case 0xbe:
                i++;
                byte_t seg = ref[i];
                i++;
                byte_t off = ref[i];
                
                si = seg;
            break;

            case 0x46:
                si++;
            break;

            // Call
            case 0xe8:
                
                i++;
                unsigned short int goback_ret = 0xFF - ref[i] + 1;
                i++;
                //goback *= 0xFF - ref[i] * 100;
                //printf("Going back to %d\n", i - goback_ret);
                rmx_parse_opcode(&ref[(i - goback_ret) + 1], 0xcb);
                //printf("Done parsing\n");

            break;

            case 0xeb:
                i++;
                
                /* Why is x86 so weird, shortjumps are signed 8 bit values, so basically if it is over (0xFF / 2), it is a jump backwards */
                if(ref[i] >= 0xFF / 2){

                    /* For now, don't loop infinately */
                    if(ref[i] == 0xFE){
                        return;
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
                            i += ref[i];
                        }
                    break;

                    case 0x4:
                        if(cmpval == dl){
                            i += ref[i];
                        }
                    break;
                    case 0x8:
                        if(cmpval == dh){
                            i += ref[i];
                        }
                }
            break;
            
            case 0x75:
                i++;
                switch(cmpreg){
                    case 1:
                        if(cmpval != al){
                            i += ref[i];
                        }
                    break;
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
                    case 0xfe:
                        i++;
                        cmpreg = 8; /*dh*/
                        cmpval = ref[i];
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
    }
    return;
}


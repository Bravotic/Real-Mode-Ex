unsigned short int ax;
unsigned short int bx;
unsigned short int cx;
unsigned short int dx;

unsigned short int si;
unsigned short int di;

unsigned short int bp;
unsigned short int sp;
unsigned short int ss;

void rmx_register_setup(){
    ax = 0x0000;
    bx = 0x0000;
    cx = 0x0000;
    dx = 0x0000;

    si = 0x0000;
    di = 0x0000;

    bp = 0x7cfe;
    sp = 0x7cfe;
    ss = 0x0000;

}

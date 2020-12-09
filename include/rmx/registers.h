#include <rmx_types.h>

#define BYTELOW(v)      (*(((byte_t*) (&v) + 1)))
#define BYTEHIGH(v)     (*((byte_t*) (&v)))

extern unsigned short int ax;
extern unsigned short int bx;
extern unsigned short int cx;
extern unsigned short int dx;

#define al BYTELOW(ax)
#define ah BYTEHIGH(ax)

#define bl BYTELOW(bx)
#define bh BYTEHIGH(bx)

#define cl BYTELOW(cx)
#define ch BYTEHIGH(cx)

#define dl BYTELOW(dx)
#define dh BYTEHIGH(dx)

extern short int si;
extern short int di;

extern unsigned short int bp;
extern unsigned short int sp;
extern unsigned short int ss;


extern void rmx_register_setup();

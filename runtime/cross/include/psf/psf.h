#define PSF_FONT_MAGIC 0x864ab572

#ifdef SDL2
#define COLOUR_TYPE SDL_Color
#include <SDL2/SDL.h>
#endif

#ifndef COLOUR_TYPE
#define COLOUR_TYPE unsigned int
#endif



typedef struct{
    unsigned int magic;
    unsigned int version;
    unsigned int headersize;
    unsigned int flags;
    unsigned int glyphtotal;
    unsigned int glyptbytes;
    unsigned int height;
    unsigned int width;
} PSF_font;

extern char _binary_adjunct_font_psf_start;
extern char _binary_adjunct_font_psf_end;
extern void PSF_init();
extern void PSF_putchar(unsigned short int c, int cx, int cy, COLOUR_TYPE fg, COLOUR_TYPE bg);
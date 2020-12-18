#include <psf/psf.h>
#include <stdio.h>
#define PSF_FONT_MAGIC 0x864ab572

#ifdef SDL2
#define DRAW_PIXEL(x, y, c) sdl_draw_pixel(x, y, c)
#endif


extern char _binary_adjunct_font_psf_start;
extern char _binary_adjunct_font_psf_end;

unsigned short unicode;

void PSF_init(){
    unsigned short glyph = 0;
    PSF_font* font = (PSF_font*)&_binary_adjunct_font_psf_start;

    printf("Loaded PSF\n");
    printf("Magic   : %d\n", font->magic);
    printf("Ver     : %d\n", font->version);
    printf("Header  : %d\n", font->headersize);
    printf("Flags   : %d\n", font->flags);
    printf("Total   : %d\n", font->glyphtotal);
    printf("Bytes   : %d\n", font->glyptbytes);
    printf("Height  : %d\n", font->height);
    printf("Width   : %d\n", font->width);

    /* For now we are going to reguard the unicode table, however in the 
     * future we may load it in here */

}


void PSF_putchar(unsigned short int c, int cx, int cy, COLOUR_TYPE fg, COLOUR_TYPE bg){
    //printf("Printing: %x(%d, %d)\n", c, cx, cy);
    PSF_font* font = (PSF_font*)&_binary_adjunct_font_psf_start;
    int bytesperline = (font->width + 7) / 8;

    //unsigned char* glyph = (unsigned char*)&_binary_font_psf_start + font->headersize + ( c > 0 && c < font->glyphtotal ? c : 0) * font->glyptbytes;
    
       unsigned char *glyph =
     (unsigned char*)&_binary_adjunct_font_psf_start +
     font->headersize +
     (c>0&&c<font->glyphtotal?c:0)*font->glyptbytes;
    
   // printf("Loaded glyph %x\n", glyph);

    int x,y, line, mask;
    for(y = 0; y < font->height; y++){
        //printf("| ");
        mask = 1 << (font->width - 1);
        for(x = 0; x < font->width; x++){
            if( ((int)*glyph) & (mask)){
                DRAW_PIXEL(cx * font->width + x, cy * font->height + y, fg);
            }
            else{
                DRAW_PIXEL(cx * font->width + x, cy * font->height + y, bg);
            }
            //printf(" [%d] %2x ",(y+1) * x, glyph[(y+1) * x]);
            mask >>= 1;
        }
        //printf(" | \n");
        glyph += bytesperline;
    }
}
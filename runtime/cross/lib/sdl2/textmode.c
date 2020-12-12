#include <rmx_types.h>
#include <SDL2/SDL.h>

SDL_Surface* windowSurface;
SDL_Window* window;

void sdl_draw_pixel(int x, int y, SDL_Color c){
    SDL_DrawPixel(windowSurface, c.r, c.b, c.g, 255, x, y);
}

void SDL_DrawPixel(SDL_Surface* surf, unsigned char r, unsigned char g, unsigned char b, unsigned char a, unsigned int x, unsigned int y){
  unsigned char* pixels = (unsigned char*)surf->pixels;
    pixels[4 * (y * surf -> w + x) + 0] = b;
    pixels[4 * (y * surf -> w + x) + 1] = g;
    pixels[4 * (y * surf -> w + x) + 2] = r;
    pixels[4 * (y * surf -> w + x) + 3] = a;

}

unsigned int draw_cursor_x = 0;
unsigned int draw_cursor_y = 0;

SDL_Color fg;


SDL_Color bg ;

unsigned char draw_setup_text_surface(unsigned int w, unsigned int h){
        SDL_Init(SDL_INIT_EVERYTHING);
        fg.r = 255;
fg.b = 255;
fg.g = 255;
        window = SDL_CreateWindow("RMX Graphics Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w * 8, h * 16, SDL_WINDOW_SHOWN);
        windowSurface = SDL_GetWindowSurface(window);
        SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 0, 0, 0));

}

void draw_move_cur(byte_t row, byte_t col){
    draw_cursor_y = row;
    draw_cursor_x = col;
}

void draw_char(byte_t c){
    if(c > 31){
        PSF_putchar((unsigned int) c, draw_cursor_x, draw_cursor_y, fg, bg);
        if(draw_cursor_x < 80){
            draw_cursor_x++;
        }
        else{
            draw_cursor_x = 0;
            draw_cursor_y++;
        }
    }
    else if(c == 10){
        draw_cursor_x = 0;
        draw_cursor_y++;
    }
    
    
    SDL_UpdateWindowSurface(window);
}

void draw_dispose_window(){
    SDL_Delay(10000);
    SDL_FreeSurface(windowSurface);
    SDL_DestroyWindow(window);
}
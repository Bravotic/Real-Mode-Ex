#include <rmx_types.h>
#include <SDL2/SDL.h>
#include <draw/textmode.h>
#include <rmx/registers.h>

SDL_Surface* windowSurface;
SDL_Window* window;
SDL_Renderer* renderer;

unsigned char *keybuffer;

void sdl_draw_pixel(int x, int y, SDL_Color c){
    #ifdef _RMX_USE_RENDERER
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 0xFF);
        SDL_RenderDrawPoint(renderer, x, y);
    #else
        SDL_DrawPixel(windowSurface, c.r, c.b, c.g, 255, x, y);
    #endif
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

unsigned int WIDTH = 0;
unsigned int HEIGHT = 0;

SDL_Color fg;


SDL_Color bg ;

unsigned char draw_setup_text_surface(unsigned int w, unsigned int h){

        WIDTH = w;
        HEIGHT = h;
        SDL_Init(SDL_INIT_EVERYTHING);
        fg.r = 255;
fg.b = 255;
fg.g = 255;
        window = SDL_CreateWindow("RMX Graphics Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w * 8, h * 16, SDL_WINDOW_SHOWN);
        
        #ifdef _RMX_USE_RENDERER
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(renderer);
        #else
            windowSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 0, 0, 0));
        #endif

        keybuffer = malloc(w * h);

        SDL_StartTextInput();
}

void draw_move_cur(byte_t row, byte_t col){
    //printf("Cursor pos set to, %d, %d\n", row, col);
    draw_cursor_y = row;
    draw_cursor_x = col;
}

void get_cursor_pos(){
    dh = draw_cursor_y;
    dl = draw_cursor_x;
}

void draw_char(byte_t c){
    //printf("Putchar called");
    if(c > 31){
        PSF_putchar((unsigned int) c, draw_cursor_x, draw_cursor_y, fg, bg);
        //keybuffer[draw_cursor_y * WIDTH + draw_cursor_x] = c;
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
    
    #ifdef _RMX_USE_RENDERER
    
    SDL_RenderPresent(renderer);
    #else
    SDL_UpdateWindowSurface(window);
    #endif
}

void draw_dispose_window(){
    //SDL_Delay(10000);
    SDL_FreeSurface(windowSurface);
    SDL_DestroyWindow(window);
}



void get_keypress(){
    SDL_Event evt;
    
    while(evt.type !=  SDL_TEXTINPUT){
        while(SDL_PollEvent(&evt)){
            //printf("Event type %d\n", evt.type);
            if(evt.type == SDL_TEXTINPUT){
                //printf("Event type KEYDOWN\n");
                //printf("TEXT: %s\n", evt.text.text);
                al = evt.text.text[0];
                //ah = evt.key.keysym.scancode;
                SDL_UpdateWindowSurface(window);
                return;
            }
            else if(evt.type == SDL_KEYDOWN){
                if( evt.key.keysym.sym < 32){
                //printf("Fallback\n");
                al = evt.key.keysym.sym;
                SDL_UpdateWindowSurface(window);
                return;
                }
            }
            if(evt.type == SDL_QUIT){
                exit(0);
            }
        }
        SDL_Delay(10);
        //printf("Event not KEYDOWN\n");
    }
}

int draw_run_window_events(){
    //SDL_UpdateWindowSurface(window);

    SDL_Event evt;
    while(SDL_PollEvent(&evt)){
        if(evt.type == SDL_QUIT){
            return 0;
        }
    }
    return 1;
}

void draw_delay(unsigned int time){
    SDL_Delay(time);
}
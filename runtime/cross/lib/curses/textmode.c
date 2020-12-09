#include <rmx_types.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int draw_cursor_x = 0;
unsigned int draw_cursor_y = 0;
unsigned int pagenum = 0;

bool_t draw_setup_text_surface(unsigned int w, unsigned int h){
    initscr();
    if(COLS < (int)w || LINES < (int)h){
        endwin();
        printf("The program is requesting a mode that is too small for the current terminal.  Please resize to %dx%d or run with the graphical terminal option by using '-gfxterm' when executing the program.\n", w, h);
        printf("(Placeholder, please resize terminal)\n");
        exit(1);
    }
    
}

void draw_move_cur(byte_t row, byte_t col){
    row--;
    //printw("Moving to %d, %d", row, col);
    move((int) row, (int) col);
    refresh();
}

void draw_char(byte_t c){
    printw("%c", c);
    refresh();
}

void draw_dispose_window(){
    getch();
    endwin();
}
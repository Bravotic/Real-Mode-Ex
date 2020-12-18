#include <rmx_types.h>

typedef struct Key{
    unsigned int scancode;
    char ascii;
} Keystroke;


extern unsigned int draw_cursor_x;
extern unsigned int draw_cursor_y;

extern bool_t draw_setup_text_surface(unsigned int, unsigned int);
extern void draw_char(byte_t);
extern void draw_move_cur(byte_t, byte_t);
extern void get_keypress();
extern int draw_run_window_events();
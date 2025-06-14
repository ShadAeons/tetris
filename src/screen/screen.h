#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdbool.h>

#include "screen_object.h"


#define SCREEN_BORDER 1
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24

#define CHAR_EMPTY_SPACE        ' '
#define CHAR_CORNER             '+'
#define CHAR_VERTICAL_BORDER    '|'
#define CHAR_HORIZONTAL_BORDER  '-'


typedef struct {
    char buffer[SCREEN_WIDTH * SCREEN_HEIGHT];
} Screen;


void screen_init(Screen *screen);
void screen_exit(Screen *screen);

void screen_clear(Screen *screen);

void screen_draw(Screen *screen, ScreenObject *object);
void screen_display(Screen *screen);

#endif  // __SCREEN_H__

#include "screen.h"
#include "screen_object.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void screen_init(Screen *screen) {
    // Enter alternate buffer screen
    fputs("\033[?1049h", stdout);

    // Start with empty screen
    screen_clear(screen);
}


void screen_exit(Screen *screen) {
    // Exit alternate buffer screen
    fputs("\033[?1049l", stdout);
}


void screen_clear(Screen *screen) {
    // Set all charachters in the screen buffer to the empty space character
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        screen->buffer[i] = CHAR_EMPTY_SPACE;
    }
}


void screen_draw(Screen *screen, ScreenObject *object) {
    // Find the amount cut off from left and top
    uint8_t left_diff = object->x < 0 ? abs(object->x) : 0;
    uint8_t top_diff = object->y < 0 ? abs(object->y) : 0;

    // Find the amount cut off from right and bottom
    uint8_t right_diff = MAX((object->x + object->width) - SCREEN_WIDTH, 0);
    uint8_t bottom_diff = MAX((object->y + object->height) - SCREEN_HEIGHT, 0);

    // The remaining size after cutting off from all sides
    uint8_t remaining_width = object->width - right_diff;
    uint8_t remaining_height = object->height - bottom_diff;

    for (int i = top_diff * object->width + left_diff; i < remaining_width * remaining_height; i++) {
        // Convert local vector positioning to screen
        uint8_t x = i % remaining_width + object->x;
        uint8_t y = (uint8_t) (i / remaining_width) + object->y;

        screen->buffer[y * SCREEN_WIDTH + x] = object->data[i];
    }
}


void screen_display(Screen *screen) {
    fputs("\033[H\033[J", stdout);

    // +2 for the borders on all 4 sides, +1 for \n character
    char buffer[(SCREEN_WIDTH + 2 + 1) * (SCREEN_HEIGHT + 2)] = {0};
    int counter = 0;

    // Draw top border
    buffer[counter++] = CHAR_CORNER;
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        buffer[counter++] = CHAR_HORIZONTAL_BORDER;
    }
    buffer[counter++] = CHAR_CORNER;
    buffer[counter++] = '\n';

    // Draw the values
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        buffer[counter++] = CHAR_VERTICAL_BORDER;
        memcpy(&buffer[counter], &screen->buffer[i * SCREEN_WIDTH], sizeof(char) * SCREEN_WIDTH);
        counter += SCREEN_WIDTH;
        buffer[counter++] = CHAR_VERTICAL_BORDER;
        buffer[counter++] = '\n';
    }
    
    // Copy top border to bottom border
    memcpy(&buffer[counter], buffer, (SCREEN_WIDTH + 2 + 1) * sizeof(char));

    // Write the buffer to stdout all at once
    fwrite(buffer, sizeof(char), (SCREEN_WIDTH + 2 + 1) * (SCREEN_HEIGHT + 2), stdout);
}

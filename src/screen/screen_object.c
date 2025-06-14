#include "screen_object.h"

#include "../memory/alloc.h"
#include <string.h>


ScreenObject *screen_object_create(int8_t x, int8_t y, uint8_t width, uint8_t height) {
    ScreenObject *object = mem_alloc(sizeof(ScreenObject));
    object->x = x;
    object->y = y;
    object->width = width;
    object->height = height;
    object->data = mem_alloc(sizeof(char) * width * height);

    // Set default data to ' '
    memset(object->data, ' ', sizeof(char) * width * height);
    return object;
}


void screen_object_destroy(ScreenObject *object) {
    mem_free(object->data);
    mem_free(object);
}

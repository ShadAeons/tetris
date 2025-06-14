#ifndef __SCREEN_OBJECT_H__
#define __SCREEN_OBJECT_H__

#include <stdint.h>


typedef struct {
    int8_t x, y;
    uint8_t width, height;
    char *data;
} ScreenObject;


ScreenObject *screen_object_create(int8_t x, int8_t y, uint8_t width, uint8_t height);
void screen_object_destroy(ScreenObject *object);


#endif  // __SCREEN_OBJECT_H__

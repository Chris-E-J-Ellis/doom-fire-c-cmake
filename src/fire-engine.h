#ifndef FIRE_ENGINE_H
#define FIRE_ENGINE_H

#include <stdint.h>

typedef struct
{
    int width;
    int height;
    int *data;
} doom_fire_buffer_t;

void engine_create_buffer(int width, int height, doom_fire_buffer_t **buffer);
void engine_destroy_buffer(doom_fire_buffer_t **buffer);
void engine_init_buffer(doom_fire_buffer_t *buffer, uint8_t ignition_value);
void engine_step_fire(doom_fire_buffer_t *buffer);

#endif

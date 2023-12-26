#ifndef FIRE_ENGINE_H
#define FIRE_ENGINE_H

#include <stdint.h>

typedef struct
{
    uint16_t width;
    uint16_t height;
    uint8_t *data;
} doom_fire_buffer_t;

void engine_create_buffer(uint16_t width, uint16_t height, doom_fire_buffer_t **buffer);
void engine_destroy_buffer(doom_fire_buffer_t **buffer);
void engine_init_buffer(doom_fire_buffer_t *buffer, uint8_t ignition_value);
void engine_step_fire(doom_fire_buffer_t *buffer);

#endif

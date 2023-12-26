#include "fire-engine.h"

#include <stdint.h>
#include <stdlib.h>
#include <time.h>

static inline void spread_fire(uint8_t *data, uint32_t source_position, uint16_t width);

void engine_create_buffer(uint16_t width, uint16_t height, doom_fire_buffer_t **const buffer)
{
    *buffer = malloc(sizeof(doom_fire_buffer_t));
    (*buffer)->width = width;
    (*buffer)->height = height;
    (*buffer)->data = malloc(width * height * sizeof(uint8_t));
}

void engine_destroy_buffer(doom_fire_buffer_t **const buffer)
{
    free((*buffer)->data);
    free(*buffer);
    *buffer = NULL;
}

void engine_init_buffer(doom_fire_buffer_t *const buffer, uint8_t ignition_value)
{
    srand(time(NULL));

    for (int i = 0; i < buffer->height * buffer->width; i++)
    {
        buffer->data[i] = 0;
    }

    for (int i = (buffer->height - 1) * buffer->width; i < buffer->height * buffer->width; i++)
    {
        buffer->data[i] = ignition_value;
    }
}

void engine_step_fire(doom_fire_buffer_t *const buffer)
{
    for (int x = 0; x < buffer->width; x++)
    {
        for (int y = 1; y < buffer->height; y++)
        {
            const uint32_t buffer_position = (y * buffer->width) + x;
            spread_fire(buffer->data, buffer_position, buffer->width);
        }
    }
}

static inline void spread_fire(uint8_t *const data, uint32_t source_position, uint16_t width)
{
    const int pixel = data[source_position];

    if (pixel <= 0)
    {
        data[source_position - width] = 0;
    }
    else
    {
        const int decay = rand() & 3;
        const int destination_position = ((int)source_position - width) - decay + 1;
        if (destination_position < 0)
            return;

        data[destination_position] = pixel - (decay & 1);
    }
}

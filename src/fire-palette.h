#ifndef FIRE_PALETTE_H
#define FIRE_PALETTE_H

#include <stdint.h>

typedef struct
{
    const uint8_t *rgb_data;
    size_t size;
} doom_fire_palette_t;

const doom_fire_palette_t *palette_get();

#endif
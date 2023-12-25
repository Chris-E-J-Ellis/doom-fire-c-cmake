#ifndef FIRE_RENDERER_H
#define FIRE_RENDERER_H

#include "fire-engine.h"
#include "fire-palette.h"

#include <stdbool.h>

typedef void (*renderer_cleanup_renderer)(void);
typedef void (*renderer_draw_buffer)(const doom_fire_buffer_t *buffer);
typedef bool (*renderer_exit_requested)(void);
typedef uint8_t (*renderer_get_max_ignition_value)(void);
typedef bool (*renderer_init_renderer)(const doom_fire_buffer_t *buffer, const doom_fire_palette_t *palette);
typedef bool (*renderer_process_additional_args)(int argc, char **argv);
typedef void (*renderer_wait)(void);

typedef struct
{
    renderer_cleanup_renderer cleanup_renderer;
    renderer_draw_buffer draw_buffer;
    renderer_exit_requested exit_requested;
    renderer_get_max_ignition_value get_max_ignition_value;
    renderer_init_renderer init;
    renderer_process_additional_args process_additional_args;
    renderer_wait wait;
} fire_renderer_t;

#endif
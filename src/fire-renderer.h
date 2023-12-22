#ifndef FIRE_RENDERER_H
#define FIRE_RENDERER_H

#include "fire-engine.h"

#include <stdbool.h>

typedef void (*renderer_cleanup_renderer)();
typedef void (*renderer_draw_buffer)(doom_fire_buffer_t *const buffer);
typedef bool (*renderer_exit_requested)();
typedef int (*renderer_get_max_ignition_value)();
typedef int (*renderer_init_renderer)(const doom_fire_buffer_t *const buffer);
typedef bool (*renderer_process_additional_args)(int argc, char **argv);
typedef void (*renderer_wait)();

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
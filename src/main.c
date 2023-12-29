#include "fire-engine.h"
#include "fire-renderer-sdl.h"
#include "fire-renderer-text.h"

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_ARG_COUNT 3
#define DEFAULT_WIDTH 300
#define DEFAULT_HEIGHT 300

static bool keep_running = true;
static void sig_handler(int input)
{
    (void)input;
    keep_running = false;
}

int main(int argc, char **argv)
{
    const bool use_default_args = argc < DEFAULT_ARG_COUNT;

    if (use_default_args)
    {
        printf("Insufficient arguments supplied, using default resolution: 300x300\n");
        printf("Usage: doom-fire [WIDTH] [HEIGHT]\n");
    }

    const int width = !use_default_args ? strtol(argv[1], NULL, 10) : DEFAULT_WIDTH;
    const int height = !use_default_args ? strtol(argv[2], NULL, 10) : DEFAULT_HEIGHT;

   const fire_renderer_t renderer = get_renderer_sdl();
   // const fire_renderer_t renderer = get_renderer_text();

    if (!renderer.process_additional_args(argc - DEFAULT_ARG_COUNT, &argv[DEFAULT_ARG_COUNT]))
    {
        printf("Unable to process additional arguments.");
        return 1;
    }

    const doom_fire_palette_t *const palette = palette_get();

    doom_fire_buffer_t *buffer = {0};
    engine_create_buffer(width, height, &buffer);

    int init_success = renderer.init(buffer, palette);
    if (!init_success)
        return 1;

    const int ignition_value = renderer.get_max_ignition_value();
    engine_init_buffer(buffer, ignition_value);

    signal(SIGINT, sig_handler);

    while (keep_running)
    {
        if (renderer.exit_requested())
            keep_running = false;

        renderer.draw_buffer(buffer);
        engine_step_fire(buffer);
        renderer.wait();
    }

    engine_destroy_buffer(&buffer);
    renderer.cleanup_renderer();

    printf("Done...\n");

    return 0;
}
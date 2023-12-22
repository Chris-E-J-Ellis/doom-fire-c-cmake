#include "fire-engine.h"
#include "fire-renderer-sdl.h"

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool keep_running = true;
static void sig_handler(int input)
{
    (void)input;
    keep_running = false;
}

int main(int argc, char **argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    bool use_default_args = false;

    if (argc < 3)
    {
        printf("Insufficient arguments supplied, using default resolution: 300x300\n");
        printf("Usage: doom-fire [WIDTH] [HEIGHT]\n");
        use_default_args = true;
    }

    int width = !use_default_args ? atoi(argv[1]) : 300;
    int height = !use_default_args ? atoi(argv[2]) : 300;

    const fire_renderer_t renderer = sdl_get_renderer();

    if (!renderer.process_additional_args(argc - 3, &argv[3]))
    {
        printf("Unable to process additional arguments.");
        return 1;
    }

    doom_fire_buffer_t *buffer = NULL;
    engine_create_buffer(width, height, &buffer);

    int init_success = renderer.init(buffer);
    if (init_success != 0)
        return init_success;

    int ignition_value = renderer.get_max_ignition_value();
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
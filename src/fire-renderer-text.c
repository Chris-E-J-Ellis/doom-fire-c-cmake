#include "fire-renderer-text.h"

#include <stdio.h>
#include <unistd.h>

static const char text_palette[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
static fire_renderer_t fire_renderer;

static void cleanup_renderer(void)
{
}

static void draw_buffer(const doom_fire_buffer_t *buffer)
{
    for (int y = 0; y < buffer->height; ++y)
    {
        for (int x = 0; x < buffer->width; ++x)
        {
            const size_t buffer_position = x + (y * buffer->width);
            const uint8_t pixel = buffer->data[buffer_position] % sizeof(text_palette);
            const char pixel_char = text_palette[pixel];
            printf("%c", pixel_char);
        }
        printf("\n");
    }
    printf("\n");
}

static bool exit_requested(void)
{
    return false;
}

static uint8_t get_max_ignition_value(void)
{
    return sizeof(text_palette) - 1;
}

static bool init(const doom_fire_buffer_t *buffer, const doom_fire_palette_t *palette)
{
    (void)buffer;
    (void)palette;

    return true;
}

static bool process_additional_args(int argc, char **argv)
{
    (void)argv;

    if (argc > 0)
        return false;

    return true;
}

static void wait(void)
{
    usleep(1000000);
}

fire_renderer_t get_renderer_text(void)
{
    fire_renderer = (fire_renderer_t){
            .cleanup_renderer = cleanup_renderer,
            .draw_buffer = draw_buffer,
            .exit_requested = exit_requested,
            .get_max_ignition_value = get_max_ignition_value,
            .init = init,
            .process_additional_args = process_additional_args,
            .wait = wait,
    };
    return fire_renderer;
}
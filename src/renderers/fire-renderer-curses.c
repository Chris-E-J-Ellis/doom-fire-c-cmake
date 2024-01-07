#include "fire-renderer-curses.h"
#include "curses.h"

#include <stdlib.h>
#include <unistd.h>

static const doom_fire_palette_t *fire_palette;
static int *pixel_palette = NULL;
static bool use_custom_colours;
static uint8_t palette_size = 0;
static fire_renderer_t fire_renderer;

static void init_colours(void);
static void init_custom_colours(void);

static void cleanup_renderer(void)
{
    free(pixel_palette);
    pixel_palette = NULL;
    clear();
    endwin();
}

static void draw_buffer(const doom_fire_buffer_t *buffer)
{
    for (int y = 0; y < buffer->height; y++)
    {
        for (int x = 0; x < buffer->width; x++)
        {
            int pixel = buffer->data[x + (y * buffer->width)];
            int colorPair = pixel_palette[pixel];
            char output = ' ';
            attron(COLOR_PAIR(colorPair));
            mvaddch(y, x, output);
            attroff(COLOR_PAIR(colorPair));
        }
    }
    refresh();
}

static bool exit_requested(void)
{
    return false;
}

static uint8_t get_max_ignition_value(void)
{
    return palette_size - 1;
}

static bool init(const doom_fire_buffer_t *buffer, const doom_fire_palette_t *palette)
{
    (void)buffer;
    fire_palette = palette;

    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);

    if (use_custom_colours)
    {
        init_custom_colours();
    }
    else
    {
        init_colours();
    }

    clear();
    return true;
}

static bool process_additional_args(int argc, char **argv)
{
    if (argc < 1)
    {
        printf("    -c    Use a custom colour palette");
        printf("          N.B. Using custom palette will alter terminal colours.\n");
        return true;
    }

    if (argv[0][1] == 'c')
        use_custom_colours = true;

    return true;
}

static void wait(void)
{
    usleep(10000);
}

fire_renderer_t get_renderer_curses(void)
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

void init_colours(void)
{
    printw("Test Palette:\n");
    for (int i = 0; i < 256; i++)
    {
        init_pair((short)i, COLOR_BLACK, (short)i);
        attron(COLOR_PAIR(i));
        printw("%i ", i);
        attroff(COLOR_PAIR(i));
    }

    uint8_t reduced_palette[] = {16, 233, 234, 52, 52, 88, 124, 160, 196, 202, 208, 215, 220, 227, 229, 230, 15};
    palette_size = sizeof(reduced_palette) / sizeof(uint8_t);
    pixel_palette = malloc(palette_size * sizeof(int));

    printw("\nSelected Palette:\n");
    for (int i = 0; i < palette_size; i++)
    {
        pixel_palette[i] = reduced_palette[i];
        attron(COLOR_PAIR(reduced_palette[i]));
        printw("%i ", i);
        attroff(COLOR_PAIR(reduced_palette[i]));
    }

    refresh();
    usleep(2000000);
}

void init_custom_colours(void)
{
    printw("Selected Palette:\n");
    float colour_scale_factor = 1000.0f / 256;
    pixel_palette = malloc(fire_palette->size * sizeof(int));

    for (int i = 0; i < palette_size; i++)
    {
        short color_index = i + 50;// Not saving the terminal colours, try not to hit the common ones.
        int paletteIndex = i * 3;
        float red = (float)fire_palette->rgb_data[paletteIndex] * colour_scale_factor;
        float green = (float)fire_palette->rgb_data[paletteIndex + 1] * colour_scale_factor;
        float blue = (float)fire_palette->rgb_data[paletteIndex + 2] * colour_scale_factor;

        init_color(color_index, (short)red, (short)green, (short)blue);
        init_pair(color_index, COLOR_BLACK, color_index);
        pixel_palette[i] = color_index;

        attron(COLOR_PAIR(color_index));
        printw("%i ", i);
        attroff(COLOR_PAIR(color_index));
    }

    refresh();
    usleep(2000000);
}
#include "SDL.h"
#include "fire-engine.h"
#include "fire-palette.h"
#include "fire-renderer.h"

#include <stdio.h>
#include <unistd.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Surface *window_surface = NULL;
static SDL_Surface *buffer_surface = NULL;
static SDL_Rect renderRect = {.x = 0, .y = 0};
static fire_renderer_t fire_renderer;

static int process_additional_args(int argc, char **argv)
{
    (void)argv;

    if (argc > 3)
        return 1;

    return 0;
}

static int init(const doom_fire_buffer_t *const buffer)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_CreateWindowAndRenderer(buffer->width, buffer->height, SDL_WINDOW_RESIZABLE, &window, &renderer);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window_surface = SDL_GetWindowSurface(window);
    if (window_surface == NULL)
    {
        printf("Window surface could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    buffer_surface = SDL_CreateRGBSurface(0, buffer->width, buffer->height, 32, 0, 0, 0, 0);
    if (buffer_surface == NULL)
    {
        printf("Buffer surface could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GetWindowSize(window, &renderRect.w, &renderRect.h);
    return 0;
}

static int get_max_ignition_value()
{
    int palette_size = palette_get_size();
    return palette_size - 1;
}

static void draw_buffer(doom_fire_buffer_t *const buffer)
{
    for (int y = 0; y < buffer->height; y++)
    {
        for (int x = 0; x < buffer->width; x++)
        {
            int pixel = buffer->data[x + (y * buffer->width)];
            int palette_index = pixel * 3;
            Uint8 r = DOOM_RGB_VALUES[palette_index];
            Uint8 g = DOOM_RGB_VALUES[palette_index + 1];
            Uint8 b = DOOM_RGB_VALUES[palette_index + 2];

            Uint8 *buffer_pixels = (Uint8 *)buffer_surface->pixels;
            Uint32 *target_pixel = (Uint32 *)(buffer_pixels + y * buffer_surface->pitch + x * sizeof(*target_pixel));

            *target_pixel = r << 16 | g << 8 | b;
        }
    }

    SDL_BlitScaled(buffer_surface, NULL, window_surface, &renderRect);
    SDL_UpdateWindowSurface(window);
}

static void wait()
{
    usleep(1000);
}

static bool exit_requested()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
            return true;

        // Seems like this can hang out here.
        if (e.type == SDL_WINDOWEVENT)
        {
            if (e.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                SDL_FreeSurface(window_surface);
                window_surface = SDL_GetWindowSurface(window);
                SDL_GetWindowSize(window, &renderRect.w, &renderRect.h);
            }
        }
    }
    return false;
}

static void cleanup_renderer()
{
    SDL_FreeSurface(buffer_surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    buffer_surface = NULL;
    renderer = NULL;
    window_surface = NULL;
    window = NULL;

    SDL_Quit();
}

fire_renderer_t sdl_get_renderer(void)
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
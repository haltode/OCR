#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>

#include "../utils/image.h"

static bool is_blank_column(SDL_Surface *line, int width)
{
    bool is_blank = true;
    for (int h = 0; h < line->h && is_blank; h++)
        if (!is_white_pixel(line, width, h))
            is_blank = false;
    return is_blank;
}

static void draw_red_column(SDL_Surface *line, int width)
{
    for (int h = 0; h < line->h; h++)
    {
        Uint32 red_pixel = SDL_MapRGB(line->format, 255, 0, 0);
        image_set_pixel(line, width, h, red_pixel);
    }
}

void detect_chars(SDL_Surface *line)
{
    int w = 0;
    while (w < line->w)
    {
        while (w < line->w && is_blank_column(line, w))
            w++;
        if (w > 0 && w < line->w)
            draw_red_column(line, w);

        while (w < line->w && !is_blank_column(line, w))
            w++;
        if (w < line->w)
            draw_red_column(line, w);

        w++;
    }
}

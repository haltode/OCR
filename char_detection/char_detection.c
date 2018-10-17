#include <SDL/SDL.h>

#include "../utils/image.h"

static bool is_blank_column(SDL_Surface *image, int width, int hstart, int hend)
{
    bool is_blank = true;
    for (int h = hstart; h < hend && is_blank; h++)
        if (!is_white_pixel(image, width, h))
            is_blank = false;
    return is_blank;
}

static void draw_red_column(SDL_Surface *image, int width, int hstart, int hend)
{
    for (int h = hstart; h < hend; h++)
    {
        Uint32 red_pixel = SDL_MapRGB(image->format, 255, 0, 0);
        image_set_pixel(image, width, h, red_pixel);
    }
}

void char_detection(SDL_Surface *image, int line_start, int line_end)
{
    int w = 0;
    while (w < image->w)
    {
        while (w < image->w && is_blank_column(image, w, line_start, line_end))
            w++;
        if (w > 0 && w < image->w)
            draw_red_column(image, w - 1, line_start, line_end);

        while (w < image->w && !is_blank_column(image, w, line_start, line_end))
            w++;
        if (w < image->w)
            draw_red_column(image, w, line_start, line_end);

        w++;
    }
}

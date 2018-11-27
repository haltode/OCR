#include "image.h"
#include "sdl.h"

bool is_white_pixel(SDL_Surface *image, int h, int w)
{
    Uint8 r, g, b;
    Uint32 pixel = image_get_pixel(image, h, w);
    SDL_GetRGB(pixel, image->format, &r, &g, &b);
    return r == 255 && g == 255 && b == 255;
}

bool is_blank_line(SDL_Surface *text, int height)
{
    bool is_blank = true;
    for (int w = 0; w < text->w && is_blank; w++)
        if (!is_white_pixel(text, height, w))
            is_blank = false;
    return is_blank;
}

bool is_blank_column(SDL_Surface *line, int width)
{
    bool is_blank = true;
    for (int h = 0; h < line->h && is_blank; h++)
        if (!is_white_pixel(line, h, width))
            is_blank = false;
    return is_blank;
}

void draw_red_line(SDL_Surface *text, int height)
{
    for (int w = 0; w < text->w; w++)
    {
        Uint32 red_pixel = SDL_MapRGB(text->format, 255, 0, 0);
        image_set_pixel(text, height, w, red_pixel);
    }
}

void draw_red_column(SDL_Surface *line, int width)
{
    for (int h = 0; h < line->h; h++)
    {
        Uint32 red_pixel = SDL_MapRGB(line->format, 255, 0, 0);
        image_set_pixel(line, h, width, red_pixel);
    }
}

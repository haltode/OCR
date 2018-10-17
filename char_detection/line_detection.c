#include <err.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../preprocessing/preprocessing.h"
#include "../utils/image.h"
#include "char_detection.h"

static bool is_blank_line(SDL_Surface *image, int height)
{
    bool is_blank = true;
    for (int w = 0; w < image->w && is_blank; w++)
        if (!is_white_pixel(image, w, height))
            is_blank = false;
    return is_blank;
}

static void draw_red_line(SDL_Surface *image, int height)
{
    for (int w = 0; w < image->w; w++)
    {
        Uint32 red_pixel = SDL_MapRGB(image->format, 255, 0, 0);
        image_set_pixel(image, w, height, red_pixel);
    }
}

void line_detection(const char *input_path, const char *output_path)
{
    SDL_Surface *image = SDL_LoadBMP(input_path);
    if (image == NULL)
        errx(3, "cannot load %s: %s", input_path, IMG_GetError());

    int h = 0;
    while (h < image->h)
    {
        int line_start = 0;
        while (h < image->h && is_blank_line(image, h))
            h++;
        if (h > 0 && h < image->h)
        {
            draw_red_line(image, h - 1);
            line_start = h;
        }

        while (h < image->h && !is_blank_line(image, h))
            h++;
        if (h < image->h)
        {
            char_detection(image, line_start, h);
            draw_red_line(image, h);
        }

        h++;
    }

    SDL_SaveBMP(image, output_path);
}

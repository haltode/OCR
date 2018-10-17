#include <err.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../utils/image.h"

void image_grayscale(const char *input_path, const char *output_path)
{
    SDL_Surface *image = IMG_Load(input_path);
    if (image == NULL)
        errx(3, "cannot load %s: %s", input_path, IMG_GetError());

    for (int w = 0; w < image->w; w++)
    {
        for (int h = 0; h < image->h; h++)
        {
            Uint8 r, g, b;
            Uint32 pixel = image_get_pixel(image, w, h);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            Uint8 avg = 0.2126 * r + 0.7152 * g + 0.0722 * b;

            Uint32 new_pixel = SDL_MapRGB(image->format, avg, avg, avg);
            image_set_pixel(image, w, h, new_pixel);
        }
    }

    SDL_SaveBMP(image, output_path);
}

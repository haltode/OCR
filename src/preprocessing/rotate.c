#include <SDL2/SDL.h>

#include "../utils/math.h"
#include "../utils/sdl.h"

SDL_Surface *image_rotate(SDL_Surface *image, double angle)
{
    angle = to_radians(-angle);
    double cos_ang = cos(angle);
    double sin_ang = sin(angle);

    int new_height = abs(-image->w * sin_ang) + abs(image->h * cos_ang);
    int new_width = abs(image->w * cos_ang) + abs(image->h * sin_ang);
    SDL_Surface *output = image_new(new_height, new_width);

    for (int h = 0; h < output->h; h++)
    {
        for (int w = 0; w < output->w; w++)
        {
            int nh =
                (h - output->h / 2) * cos_ang - (w - output->w / 2) * sin_ang;
            int nw =
                (w - output->w / 2) * cos_ang + (h - output->h / 2) * sin_ang;

            nh += image->h / 2;
            nw += image->w / 2;

            if (nh > 0 && nh < image->h && nw > 0 && nw < image->w)
            {
                Uint32 pixel = image_get_pixel(image, nh, nw);
                image_set_pixel(output, h, w, pixel);
            }
            else
            {
                Uint32 white_pixel = SDL_MapRGB(output->format, 255, 255, 255);
                image_set_pixel(output, h, w, white_pixel);
            }
        }
    }

    return output;
}

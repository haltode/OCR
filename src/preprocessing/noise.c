#include "../utils/image.h"
#include "../utils/sdl.h"
#include "preprocessing.h"

const int delta[8][2] =
    {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

// Block-matching noise reduction
void image_noise_reduction(SDL_Surface *image)
{
    SDL_Surface *output = image_new(image->h, image->w);

    for (int h = 0; h < image->h; h++)
    {
        for (int w = 0; w < image->w; w++)
        {
            int sum = 0;
            for (int dir = 0; dir < 8; dir++)
            {
                int nh = h + delta[dir][0];
                int nw = w + delta[dir][1];
                if (nh >= 0 && nh < image->h && nw >= 0 && nw < image->w)
                    sum += is_white_pixel(image, nh, nw);
            }

            Uint32 white_pixel = SDL_MapRGB(image->format, 255, 255, 255);
            Uint32 black_pixel = SDL_MapRGB(image->format, 0, 0, 0);
            if (sum > 4)
                image_set_pixel(output, h, w, white_pixel);
            else
                image_set_pixel(output, h, w, black_pixel);
        }
    }

    image_copy(output, image);
    SDL_FreeSurface(output);
}

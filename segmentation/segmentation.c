#include <err.h>

#include "segmentation.h"

void image_segmentation(const char *input_path, const char *output_path)
{
    SDL_Surface *image = SDL_LoadBMP(input_path);
    if (image == NULL)
        errx(3, "cannot load %s: %s", input_path, SDL_GetError());

    detect_lines(image);

    SDL_SaveBMP(image, output_path);
}

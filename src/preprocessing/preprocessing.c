#include <err.h>

#include <SDL2/SDL_image.h>

#include "preprocessing.h"

const char *g_grayscale_img_path = "output/image_grayscale.bmp";
const char *g_binarize_img_path = "output/image_binarize.bmp";

void preprocessing(const char *image_path)
{
    SDL_Surface *image = IMG_Load(image_path);
    if (image == NULL)
        errx(3, "cannot load %s: %s", image_path, IMG_GetError());

    image_grayscale(image);
    SDL_SaveBMP(image, g_grayscale_img_path);

    image_binarize(image);
    SDL_SaveBMP(image, g_binarize_img_path);

    SDL_FreeSurface(image);
}

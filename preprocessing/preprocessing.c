#include <err.h>

#include <SDL/SDL.h>

#include "binarization.h"
#include "grayscale.h"

void preprocessing(const char *image_path)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1, "could not initialize SDL: %s.\n", SDL_GetError());

    const char *grayscale_img_path = "output/image_grayscale.bmp";
    const char *binarize_img_path = "output/image_binarize.bmp";

    image_grayscale(image_path, grayscale_img_path);
    image_binarize(grayscale_img_path, binarize_img_path);
}

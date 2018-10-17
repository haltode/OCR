#include <err.h>

#include <SDL/SDL.h>

#include "binarization.h"
#include "grayscale.h"

const char *g_grayscale_img_path = "output/image_grayscale.bmp";
const char *g_binarize_img_path = "output/image_binarize.bmp";

void preprocessing(const char *image_path)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1, "could not initialize SDL: %s.\n", SDL_GetError());

    image_grayscale(image_path, g_grayscale_img_path);
    image_binarize(g_grayscale_img_path, g_binarize_img_path);
}

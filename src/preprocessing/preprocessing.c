#include <err.h>

#include <SDL/SDL_image.h>

#include "../segmentation/segmentation.h"
#include "preprocessing.h"

const char *g_grayscale_img_path = "output/image_grayscale.bmp";
const char *g_binarize_img_path = "output/image_binarize.bmp";
const char *g_segmentation_img_path = "output/image_segmentation.bmp";

void preprocessing(const char *image_path)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(1, "could not initialize SDL: %s.\n", SDL_GetError());

    SDL_Surface *image = IMG_Load(image_path);
    if (image == NULL)
        errx(3, "cannot load %s: %s", image_path, IMG_GetError());

    image_grayscale(image);
    SDL_SaveBMP(image, g_grayscale_img_path);

    image_binarize(image);
    SDL_SaveBMP(image, g_binarize_img_path);

    image_segmentation(image);
    SDL_SaveBMP(image, g_segmentation_img_path);

    SDL_FreeSurface(image);
    SDL_Quit();
}

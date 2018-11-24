#include <err.h>

#include <SDL2/SDL_image.h>

#include "../preprocessing/preprocessing.h"
#include "segmentation.h"

const char *g_segmentation_img_path = "output/image_segmentation.bmp";

int segmentation(void)
{
    SDL_Surface *image = IMG_Load(g_binarize_img_path);
    if (image == NULL)
        errx(3, "cannot load %s: %s", g_binarize_img_path, IMG_GetError());

    int nb_chars_found = 0;
    detect_lines(image, &nb_chars_found);
    SDL_SaveBMP(image, g_segmentation_img_path);
    SDL_FreeSurface(image);

    return nb_chars_found;
}

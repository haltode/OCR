#include "../constants.h"
#include "../utils/image.h"
#include "preprocessing.h"

void preprocessing(const char *image_path)
{
    SDL_Surface *image = image_load(image_path);

    image_grayscale(image);
    SDL_SaveBMP(image, g_path_img_grayscale);

    image_binarize(image);
    SDL_SaveBMP(image, g_path_img_binarize);

    SDL_FreeSurface(image);
}

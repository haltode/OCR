#include "../utils/constants.h"
#include "../utils/sdl.h"
#include "preprocessing.h"

void preprocessing(const char *image_path)
{
    SDL_Surface *image = image_load(image_path);

    image_grayscale(image);
    SDL_SaveBMP(image, g_path_img_grayscale);

    image_binarize(image);
    SDL_SaveBMP(image, g_path_img_binarize);

    image_deskew(image);
    SDL_SaveBMP(image, g_path_img_deskew);

    image_noise_reduction(image);
    SDL_SaveBMP(image, g_path_img_noise_reduc);

    SDL_FreeSurface(image);
}

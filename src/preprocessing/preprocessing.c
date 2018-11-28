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

    SDL_Surface *final_image = image_deskew(image);
    SDL_SaveBMP(final_image, g_path_img_deskew);

    SDL_FreeSurface(image);
    SDL_FreeSurface(final_image);
}

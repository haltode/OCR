#include "../preprocessing/preprocessing.h"
#include "../utils/constants.h"
#include "../utils/image.h"
#include "segmentation.h"

int segmentation(void)
{
    SDL_Surface *image = image_load(g_path_img_binarize);

    int nb_chars_found = 0;
    detect_lines(image, &nb_chars_found);
    SDL_SaveBMP(image, g_path_img_segmentation);
    SDL_FreeSurface(image);

    return nb_chars_found;
}

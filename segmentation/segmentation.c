#include "segmentation.h"

void image_segmentation(SDL_Surface *binarize_image)
{
    detect_lines(binarize_image);
}

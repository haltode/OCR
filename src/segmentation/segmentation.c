#include "../preprocessing/preprocessing.h"
#include "../utils/constants.h"
#include "../utils/sdl.h"
#include "segmentation.h"

struct PageAnalysis *segmentation(void)
{
    struct PageAnalysis *page_analysis = malloc(sizeof(struct PageAnalysis));

    SDL_Surface *image = image_load(g_path_img_noise_reduc);
    detect_lines(image, page_analysis);

    SDL_SaveBMP(image, g_path_img_segmentation);
    SDL_FreeSurface(image);

    return page_analysis;
}

#include <err.h>

#include <SDL/SDL.h>

#include "../char_detection/char_detection.h"
#include "binarization.h"
#include "grayscale.h"

const char *g_grayscale_img_path = "output/image_grayscale.bmp";
const char *g_binarize_img_path = "output/image_binarize.bmp";
const char *g_detect_chars_img_path = "output/image_detect_chars.bmp";

void preprocessing(const char *image_path)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1, "could not initialize SDL: %s.\n", SDL_GetError());

    image_grayscale(image_path, g_grayscale_img_path);
    image_binarize(g_grayscale_img_path, g_binarize_img_path);

    line_detection(g_binarize_img_path, g_detect_chars_img_path);
}

#include <err.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../preprocessing/preprocessing.h"
#include "../utils/image.h"

const char *g_detect_lines_img_path = "output/image_detect_lines.bmp";

void line_detection(void)
{
    SDL_Surface *image = SDL_LoadBMP(g_binarize_img_path);
    if (image == NULL)
        errx(3, "cannot load %s: %s", g_binarize_img_path, IMG_GetError());

    int h = 0;
    while (h < image->h)
    {
        while (h < image->h && is_blank_line(image, h))
            h++;
        if (h > 0 && h < image->h)
            draw_red_line(image, h - 1);

        while (h < image->h && !is_blank_line(image, h))
            h++;
        if (h < image->h)
            draw_red_line(image, h);

        h++;
    }

    SDL_SaveBMP(image, g_detect_lines_img_path);
}

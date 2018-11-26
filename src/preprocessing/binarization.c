#include <stdlib.h>

#include "../utils/image.h"

static int *get_histogram(SDL_Surface *image)
{
    int *histogram = calloc(256, sizeof(int));
    for (int h = 0; h < image->h; h++)
    {
        for (int w = 0; w < image->w; w++)
        {
            Uint8 r, g, b;
            Uint32 pixel = image_get_pixel(image, h, w);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            // This is a grayscale image so we have r = g = b
            histogram[r]++;
        }
    }
    return histogram;
}

// Otsu's method for adaptive threshold
static int get_threshold(SDL_Surface *image)
{
    int threshold = 0;
    double current_max = 0.;
    int sum = 0;
    int sum_background = 0;
    int weight_background = 0;
    int nb_pixels = image->h * image->w;

    int *histogram = get_histogram(image);
    for (int i = 0; i < 256; i++)
        sum += i * histogram[i];

    for (int i = 0; i < 256; i++)
    {
        weight_background += histogram[i];
        int weight_foreground = nb_pixels - weight_background;
        if (weight_background == 0 || weight_foreground == 0)
            continue;

        sum_background += i * histogram[i];
        int sum_foreground = sum - sum_background;

        double f_weight_background = weight_background;
        double f_weight_foreground = weight_foreground;
        double mean_background = sum_background / f_weight_background;
        double mean_foreground = sum_foreground / f_weight_foreground;
        double mean_diff = mean_background - mean_foreground;

        double variance = f_weight_background *
                          f_weight_foreground *
                          mean_diff * mean_diff;
        if (variance > current_max)
        {
            current_max = variance;
            threshold = i;
        }
    }

    free(histogram);

    return threshold;
}

void image_binarize(SDL_Surface *image)
{
    int threshold = get_threshold(image);

    for (int h = 0; h < image->h; h++)
    {
        for (int w = 0; w < image->w; w++)
        {
            Uint8 r, g, b;
            Uint32 pixel = image_get_pixel(image, h, w);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            Uint32 new_pixel;
            if (r > threshold)
                new_pixel = SDL_MapRGB(image->format, 255, 255, 255);
            else
                new_pixel = SDL_MapRGB(image->format, 0, 0, 0);
            image_set_pixel(image, h, w, new_pixel);
        }
    }
}

#include <err.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../utils/image.h"

const char *grayscale_img_path = "output/image_grayscale.bmp";
const char *binarize_img_path = "output/image_binarize.bmp";

static void grayscale_image(const char *input_path)
{
    SDL_Surface *image = IMG_Load(input_path);
    if (image == NULL)
        errx(3, "cannot load %s: %s", input_path, IMG_GetError());

    for (int w = 0; w < image->w; w++)
    {
        for (int h = 0; h < image->h; h++)
        {
            Uint8 r, g, b;
            Uint32 pixel = image_get_pixel(image, w, h);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            Uint8 avg = 0.2126 * r + 0.7152 * g + 0.0722 * b;

            Uint32 new_pixel = SDL_MapRGB(image->format, avg, avg, avg);
            image_set_pixel(image, w, h, new_pixel);
        }
    }

    SDL_SaveBMP(image, grayscale_img_path);
}

static int otsu_method(int histogram[256], int nb_pixels)
{
    int threshold = 0;
    double current_max = 0.;
    int sum = 0;
    int sum_background = 0;
    int weight_background = 0;

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

        double mean_background = sum_background / (double) weight_background;
        double mean_foreground = sum_foreground / (double) weight_foreground;
        double mean_diff = mean_background - mean_foreground;

        double variance = (double) weight_background *
                          (double) weight_foreground *
                          mean_diff * mean_diff;
        if (variance > current_max)
        {
            current_max = variance;
            threshold = i;
        }
    }

    return threshold;
}

static void binarize_image(void)
{
    SDL_Surface *image = SDL_LoadBMP(grayscale_img_path);
    int histogram[256];

    for (int i = 0; i < 256; i++)
        histogram[i] = 0;

    for (int w = 0; w < image->w; w++)
    {
        for (int h = 0; h < image->h; h++)
        {
            Uint8 r, g, b;
            Uint32 pixel = image_get_pixel(image, w, h);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            // grayscale image so we have r = g = b
            histogram[r]++;
        }
    }

    int nb_pixels = image->w * image->h;
    int threshold = otsu_method(histogram, nb_pixels);

    for (int w = 0; w < image->w; w++)
    {
        for (int h = 0; h < image->h; h++)
        {
            Uint8 r, g, b;
            Uint32 pixel = image_get_pixel(image, w, h);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            // grayscale image so we have r = g = b
            Uint32 new_pixel;
            if (r > threshold)
                new_pixel = SDL_MapRGB(image->format, 255, 255, 255);
            else
                new_pixel = SDL_MapRGB(image->format, 0, 0, 0);
            image_set_pixel(image, w, h, new_pixel);
        }
    }

    SDL_SaveBMP(image, binarize_img_path);
}

void preprocessing(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1, "could not initialize SDL: %s.\n", SDL_GetError());

    grayscale_image("output/image.png");
    binarize_image();
}

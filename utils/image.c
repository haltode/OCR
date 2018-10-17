#include "image.h"

static Uint8* image_get_pixel_ref(SDL_Surface *image, int x, int y)
{
    int bpp = image->format->BytesPerPixel;
    Uint8 *pixels = image->pixels;
    return pixels + y * image->pitch + x * bpp;
}

Uint32 image_get_pixel(SDL_Surface *image, int x, int y)
{
    Uint8 *p = image_get_pixel_ref(image, x, y);

    switch (image->format->BytesPerPixel)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *) p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *) p;
        break;

    default:
        return 0;
    }
}

void image_set_pixel(SDL_Surface *image, int x, int y, Uint32 pixel)
{
    Uint8 *p = image_get_pixel_ref(image, x, y);

    switch (image->format->BytesPerPixel)
    {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *) p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else
        {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *) p = pixel;
        break;

    default:
        break;
    }
}

bool is_white_pixel(SDL_Surface *image, int x, int y)
{
    Uint8 r, g, b;
    Uint32 pixel = image_get_pixel(image, x, y);
    SDL_GetRGB(pixel, image->format, &r, &g, &b);
    return r == 255 && g == 255 && b == 255;
}

bool is_blank_line(SDL_Surface *image, int height)
{
    bool is_blank_line = true;
    for (int w = 0; w < image->w && is_blank_line; w++)
        if (!is_white_pixel(image, w, height))
            is_blank_line = false;
    return is_blank_line;
}

void draw_red_line(SDL_Surface *image, int height)
{
    for (int w = 0; w < image->w; w++)
    {
        Uint32 red_pixel = SDL_MapRGB(image->format, 255, 0, 0);
        image_set_pixel(image, w, height, red_pixel);
    }
}

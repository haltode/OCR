#include <err.h>

#include <SDL2/SDL_image.h>

#include "sdl.h"

SDL_Surface *image_load(const char *path)
{
    SDL_Surface *image = IMG_Load(path);
    if (image == NULL)
        errx(3, "cannot load %s: %s", path, IMG_GetError());
    return image;
}

SDL_Surface *image_new(const int height, const int width)
{
    SDL_Rect dim;
    dim.y = 0;
    dim.x = 0;
    dim.h = height;
    dim.w = width;
    SDL_Surface *surface =
        SDL_CreateRGBSurface(0, dim.w, dim.h, 32, 0, 0, 0, 0);
    return surface;
}

// http://sdl.beuc.net/sdl.wiki/Pixel_Access
static Uint8* image_get_pixel_ref(SDL_Surface *image, int h, int w)
{
    int bpp = image->format->BytesPerPixel;
    Uint8 *pixels = image->pixels;
    return pixels + h * image->pitch + w * bpp;
}

Uint32 image_get_pixel(SDL_Surface *image, int h, int w)
{
    Uint8 *p = image_get_pixel_ref(image, h, w);

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

void image_set_pixel(SDL_Surface *image, int h, int w, Uint32 pixel)
{
    Uint8 *p = image_get_pixel_ref(image, h, w);

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

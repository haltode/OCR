#ifndef IMAGE_H
#define IMAGE_H

#include <SDL/SDL.h>

Uint32 image_get_pixel(SDL_Surface *image, int x, int y);
void image_set_pixel(SDL_Surface *image, int x, int y, Uint32 pixel);

#endif

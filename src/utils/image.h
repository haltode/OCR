#ifndef UTILS_IMAGE_H
#define UTILS_IMAGE_H

#include <stdbool.h>

#include <SDL2/SDL.h>

bool is_white_pixel(SDL_Surface *image, int h, int w);
bool is_blank_line(SDL_Surface *text, int height);
bool is_blank_column(SDL_Surface *line, int width);

void draw_line(
    SDL_Surface *image, Uint32 pixel, int height, int w_start, int w_end);
void draw_column(
    SDL_Surface *image, Uint32 pixel, int width, int h_start, int h_end);

#endif

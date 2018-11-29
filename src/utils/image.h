#ifndef UTILS_IMAGE_H
#define UTILS_IMAGE_H

#include <stdbool.h>

#include <SDL2/SDL.h>

bool is_white_pixel(SDL_Surface *image, int h, int w);
bool is_blank_line(SDL_Surface *text, int height);
bool is_blank_column(SDL_Surface *line, int width);

void draw_red_line(SDL_Surface *text, int height);
void draw_red_column(SDL_Surface *line, int width);

#endif

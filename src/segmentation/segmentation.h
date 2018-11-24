#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <SDL2/SDL.h>

void image_segmentation(SDL_Surface *binarize_image);
void detect_lines(SDL_Surface *text);
void detect_chars(SDL_Surface *line);

#endif

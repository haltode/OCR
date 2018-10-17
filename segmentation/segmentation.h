#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <SDL/SDL.h>

void image_segmentation(const char *input_path, const char *output_path);
void detect_lines(SDL_Surface *text);
void detect_chars(SDL_Surface *line);

#endif

#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <SDL2/SDL.h>

int segmentation(void);
void detect_lines(SDL_Surface *text, int *char_cnt);
void detect_chars(SDL_Surface *line, int *char_cnt);

#endif

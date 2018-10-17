#ifndef CHAR_DETECTION_H
#define CHAR_DETECTION_H

#include <SDL/SDL.h>

void char_detection(SDL_Surface *image, int line_start, int line_end);
void line_detection(const char *input_path, const char *output_path);

#endif

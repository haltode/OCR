#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <SDL2/SDL.h>

void preprocessing(const char *image_path);

void image_grayscale(SDL_Surface *image);
void image_binarize(SDL_Surface *image);
SDL_Surface *image_deskew(SDL_Surface *image);
SDL_Surface *image_noise_reduction(SDL_Surface *image);

#endif

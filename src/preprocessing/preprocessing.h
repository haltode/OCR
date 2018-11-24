#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <SDL2/SDL.h>

extern const char *g_grayscale_img_path;
extern const char *g_binarize_img_path;
extern const char *g_segmentation_img_path;

void preprocessing(const char *image_path);

void image_grayscale(SDL_Surface *image);
void image_binarize(SDL_Surface *image);

#endif

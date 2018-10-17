#ifndef PREPROCESSING_H
#define PREPROCESSING_H

extern const char *g_grayscale_img_path;
extern const char *g_binarize_img_path;
extern const char *g_segmentation_img_path;

void preprocessing(const char *image_path);

void image_grayscale(const char *input_path, const char *output_path);
void image_binarize(const char *input_path, const char *output_path);

#endif

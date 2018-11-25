#include "convert.h"
#include "image.h"

struct Matrix *convert_image_to_matrix(SDL_Surface *image)
{
    struct Matrix *matrix = matrix_alloc(image->h * image->w, 1);
    for (int h = 0; h < image->h; h++)
    {
        for (int w = 0; w < image->w; w++)
        {
            float val = (is_white_pixel(image, h, w)) ? 0. : 1.;
            matrix_set(matrix, h * image->w + w, 0, val);
        }
    }
    return matrix;
}

const size_t g_charset_size = 76;
const char *g_charset =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    ".,!?:;/+-=\"\'()";

struct Matrix *convert_char_to_matrix(char c)
{
    struct Matrix *matrix = matrix_alloc(g_charset_size, 1);
    for (size_t pos = 0; g_charset[pos] != '\0'; pos++)
    {
        if (g_charset[pos] == c)
        {
            matrix_set(matrix, pos, 0, 1.);
            break;
        }
    }
    return matrix;
}

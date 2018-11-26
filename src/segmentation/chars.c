#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>

#include "../utils/constants.h"
#include "../utils/image.h"

static bool is_blank_column(SDL_Surface *line, int width)
{
    bool is_blank = true;
    for (int h = 0; h < line->h && is_blank; h++)
        if (!is_white_pixel(line, h, width))
            is_blank = false;
    return is_blank;
}

static void draw_red_column(SDL_Surface *line, int width)
{
    for (int h = 0; h < line->h; h++)
    {
        Uint32 red_pixel = SDL_MapRGB(line->format, 255, 0, 0);
        image_set_pixel(line, h, width, red_pixel);
    }
}

static void extract_chars_from_line(SDL_Surface *line,
    int col_start, int col_end, int *char_cnt)
{
    SDL_Rect char_rect;
    char_rect.y = 0;
    char_rect.x = col_start;
    char_rect.h = line->h;
    char_rect.w = col_end - col_start + 1;

    SDL_Rect scaled_rect;
    scaled_rect.y = 0;
    scaled_rect.x = 0;
    scaled_rect.h = 32;
    scaled_rect.w = 32;

    SDL_Surface *scaled_char =
        SDL_CreateRGBSurface(0, scaled_rect.w, scaled_rect.h, 32, 0, 0, 0, 0);

    SDL_BlitScaled(line, &char_rect, scaled_char, &scaled_rect);

    char output_path[128];
    sprintf(output_path, "%s/char%d.bmp", g_path_img_chars, *char_cnt);
    SDL_SaveBMP(scaled_char, output_path);
    (*char_cnt)++;

    SDL_FreeSurface(scaled_char);
}

void detect_chars(SDL_Surface *line, int *char_cnt)
{
    int w = 0;
    while (w < line->w)
    {
        int col_start = 0;
        while (w < line->w && is_blank_column(line, w))
            w++;
        if (w > 0 && w < line->w)
        {
            col_start = w;
            draw_red_column(line, w - 1);
        }

        int col_end = 0;
        while (w < line->w && !is_blank_column(line, w))
            w++;
        if (w < line->w)
        {
            col_end = w;
            extract_chars_from_line(line, col_start, col_end, char_cnt);
            draw_red_column(line, w);
        }

        w++;
    }
}

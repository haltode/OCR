#include <err.h>

#include "../utils/image.h"
#include "segmentation.h"

static bool is_blank_line(SDL_Surface *text, int height)
{
    bool is_blank = true;
    for (int w = 0; w < text->w && is_blank; w++)
        if (!is_white_pixel(text, w, height))
            is_blank = false;
    return is_blank;
}

static void draw_red_line(SDL_Surface *text, int height)
{
    for (int w = 0; w < text->w; w++)
    {
        Uint32 red_pixel = SDL_MapRGB(text->format, 255, 0, 0);
        image_set_pixel(text, w, height, red_pixel);
    }
}

static void draw_chars_boxes(SDL_Surface *text, int line_start, int line_end)
{
    SDL_Rect line_rect;
    line_rect.x = 0;
    line_rect.y = line_start;
    line_rect.w = text->w;
    line_rect.h = line_end - line_start + 1;
    SDL_Surface *line =
        SDL_CreateRGBSurface(0, line_rect.w, line_rect.h, 32, 0, 0, 0, 0);

    SDL_BlitSurface(text, &line_rect, line, NULL);
    detect_chars(line);
    SDL_BlitSurface(line, NULL, text, &line_rect);

    SDL_FreeSurface(line);
}

void detect_lines(SDL_Surface *text)
{
    int h = 0;
    while (h < text->h)
    {
        int line_start = 0;
        while (h < text->h && is_blank_line(text, h))
            h++;
        if (h > 0 && h < text->h)
        {
            line_start = h;
            draw_red_line(text, h - 1);
        }

        int line_end = 0;
        while (h < text->h && !is_blank_line(text, h))
            h++;
        if (h < text->h)
        {
            line_end = h;
            draw_chars_boxes(text, line_start, line_end);
            draw_red_line(text, h);
        }

        h++;
    }
}

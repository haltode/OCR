#include "../utils/constants.h"
#include "../utils/image.h"
#include "segmentation.h"

static int go_to_char_start(SDL_Surface *line, int w)
{
    while (w < line->w && is_blank_column(line, w))
        w++;
    return w;
}

static int go_to_char_end(SDL_Surface *line, int w)
{
    while (w < line->w && !is_blank_column(line, w))
        w++;
    return w;
}

static void extract_char_from_line(
    SDL_Surface *line, size_t line_id,
    struct CharAnalysis char_analysis, size_t char_id)
{
    SDL_Rect char_rect;
    char_rect.y = 0;
    char_rect.x = char_analysis.col_start;
    char_rect.h = line->h;
    char_rect.w = char_analysis.col_end - char_analysis.col_start + 1;

    SDL_Rect scaled_rect;
    scaled_rect.y = 0;
    scaled_rect.x = 0;
    scaled_rect.h = 32;
    scaled_rect.w = 32;

    SDL_Surface *scaled_char =
        SDL_CreateRGBSurface(0, scaled_rect.w, scaled_rect.h, 32, 0, 0, 0, 0);
    SDL_BlitScaled(line, &char_rect, scaled_char, &scaled_rect);

    char output_path[128];
    sprintf(output_path,
        "%s/line_%zu_char_%zu.bmp", g_path_img_chars, line_id, char_id);
    SDL_SaveBMP(scaled_char, output_path);

    SDL_FreeSurface(scaled_char);
}

void detect_chars(
    SDL_Surface *line, struct LineAnalysis *line_analysis, size_t line_id)
{
    line_analysis->nb_chars = 0;

    for (int w = 0; w < line->w; w++)
    {
        struct CharAnalysis char_analysis;
        size_t char_id = line_analysis->nb_chars;

        w = go_to_char_start(line, w);
        if (w > 0 && w < line->w)
        {
            char_analysis.col_start = w;
            draw_red_column(line, w - 1);

            w = go_to_char_end(line, w);
            if (w < line->w)
            {
                char_analysis.col_end = w;
                extract_char_from_line(line, line_id, char_analysis, char_id);
                draw_red_column(line, w);

                line_analysis->chars[char_id] = char_analysis;
                (line_analysis->nb_chars)++;
            }
        }
    }
}

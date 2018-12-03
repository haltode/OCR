#include "../utils/image.h"
#include "segmentation.h"

static int go_to_line_start(SDL_Surface *text, int h)
{
    while (h < text->h && is_blank_line(text, h))
        h++;
    return h;
}

static int go_to_line_end(SDL_Surface *text, int h)
{
    while (h < text->h && !is_blank_line(text, h))
        h++;
    if (h < text->h)
        h--;
    return h;
}

static void extract_line_from_text(
    SDL_Surface *text, struct LineAnalysis *line_analysis, size_t line_id)
{
    SDL_Rect line_rect;
    line_rect.y = line_analysis->line_start;
    line_rect.x = 0;
    line_rect.h = line_analysis->line_end - line_analysis->line_start + 1;
    line_rect.w = text->w;

    SDL_Surface *line =
        SDL_CreateRGBSurface(0, line_rect.w, line_rect.h, 32, 0, 0, 0, 0);
    SDL_BlitSurface(text, &line_rect, line, NULL);

    detect_chars(line, line_analysis, line_id);

    SDL_FreeSurface(line);
}

void detect_lines(SDL_Surface *text, struct PageAnalysis *page_analysis)
{
    page_analysis->nb_lines = 0;

    for (int h = 0; h < text->h; h++)
    {
        struct LineAnalysis line_analysis;
        size_t line_id = page_analysis->nb_lines;

        h = go_to_line_start(text, h);
        if (h > 0 && h < text->h)
        {
            line_analysis.line_start = h;

            h = go_to_line_end(text, h);
            if (h < text->h)
            {
                line_analysis.line_end = h;
                extract_line_from_text(text, &line_analysis, line_id);

                page_analysis->lines[line_id] = line_analysis;
                (page_analysis->nb_lines)++;
            }
        }
    }
}

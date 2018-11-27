#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <stdbool.h>
#include <stddef.h>

#include <SDL2/SDL.h>

#define NB_CHARS_MAX 256
#define NB_LINES_MAX 256

struct CharAnalysis
{
    int col_start;
    int col_end;
};

struct LineAnalysis
{
    int line_start;
    int line_end;
    size_t nb_chars;
    struct CharAnalysis chars[NB_CHARS_MAX];
};

struct PageAnalysis
{
    size_t nb_lines;
    struct LineAnalysis lines[NB_LINES_MAX];
};

struct PageAnalysis *segmentation(void);

void detect_lines(
    SDL_Surface *text, struct PageAnalysis *page_analysis);
void detect_chars(
    SDL_Surface *line, struct LineAnalysis *line_analysis, size_t line_id);

bool has_space_before_char(struct LineAnalysis *line, size_t char_id);
bool has_newline_before_line(struct PageAnalysis *page, size_t line_id);

#endif

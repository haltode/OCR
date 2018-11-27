#include <err.h>
#include <stdlib.h>

#include "neural_network/evaluate/evaluate.h"
#include "neural_network/neural_network.h"
#include "preprocessing/preprocessing.h"
#include "segmentation/segmentation.h"
#include "utils/constants.h"
#include "utils/convert.h"
#include "utils/sdl.h"

void ocr_run(const char *input_image)
{
    struct Network *network = network_load("output/ocr_network");
    FILE *f = fopen(g_path_ocr_output, "w");
    if (f == NULL)
        errx(1, "could not open %s", g_path_ocr_output);

    preprocessing(input_image);
    struct PageAnalysis *page_analysis = segmentation();

    char filename[128];
    for (size_t line_id = 0; line_id < page_analysis->nb_lines; line_id++)
    {
        if (has_newline_before_line(page_analysis, line_id))
            fprintf(f, "\n");

        struct LineAnalysis *line = &page_analysis->lines[line_id];
        for (size_t char_id = 0; char_id < line->nb_chars; char_id++)
        {
            if (has_space_before_char(line, char_id))
                fprintf(f, " ");

            sprintf(filename,
                "%s/line_%zu_char_%zu.bmp", g_path_img_chars, line_id, char_id);
            SDL_Surface *char_img = image_load(filename);

            struct Matrix *network_input = convert_image_to_matrix(char_img);
            struct Matrix *network_output = network_run(network, network_input);

            char c = convert_matrix_to_char(network_output);
            fprintf(f, "%c", c);

            matrix_free(network_input);
            SDL_FreeSurface(char_img);
        }

        fprintf(f, " ");
    }

    fclose(f);
    free(page_analysis);
    network_free(network);
}

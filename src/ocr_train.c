#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "neural_network/evaluate/evaluate.h"
#include "neural_network/training/training.h"
#include "preprocessing/preprocessing.h"
#include "segmentation/segmentation.h"
#include "utils/constants.h"
#include "utils/convert.h"
#include "utils/image.h"

#define TOTAL_PAGES 32
#define NB_CHARS_PER_PAGE 5000
#define TOTAL_CHARS (TOTAL_PAGES * NB_CHARS_PER_PAGE)

static void add_font_to_dataset(
    struct Dataset *full_set,
    const size_t font_id, const char *fontname)
{
    printf("adding font '%s' to dataset...\n", fontname);

    size_t char_cnt = 0;
    FILE *f = fopen(g_path_dataset_scrambled, "r");
    if (f == NULL)
        errx(1, "could not open %s", g_path_dataset_scrambled);

    char c;
    char filename[128];
    for (size_t page = 1; page <= TOTAL_PAGES; page++)
    {
        sprintf(filename, "dataset/%s/page-%02zu.png", fontname, page);

        preprocessing(filename);
        size_t nb_chars = segmentation();
        if (nb_chars != NB_CHARS_PER_PAGE)
            errx(1, "on page %zu: expected %d chars, found %zu.",
                     page, NB_CHARS_PER_PAGE, nb_chars);

        for (size_t char_id = 0; char_id < nb_chars; char_id++)
        {
            while ((c = fgetc(f)) != EOF)
                if (isgraph(c))
                    break;
            if (c == EOF)
                errx(1, "reached end of file before end of images");

            sprintf(filename, "%s/char%zu.bmp", g_path_img_chars, char_id);
            SDL_Surface *char_img = image_load(filename);

            struct Matrix *in = convert_image_to_matrix(char_img);
            struct Matrix *out = convert_char_to_matrix(c);

            struct ExampleData example = {in, out};
            size_t ex_id = char_cnt + font_id * TOTAL_CHARS;
            full_set->examples[ex_id] = example;
            char_cnt++;

            SDL_FreeSurface(char_img);
        }
    }

    while ((c = fgetc(f)) != EOF)
        if (isgraph(c))
        {
            warnx("reached end of images before end of file");
            break;
        }

    fclose(f);
    printf("characters read: %zu / %d\n", char_cnt, TOTAL_CHARS);
}

void ocr_train(void)
{
    struct Dataset *full_set = dataset_alloc(3 * TOTAL_CHARS);
    add_font_to_dataset(full_set, 0, "courier");
    add_font_to_dataset(full_set, 1, "dejavu_sans");
    add_font_to_dataset(full_set, 2, "droid_sans_mono");

    // train: 60%, validation: 20%, test: 20%
    struct Dataset *train_set = dataset_alloc(0.6 * full_set->nb_examples);
    struct Dataset *validation_set = dataset_alloc(0.2 * full_set->nb_examples);
    struct Dataset *test_set = dataset_alloc(0.2 * full_set->nb_examples);
    dataset_split(full_set, train_set, validation_set, test_set);

    printf("datasets sizes:\n"
           "full_set: %zu\n"
           "train_set: %zu\n"
           "validation_set: %zu\n"
           "test_set: %zu\n\n",
        full_set->nb_examples, train_set->nb_examples,
        validation_set->nb_examples, test_set->nb_examples);

    struct TrainingParams params;
    params.nb_examples = train_set->nb_examples;
    params.nb_epochs = 10;
    params.mini_batch_size = 50;
    params.learn_rate = 0.2;
    params.regularization_rate = 5;

    size_t input_size = 32 * 32;
    size_t output_size = g_charset_size;
    size_t layers_size[] = {input_size, 30, output_size};
    struct Network *network = network_alloc(3, layers_size);

    bool verbose = true;
    gradient_descent(network, params, train_set, validation_set, verbose);

    network_save(network, "output/ocr_network");

    network_evaluate(network, params, test_set, "test_set");

    dataset_free(full_set);
    dataset_free(train_set);
    dataset_free(validation_set);
    dataset_free(test_set);
    network_free(network);
}

#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "neural_network/evaluate.h"
#include "neural_network/training/training.h"
#include "preprocessing/preprocessing.h"
#include "segmentation/segmentation.h"
#include "utils/convert.h"

static struct Dataset *get_full_dataset(void)
{
    const size_t total_pages = 50;
    const size_t total_chars = 160000;

    struct Dataset *full_set = dataset_alloc(total_chars);
    size_t char_cnt = 0;

    FILE *lorem_ipsum = fopen("dataset/lorem_ipsum.txt", "r");
    if (lorem_ipsum == NULL)
        errx(1, "could not open lorem_ipsum file");

    char c;
    char filename[128];
    for (size_t page = 1; page <= total_pages; page++)
    {
        sprintf(filename, "dataset/courier/lorem_ipsum-%02zu.png", page);

        preprocessing(filename);
        size_t nb_chars = segmentation();

        for (size_t char_id = 0; char_id < nb_chars; char_id++)
        {
            while ((c = fgetc(lorem_ipsum)) != EOF)
                if (isgraph(c))
                    break;

            sprintf(filename, "output/chars/char%zu.bmp", char_id);
            SDL_Surface *char_img = IMG_Load(filename);
            if (char_img == NULL)
                errx(3, "cannot load %s: %s", filename, IMG_GetError());

            struct Matrix *in = convert_image_to_matrix(char_img);
            struct Matrix *out = convert_char_to_matrix(c);

            struct ExampleData example = {in, out};
            full_set->examples[char_cnt] = example;
            char_cnt++;

            SDL_FreeSurface(char_img);
        }

        printf("page %zu done: read %zu characters.\n", page, nb_chars);
    }

    fclose(lorem_ipsum);
    printf("total read: %zu / %zu.\n\n", char_cnt, total_chars);

    return full_set;
}

void ocr_train(void)
{
    struct Dataset *full_set = get_full_dataset();

    // train: 60%, validation: 20%, test: 20%
    struct Dataset *train_set = dataset_alloc(96000);
    struct Dataset *validation_set = dataset_alloc(32000);
    struct Dataset *test_set = dataset_alloc(32000);
    dataset_split(full_set, train_set, validation_set, test_set);

    struct TrainingParams params;
    params.nb_examples = train_set->nb_examples;
    params.nb_epochs = 20;
    params.mini_batch_size = 10;
    params.learn_rate = 0.2;
    params.regularization_rate = 5;

    size_t input_size = 32 * 32;
    size_t output_size = g_charset_size;
    size_t layers_size[] = {input_size, 30, output_size};
    struct Network *network = network_alloc(3, layers_size);

    bool verbose = true;
    gradient_descent(network, params, train_set, validation_set, verbose);

    network_save(network, "output/ocr_network");

    dataset_free(full_set);
    network_free(network);
}

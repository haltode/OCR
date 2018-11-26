#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <gtk/gtk.h>

#include "interface/interface.h"
#include "ocr.h"
#include "tests/tests.h"

static void print_help(void)
{
    printf("Usage: ocr [options]\n"
            "Optical character recognition software.\n"
            "\n"
            "Options:\n"
            "    -h, --help    "
            "Show this help.\n"
            "        --train   "
            "Train the neural network.\n"
            "        --test    "
            "Run tests (possible values: xor, random).\n");
    exit(EXIT_SUCCESS);
}

static void run_tests(char *test_name)
{
    if (!strcmp(test_name, "xor"))
        test_xor_network();
    else if (!strcmp(test_name, "random"))
        test_normal_distribution();
    else
        print_help();
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    srand(42);

    bool train = false;
    if (argc > 1)
    {
        if (!strcmp(argv[1], "--train"))
            train = true;
        else if (!strcmp(argv[1], "--test") && argc > 2)
            run_tests(argv[2]);
        else
            print_help();
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(1, "could not initialize SDL: %s.\n", SDL_GetError());
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (IMG_Init(flags) != flags)
        errx(1, "could not initialize SDL_image: %s.\n", IMG_GetError());
    gtk_init(&argc, &argv);

    if (train)
        ocr_train();
    else
        interface_start();

    IMG_Quit();
    SDL_Quit();
    return 0;
}

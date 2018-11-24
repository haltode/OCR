#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <gtk/gtk.h>

#include "interface/interface.h"
#include "tests/xor_network.h"

int main(int argc, char *argv[])
{
    srand(42);

    bool train = false;
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "--train") || !strcmp(argv[i], "-t"))
            train = true;
        if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h"))
        {
            printf("Usage: ocr [options]\n"
                    "Optical character recognition software.\n"
                    "\n"
                    "Options:\n"
                    "    -h, --help    "
                    "Show this help.\n"
                    "    -t, --train   "
                    "Train the neural network.\n");
            return 0;
        }
    }

    if (train)
    {
        printf("using xor test network\n");
        test_xor_network();
    }
    else
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            errx(1, "could not initialize SDL: %s.\n", SDL_GetError());
        int flags = IMG_INIT_JPG | IMG_INIT_PNG;
        if (IMG_Init(flags) != flags)
            errx(1, "could not initialize SDL_image: %s.\n", IMG_GetError());
        gtk_init(&argc, &argv);

        interface_start();

        IMG_Quit();
        SDL_Quit();
    }

    return 0;
}

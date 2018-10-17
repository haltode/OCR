#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            printf("TODO: write help\n");
            return 0;
        }
    }

    if (train)
    {
        printf("training xor network...\n");
        test_xor_network();
    }
    else
    {
        gtk_init(&argc, &argv);
        interface_start();
    }

    return 0;
}

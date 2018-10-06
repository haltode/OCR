#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "ocr.h"

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("Try 'ocr --help' for more information.\n");
        return -1;
    }

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
        train_ocr();
    else
        run_ocr();

    return 0;
}

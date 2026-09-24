#include <stdio.h>
#include <string.h>
#include "commands.h"

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        show_help();
        return 0;
    }

    if (strcmp(argv[1], "create") == 0)
    {

        if (argc < 3)
        {

            printf("Usage: bsa create <AppName>\n");

            return 1;
        }

        return cmd_create(argv[2]);
    }

    if (strcmp(argv[1], "build") == 0)
        return cmd_build();

    if (strcmp(argv[1], "pack") == 0)
        return cmd_pack();

    if (strcmp(argv[1], "clean") == 0)
        return cmd_clean();

    if (strcmp(argv[1], "doctor") == 0)
        return cmd_doctor();

    if (strcmp(argv[1], "version") == 0)
    {

        printf("Bornomala SDK 1.0\n");

        return 0;
    }

    show_help();

    return 0;
}
#include <window.h>

#include "include/ui.h"

int ui_run(void)
{
    BOS_Window *window =
        bos_window_create(
            900,
            600,
            "Bornomala App");

    bos_window_show(window);

    return 0;
}
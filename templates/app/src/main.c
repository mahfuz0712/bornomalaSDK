#include "include/ui.h"
#include "include/app.h"

#ifdef BOS_LINUX

int main(void)
{
    app_init();

    int result = ui_run();

    app_shutdown();

    return result;
}

#else

#include <mmr.h>

int mmr_main(void)
{
    app_init();

    int result = ui_run();

    app_shutdown();

    return result;
}

#endif
#include <stdint.h>
#include "../include/bos.h"
#include "../include/window.h"

static BOS_Window window;

BOS_Window *bos_window_create(int width,int height,const char *title)
{
    window.width=width;
    window.height=height;
    window.title=title;
    return &window;
}

void bos_window_show(BOS_Window *w)
{
    (void)w;
}

void bos_window_close(BOS_Window *w)
{
    (void)w;
}

void bos_exit(int code)
{
    (void)code;
    for(;;);
}

void bos_sleep(uint32_t ms)
{
    (void)ms;
}

void bos_log(const char *msg)
{
    (void)msg;
}

uint64_t bos_ticks(void)
{
    return 0;
}
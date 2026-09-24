#pragma once

typedef struct
{
    int width;
    int height;
    const char *title;
} BOS_Window;

BOS_Window *bos_window_create(int width,int height,const char *title);

void bos_window_show(BOS_Window *window);

void bos_window_close(BOS_Window *window);
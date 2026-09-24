#pragma once

typedef int BOS_File;

BOS_File bos_open(const char *path);

int bos_read(
    BOS_File fd,
    void *buffer,
    int size);

int bos_write(
    BOS_File fd,
    const void *buffer,
    int size);

void bos_close(BOS_File fd);
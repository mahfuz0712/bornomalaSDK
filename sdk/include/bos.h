#pragma once

#include <stdint.h>

void bos_exit(int code);

void bos_sleep(uint32_t ms);

void bos_log(const char *msg);

uint64_t bos_ticks(void);
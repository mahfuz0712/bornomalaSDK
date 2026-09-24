#pragma once

void show_help(void);

int cmd_create(const char *name);

int cmd_build(int linux_mode);

int cmd_run(void);

int cmd_pack(void);

int cmd_clean(void);

int cmd_doctor(void);
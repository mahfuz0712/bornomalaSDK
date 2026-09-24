#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "project.h"
#include "build.h"
#include "pack.h"
#include "doctor.h"

void show_help(void)
{
    printf(
        "Bornomala SDK\n\n"
        "Commands:\n"
        "  bsa create <AppName>\n"
        "  bsa build\n"
        "  bsa build --linux\n"
        "  bsa run\n"
        "  bsa pack\n"
        "  bsa clean\n"
        "  bsa doctor\n"
        "  bsa version\n");
}

int cmd_create(const char *name)
{
    return project_create(name);
}

int cmd_build(int linux_mode)
{
    return linux_mode ? build_linux() : build_bos();
}

int cmd_run(void)
{
    if (build_linux() != 0)
        return 1;

    char app_name[128] = "App";

    FILE *f = fopen("Manifest.json", "r");

    if (f)
    {
        char line[512];

        while (fgets(line, sizeof(line), f))
        {
            char *p = strstr(line, "\"name\"");

            if (!p)
                continue;

            char *q = strchr(p, ':');

            if (!q)
                continue;

            q++;

            while (*q == ' ' || *q == '"')
                q++;

            char *e = strchr(q, '"');

            if (e)
            {
                *e = '\0';
                strncpy(app_name, q, sizeof(app_name) - 1);
                app_name[sizeof(app_name) - 1] = '\0';
            }

            break;
        }

        fclose(f);
    }

    char cmd[256];
    snprintf(cmd, sizeof(cmd), "./dist/%s", app_name);

    return system(cmd);
}

int cmd_pack(void)
{
    return pack_project();
}

int cmd_clean(void)
{
    return system("rm -rf build dist");
}

int cmd_doctor(void)
{
    return doctor_run();
}
#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>

#include "build.h"

static char app_name[128] = "App";
static const char *sdk_root = "/opt/BornomalaSDK";
static const char *compiler = NULL;
static const char *linker = NULL;

/* ---------------- Helpers ---------------- */

static int run_cmd(const char *cmd)
{
    int r = system(cmd);

    if (r != 0)
    {
        fprintf(stderr, "\nCommand failed:\n%s\n", cmd);
        return 1;
    }

    return 0;
}

static int ensure_dir(const char *path)
{
    if (mkdir(path, 0755) == -1 && errno != EEXIST)
    {
        perror(path);
        return 1;
    }

    return 0;
}

static void detect_toolchain(void)
{
    compiler =
        system("command -v x86_64-linux-gnu-gcc >/dev/null 2>&1") == 0
            ? "x86_64-linux-gnu-gcc"
            : "gcc";

    linker =
        system("command -v x86_64-linux-gnu-ld >/dev/null 2>&1") == 0
            ? "x86_64-linux-gnu-ld"
            : "ld";
}

/* ---------------- Manifest ---------------- */

static void read_manifest(void)
{
    FILE *f = fopen("Manifest.json", "r");

    if (!f)
        return;

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

/* ---------------- Source Scanner ---------------- */

static void scan(const char *path, FILE *list, int linux_mode)
{
    DIR *d = opendir(path);

    if (!d)
        return;

    struct dirent *ent;

    while ((ent = readdir(d)))
    {
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
            continue;

        char full[PATH_MAX];

        snprintf(full, sizeof(full), "%s/%s", path, ent->d_name);

        struct stat st;

        if (stat(full, &st))
            continue;

        if (S_ISDIR(st.st_mode))
        {
            scan(full, list, linux_mode);
            continue;
        }

        char *ext = strrchr(ent->d_name, '.');

        if (!ext || strcmp(ext, ".c"))
            continue;

        if (linux_mode)
        {
            if (!strcmp(ent->d_name, "ui_bos.c"))
                continue;
        }
        else
        {
            if (!strcmp(ent->d_name, "ui_linux.c"))
                continue;
        }

        fprintf(list, "%s\n", full);
    }

    closedir(d);
}

/* ---------------- BOS Build ---------------- */

int build_bos(void)
{
    detect_toolchain();
    read_manifest();

    if (ensure_dir("build"))
        return 1;

    if (ensure_dir("dist"))
        return 1;

    FILE *list = fopen("build/files.txt", "w");

    if (!list)
        return 1;

    scan("src", list, 0);

    fprintf(list, "%s/sdk/lib/bos_stub.c\n", sdk_root);

    fclose(list);

    list = fopen("build/files.txt", "r");

    if (!list)
        return 1;

    char file[PATH_MAX];
    char objects[32768] = "";

    while (fgets(file, sizeof(file), list))
    {
        file[strcspn(file, "\n")] = '\0';

        char obj[8192];

        if (strstr(file, "bos_stub.c"))
        {
            snprintf(obj, sizeof(obj), "build/bos_stub.o");
        }
        else
        {
            const char *name = strrchr(file, '/');
            name = name ? name + 1 : file;

            snprintf(obj, sizeof(obj), "build/%s.o", name);
        }

        char cmd[16384];

        snprintf(cmd,
                 sizeof(cmd),
                 "%s "
                 "-std=gnu99 "
                 "-ffreestanding "
                 "-O2 "
                 "-Wall -Wextra "
                 "-I%s/sdk/include "
                 "-c \"%s\" -o \"%s\"",
                 compiler,
                 sdk_root,
                 file,
                 obj);

        printf("Compiling %s\n", file);

        if (run_cmd(cmd))
        {
            fclose(list);
            return 1;
        }

        strcat(objects, obj);
        strcat(objects, " ");
    }

    fclose(list);

    char cmd[32768];

    snprintf(cmd,
             sizeof(cmd),
             "%s "
             "-nostdlib "
             "-static "
             "-T %s/sdk/linker/app.ld "
             "-z max-page-size=0x1000 "
             "-z noexecstack "
             "-z noseparate-code "
             "-o dist/%s.mmr %s",
             linker,
             sdk_root,
             app_name,
             objects);

    printf("Linking %s.mmr\n", app_name);

    if (run_cmd(cmd))
        return 1;

    printf("\nBuild complete: dist/%s.mmr\n", app_name);

    return 0;
}

/* ---------------- Linux Build ---------------- */

int build_linux(void)
{
    detect_toolchain();
    read_manifest();

    if (ensure_dir("build"))
        return 1;

    if (ensure_dir("dist"))
        return 1;

    FILE *list = fopen("build/files_linux.txt", "w");
    if (!list)
        return 1;

    scan("src", list, 1);
    fclose(list);

    list = fopen("build/files_linux.txt", "r");
    if (!list)
        return 1;

    char sources[32768] = "";
    char file[PATH_MAX];

    while (fgets(file, sizeof(file), list))
    {
        file[strcspn(file, "\n")] = '\0';

        strcat(sources, "\"");
        strcat(sources, file);
        strcat(sources, "\" ");
    }

    fclose(list);

    char cmd[65536];

    snprintf(cmd,
             sizeof(cmd),
             "%s "
             "-std=gnu99 "
             "-DBOS_LINUX "
             "-O2 "
             "-Wall -Wextra "
             "-I%s/sdk/include "
             "%s "
             "-o dist/%s "
             "$(pkg-config --cflags --libs gtk4)",
             compiler,
             sdk_root,
             sources,
             app_name);

    printf("Building Linux preview...\n");

    if (run_cmd(cmd))
        return 1;

    printf("Linux build complete: dist/%s\n", app_name);

    return 0;
}
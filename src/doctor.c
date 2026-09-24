#include <stdio.h>
#include <stdlib.h>

static int exists(const char *cmd)
{
    char full[256];
    snprintf(full, sizeof(full), "command -v %s >/dev/null 2>&1", cmd);
    return system(full) == 0;
}

static void check(const char *name, const char *cmd)
{
    printf("%-20s", name);

    if (exists(cmd))
        printf("✓ Found\n");
    else
        printf("✗ Missing\n");
}

int doctor_run()
{
    printf("\n");
    printf("=====================================\n");
    printf("      Bornomala SDK Doctor\n");
    printf("=====================================\n\n");

    check("GCC", "gcc");
    check("Cross GCC", "x86_64-linux-gnu-gcc");
    check("NASM", "nasm");
    check("ZIP", "zip");
    check("QEMU", "qemu-system-x86_64");

    printf("\nPreferred Compiler: ");

    if (exists("x86_64-linux-gnu-gcc"))
        printf("x86_64-linux-gnu-gcc\n");
    else if (exists("gcc"))
        printf("gcc\n");
    else
        printf("None\n");

    return 0;
}
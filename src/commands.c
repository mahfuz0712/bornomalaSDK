#include <stdio.h>
#include <stdlib.h>
#include "commands.h"
#include "project.h"
#include "build.h"
#include "pack.h"
#include "doctor.h"

void show_help()
{

    printf(
        "Bornomala SDK\n\n"
        "Commands:\n"
        "  bsa create <AppName>\n"
        "  bsa build\n"
        "  bsa pack\n"
        "  bsa clean\n"
        "  bsa doctor\n"
        "  bsa version\n");
}

int cmd_create(const char *name) { return project_create(name); }

int cmd_build() { return build_project(); }

int cmd_pack() { return pack_project(); }

int cmd_clean() { return system("rm -rf build dist"); }

int cmd_doctor() { return doctor_run(); }
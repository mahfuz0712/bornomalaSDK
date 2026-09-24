#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char app_name[128]="App";

static int run_cmd(const char *cmd){

    int r=system(cmd);

    if(r!=0){

        fprintf(stderr,"\nCommand failed:\n%s\n",cmd);

        return 1;

    }

    return 0;

}

static void read_manifest(){

    FILE *f=fopen("Manifest.json","r");

    if(!f) return;

    char line[512];

    while(fgets(line,sizeof(line),f)){

        char *p=strstr(line,"\"name\"");

        if(!p) continue;

        char *q=strchr(p,':');

        q++;

        while(*q==' '||*q=='"') q++;

        char *e=strchr(q,'"');

        if(e){

            *e=0;

            strncpy(app_name,q,sizeof(app_name)-1);

        }

        break;

    }

    fclose(f);

}

int pack_project(){

    read_manifest();

    if(run_cmd("rm -rf build/package")) return 1;

    char cmd[4096];

    snprintf(cmd,sizeof(cmd),

    "mkdir -p build/package/%s",

    app_name);

    if(run_cmd(cmd)) return 1;

    snprintf(cmd,sizeof(cmd),

    "cp dist/%s.mmr build/package/%s/",

    app_name,app_name);

    if(run_cmd(cmd)) return 1;

    snprintf(cmd,sizeof(cmd),

    "cp Manifest.json build/package/%s/",

    app_name);

    if(run_cmd(cmd)) return 1;

    snprintf(cmd,sizeof(cmd),

    "cp -r src/resources build/package/%s/ 2>/dev/null || true",

    app_name);

    if(run_cmd(cmd)) return 1;

    snprintf(cmd,sizeof(cmd),

    "cd build/package && zip -r ../../dist/%s.bsa %s >/dev/null",

    app_name,app_name);

    if(run_cmd(cmd)) return 1;

    printf("Package created: dist/%s.bsa\n",app_name);

    return 0;

}
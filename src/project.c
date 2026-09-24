#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static const char *sdk_root="/opt/BornomalaSDK";

static int run_cmd(const char *cmd){

    int r=system(cmd);

    if(r!=0){

        fprintf(stderr,"\nCommand failed:\n%s\n",cmd);

        return 1;

    }

    return 0;

}

int project_create(const char *name){

    char cmd[2048];

    snprintf(cmd,sizeof(cmd),

    "mkdir -p \"%s/src/include\" \"%s/src/resources\"",

    name,name);

    if(run_cmd(cmd)) return 1;

    snprintf(cmd,sizeof(cmd),

    "cp -r \"%s/templates/app/src/.\" \"%s/src/\"",

    sdk_root,name);

    if(run_cmd(cmd)) return 1;

    char path[PATH_MAX];

    snprintf(path,sizeof(path),"%s/Manifest.json",name);

    FILE *mf=fopen(path,"w");

    fprintf(mf,

"{\n"

"  \"name\":\"%s\",\n"

"  \"package\":\"com.bornomala.%s\",\n"

"  \"version\":\"1.0.0\",\n"

"  \"author\":\"Unknown\",\n"

"  \"entry\":\"%s.mmr\",\n"

"  \"permissions\":[]\n"

"}\n",

    name,name,name);

    fclose(mf);

    snprintf(path,sizeof(path),"%s/.gitignore",name);

    FILE *gf=fopen(path,"w");

    fprintf(gf,"build/\ndist/\n.bsa/\n");

    fclose(gf);

    printf("Created project: %s\n",name);

    return 0;

}
/* Example: parse a simple configuration file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ini.h"

typedef struct
{
    /* protocol */
    int version;

    /* user */
    const char* name;
    const char* email;
    bool active;
    double pi;
    long long int trillion;
} configuration;

static int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    configuration* pconfig = (configuration*)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("protocol", "version")) {
        pconfig->version = atoi(value);
    } else if (MATCH("user", "name")) {
        pconfig->name = strdup(value);
    } else if (MATCH("user", "email")) {
        pconfig->email = strdup(value);
    } else if (MATCH("user", "active")) {
        pconfig->active = (bool)value;
    } else if (MATCH("user", "pi")) {
        pconfig->pi = atof(value);
    } else if (MATCH("user", "trillion")) {
        pconfig->trillion = atoll(value);
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

int main(int argc, char* argv[])
{
    configuration config;

    /* set defaults */
    config.version = 0;
    config.name = NULL;
    config.email = NULL;
    config.active = false;
    config.pi = 3.1;
    config.trillion = 20;

    if (ini_parse("test.ini", handler, &config) < 0) {
        printf("Can't load 'test.ini'\n");
        return 1;
    }

    printf(
        "Config loaded from 'test.ini':\n"
        "version=%d\n"
        "name=%s\n"
        "email=%s\n"
        "active=%d\n"
        "pi=%f\n"
        "trillion=%lld\n",
        config.version,
        config.name,
        config.email,
        config.active,
        config.pi,
        config.trillion
    );

    if (config.name)
        free((void*)config.name);
    if (config.email)
        free((void*)config.email);

    return 0;
}
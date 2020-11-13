#pragma once
#ifndef ltools_h
#define ltools_h

#include <cstdlib>

#define PATH_MAX _MAX_PATH
#define no_argument 0
#define required_argument 1
#define optional_argument 2

struct option {
    const char *name;
    int has_arg;
    int *flag;
    int val;
};

int getopt_long(int argc, char *const argv[],
                const char *optstring,
                const struct option *longopts, int *longindex);

extern char *optarg;
extern int optind, opterr, optopt;

#endif
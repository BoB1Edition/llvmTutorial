#include <cstdio>
#include <cstring>

#include "ltools.h"

char *optarg;
int optind, opterr, optopt;
static int nextchar = 0;

int getopt_long(int argc, char *const argv[], const char *optstring, const struct option *longopts, int *longindex)
{
    *longindex = 0;
    nextchar++;
    if( nextchar >= argc) return -1;
    char *arg = argv[nextchar];
    if (arg[0] == '-' && arg[1] == '-')
    {
        char *shortarg = &arg[2];
        for (;; *longindex++) {
            if (longopts[*longindex].name == NULL)
                break;
            if (strncmp(longopts[*longindex].name, shortarg, strlen(shortarg)) == 0)
            {
                switch (longopts[*longindex].has_arg)
                {
                case no_argument:
                    break;
                case required_argument:
                    if (strlen(longopts[*longindex].name) == strlen(shortarg)) {
                        optarg = argv[nextchar+1];
                        if (optarg[0]=='-') return -1;
                    }
                break;
                case optional_argument:
                    break;
                default:
                    break;
                }
                if (longopts[*longindex].flag == NULL)
                    return longopts[*longindex].val;
                return *longopts[*longindex].flag;
            }
        }
    }
    if (arg[0] == '-') {
        const char *point = strchr(optstring, (int)arg[1]);
        if (point == NULL) return -1;
        if (optstring[point - optstring + 1] == ':')
        {
            nextchar++;
            optarg = argv[nextchar];
            return arg[1];
        }
        else {
            return arg[1];
        }
    }
    return -1;
}
#include "getopt.h"
#include <stdlib.h>

int getopt(int argc, char *const argv[], const char *optstring) {
    for(int i =0; i< argc; i++) {
        printf("arg[%i]: %s\n", i, argv[i]);
    }
}

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#include <unistd.h>
#include <getopt.h>
#elif _WIN32
#include "mytools/getopt.h"
#endif

int main(int argc, char* argv[]) {
    getopt(argc, argv, "");
}
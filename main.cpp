#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <getopt.h>
#include <dir.h>
#include "CApp.h"

typedef struct config {
    char source[_MAX_PATH], output[_MAX_PATH], directory[_MAX_PATH];
} config;

int defaultconfig(config *conf) {
    strncpy(conf->directory,"./\0", 3);
    strncpy(conf->output, "main.execute\0", 13);
    strncpy(conf->source, "main.ltl\0", 9);
    return 0;
}

void printhelp() {
    printf("the usage:\n");
    printf("-h or --help: print this help and exit\n");
    printf("-v or --version: print version and exit\n");
    printf("-s<filename> or --source=<filename>: install source file in filename, default main.ltl\n");
    printf("-o<filename> or --output=<filename>: install output file in filename, default main.execute\n");
    printf("-d<path> or --directory=<path>: install work dir in path, default .\n");
}

int main(int argc, char *argv[])
{
    config *conf = new(config);
    defaultconfig(conf);
    const char *short_options = "hvs:o:d:";
    const struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {"source", required_argument, NULL, 's'},
        {"output", required_argument, NULL, 'o'},
        {"directory", required_argument, NULL, 'd'},
        {NULL, 0, NULL, 0}};
    int rez;
    int option_index = -1;
    while ((rez = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (rez) {
        case 'h':
            printf("option_index = %d (\"%s\",%d,%c)\n",
                   option_index,
                   long_options[option_index].name,
                   long_options[option_index].has_arg,
                   long_options[option_index].val);
            exit(0);
            break;
        case 'v':
            printf("Verion: 0.0.0001\n");
            exit(0);
            break;
        case 's':
            strncpy(conf->source, optarg, _MAX_PATH);
            break;
        case 'o':
            strncpy(conf->output, optarg, _MAX_PATH);
            break;
        case 'd':
            strncpy(conf->directory, optarg, _MAX_PATH);
            break;

        default:
            break;
        }
        option_index = -1;
    }
    FILE *input = fopen(conf->source, "rt");
    chdir(conf->directory);
    FILE *output = fopen(conf->output, "wb");
    delete conf;
    CApp capp(input, output);
    
    return 0;
}
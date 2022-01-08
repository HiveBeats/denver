#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int opt;
    char* env_filename;
    char* tmp_filename;
    while ((opt = getopt(argc, argv, "e:t:")) != -1) {
        switch (opt) {
            case 'e': 
                printf("env filename: %s\n", optarg); 
                break;
            case 't': 
                printf("template filename: %s\n", optarg); 
                break;
            case ':': 
                printf("option needs a value\n"); 
                break; 
            case '?': 
                printf("unknown option: %c\n", optopt);
                break; 
        }
    }

    return 0;
}
// Copyright (c) 2021.
// BVernam: a simple program for one-time-pad enccription.
#include <stdio.h>
#include "bvernam.h"

void print_call_error(int args);

int main(int argc, char** argv) {
    if (argc != 4) {
        print_call_error(argc-1);
        return -1;
    }
    encode(argv[1],argv[2],argv[3]);
    return 0;
}

void print_call_error(int args) {
    fprintf(stderr,"\n\nWrong number of parameters! Expected 3 are %d!\n",args);
    fprintf(stderr,"\nbvernan <keyfile> <inputfile> <outputfile>\n\n");
}

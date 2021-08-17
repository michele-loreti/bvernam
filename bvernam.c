// Copyright (c) 2021.
// BVernam: a simple program for one-time-pad enccription.
#include <stdlib.h>
#include "bvernam.h"

#define DEFAULT_BUFFER_SIZE 512


byte encode_byte(t_key* key, byte b) {
    return b ^ next(key);
}

void encode_buffer(t_key* key, byte* buffer, byte* output, long len) {
    int outcode = 0;
    for(long i=0; i<len; i++) {
        output[i] = encode_byte(key, buffer[i]);
    }
}

void encode_file(t_key* key, FILE* input_file, FILE* output_file, int buffer_size) {
    byte* input_buffer = malloc(buffer_size);
    byte* output_buffer = malloc(buffer_size);
    size_t dl;
    while ((dl= fread(input_buffer,1,buffer_size,input_file))>0) {
        encode_buffer(key, input_buffer, output_buffer, dl);
        fwrite(output_buffer,1,dl,output_file);
    }
}

void encode(char* key_file_name, char* input_file_name, char* output_file_name) {
    t_key* key = open_key_file(key_file_name, DEFAULT_BUFFER_SIZE);
    FILE* input_file = open_input_file(input_file_name);
    FILE* output_file = open_output_file(output_file_name);
    if ((key != NULL)&&(input_file != NULL)&&(output_file != NULL)) {
        encode_file(key, input_file, output_file, DEFAULT_BUFFER_SIZE);
    }
    close_key(key);
    close_file(input_file);
    close_file(output_file);
}

FILE* open_input_file(char *name) {
    FILE* file = fopen(name,"rb");
    if (file == NULL) {
        perror("Error while opening input file.");
    }
    return file;
}

FILE* open_output_file(char *name) {
    FILE* file = fopen(name,"wb");
    if (file == NULL) {
        perror("Error while opening output file.");
    }
    return file;
}

byte next(t_key* key) {
    if (key->buffer_limit==key->buffer_counter) {//All the bytes in the buffer have been used.
        fill_buffer(key);
    }
    byte result = key->buffer[key->buffer_counter++];
    key->byte_counter++;
    rewind_key(key);
    return result;
}

void fill_buffer(t_key *key) {
    size_t dl = 0;
    while (dl == 0) {
        dl = fread(key->buffer,1,key->buffer_size, key->key_file);
        if (dl == 0) {//We reached the end of file
            end_of_file(key);
        }
    }
    key->buffer_counter = 0;
    key->buffer_limit = dl;
}

void rewind_key(t_key *key) {
    if (key->file_length == key->byte_counter) {
        //A block has been encoded we start a new round.
        key->round_counter++;
        key->byte_counter=0;
        fseek(key->key_file,key->round_counter%key->file_length,SEEK_SET);
        key->buffer_counter = key->buffer_limit;
    }
}

t_key* get_key(FILE* keyFile, long buffer_size) {
    t_key* key = malloc(sizeof(t_key));
    key->key_file = keyFile;
    key->buffer_size = buffer_size;
    key->buffer = malloc(buffer_size);
    key->buffer_limit = fread(key->buffer,1,key->buffer_size,key->key_file);
    if (key->buffer_limit == 0) {
        perror("Key file is empty!");
        return NULL;
    }
    key->byte_counter = 0;
    key->file_length = -1;
    key->round_counter = 0L;
    return key;
}

void close_key(t_key* key) {
    if (key != NULL) {
        free(key->buffer);
        fclose(key->key_file);
        free(key);
    }
}

void close_file(FILE* file) {
    if (file != NULL) {
        fclose(file);
    }
}

void end_of_file(t_key* key) {
    if (key->file_length < 0) {
        key->file_length = key->byte_counter;
    }
    if (key->file_length == key->byte_counter) {
        rewind_key(key);
    } else {
        fseek(key->key_file,0L,SEEK_SET);
    }
}

t_key* open_key_file(char* key_file_name, long buffer_size) {
    FILE* file = fopen(key_file_name,"rb");
    if (file == NULL) {
        perror("An error occurred while opening key file!");
        return NULL;
    }
    return get_key(file,buffer_size);
}

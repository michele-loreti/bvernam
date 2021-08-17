//
// Created by Michele Loreti on 21/07/21.
//

#include <stdio.h>

#ifndef UNTITLED_BVERNAN_H
#define UNTITLED_BVERNAN_H

typedef unsigned char byte;

#define EMPTY_KEY_FILE 0;

/**
 * Data structure used to store the bvernan key.
 */
typedef struct str_key {
    /**
     * Size of the buffer used to store data read from key file.
     */
    long buffer_size;

    /**
     * Indicates the number of relevant elements in the buffer.
     */
    long buffer_limit;

    /**
     * Current byte in the buffer.
     */
    long buffer_counter;

    /**
     * Number of bytes encoded in the current round.
     */
    long byte_counter;

    /**
     * Length of key file. When this value is not yet computed is -1.
     */
    long file_length;

    /**
     * Key file.
     */
    FILE* key_file;

    /**
     * Buffer used to store data read from file.
     */
    byte *buffer;

    /**
     * Current encoding round.
     */
    long round_counter;

} t_key;

/**
 * Get the next byte from the key.
 *
 * @param key       key structure
 * @return next byte in the key.
 */
byte next(t_key* key);

/**
 * Fill the buffer with the bytes read from the key file.
 *
 * @param key key structure
 */
void fill_buffer(t_key *key);

/**
 * Encode a single byte e store the result in the given location.
 *
 * @param key key structure
 * @param src source byte
 * @return encoded byte.
 */
byte encode_byte(t_key* key, byte src);

/**
 * Encode the first len bytes of buffer with the given key and store the result in output.
 *
 * @param key
 * @param buffer
 * @param output
 * @param len
 */
void encode_buffer(t_key* key, byte* buffer, byte* output, long len);

/**
 * Encode the input_file with the given key and store the result in output_file. Buffers of size
 * buffer_size are used for i/o operations.
 *
 * @param key key structure.
 * @param input_file  input file.
 * @param output_file  output file.
 * @param buffer_size buffer size.
 *
 */
void encode_file(t_key* key, FILE* input_file, FILE* output_file, int buffer_size);

/**
 * Encode the given input file by using the given key file and storing the result in the output_file.
 *
 * @param key_file_name key file name.
 * @param input_file_name  input file name.
 * @param output_file_name output file name.
 */
void encode(char* key_file_name, char* input_file_name, char* output_file_name);

/**
 * Open the key file and allocate the data structure.
 *
 * @param key_file_name key file name.
 * @return  key data structure.
 */
t_key* open_key_file(char* key_file_name,  long buffer_size);

/**
 * Allocate the key data structure with the given key file.
 *
 * @param keyFile pointer to the key file.
 * @param buffer_size size of buffer.
 * @return key data structure.
 */
t_key* get_key(FILE* keyFile, long buffer_size);

/**
 * Close and deallocate the key data structure.
 *
 * @param key key data structure.
 */
void close_key(t_key* key);

/**
 * Open input file.
 *
 * @param name input file name.
 * @return pointer to the file to encode.
 */
FILE* open_input_file(char *name);

/**
 * Open output file.
 *
 * @param name output file name.
 *
 * @return pointer to the output file.
 */
FILE* open_output_file(char *name);

/**
 * Close a file.
 *
 * @param file a file to close.
 */
void close_file(FILE* file);

/**
 * This function is used to rewind the key when a round is completed.
 *
 * @param key key data structure.
 */
void rewind_key(t_key *key);

/**
 * This function is invoked when the end of key file is reached.
 *
 * @param key key data structure.
 */
void end_of_file(t_key *key);


#endif //UNTITLED_BVERNAN_H
